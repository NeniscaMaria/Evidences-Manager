#include "StandardClearanceLevelGUI.h"
#include <exception>

StandardClearanceLevel::StandardClearanceLevel(QWidget* parent) : QWidget{ parent }
{
	this->initGUI();
}

StandardClearanceLevel::StandardClearanceLevel(Controller<Evidence>* savedEvidences, Controller<Evidence>* evid)
{
	this->savedEvidences = savedEvidences;
	this->evidences = evid;
	this->initGUI();
}


void StandardClearanceLevel::initGUI()
{
	this->evidencesIterated = 0;
	this->repositoryEvidencesWithTheseCharacteristics = NULL;
	this->errorBox = new QErrorMessage();
	//creating the main window in which every widget will be in
	this->window = new QWidget{};
	this->window->setWindowTitle("Standard Clearance Level"); // setting the title of the window

	//creating the main layout <=> vertical; layout
	this->mainLayout = new QVBoxLayout{};
	this->window->setLayout(mainLayout);

	//the main layout has another horizontal layout at the top and a vertical one at the bottom

	//creating the top horizontal layout
	this->topLayoutBox = new QWidget{};
	this->topLayout = new QHBoxLayout{};
	topLayoutBox->setLayout(topLayout);
	mainLayout->addWidget(topLayoutBox);

	//the top layout has 2 grid layouts
	//creating top grid layout
	this->topGridLayoutBox = new QWidget{};
	this->topGridLayout = new QGridLayout{};
	topGridLayoutBox->setLayout(topGridLayout);
	topLayout->addWidget(topGridLayoutBox);
	//populating the top grid layout
	//adding measurement boxes
	this->measurementTextBox = new QLineEdit{};
	this->measurementLabel = new QLabel{ "&Measurement:" };
	measurementLabel->setBuddy(measurementTextBox);
	topGridLayout->addWidget(measurementLabel, 0, 0);
	topGridLayout->addWidget(measurementTextBox, 1, 0);
	//adding quantty boxes
	this->quantityTextBox = new QLineEdit{};
	this->quantityLabel = new QLabel{ "&Quantity:" };
	quantityLabel->setBuddy(quantityTextBox);
	topGridLayout->addWidget(quantityLabel, 0, 1);
	topGridLayout->addWidget(quantityTextBox, 1, 1);
	//adding push button
	this->listButton = new QPushButton{ "&List" };
	topGridLayout->addWidget(listButton, 1, 2);

	//creating bottom grid layout
	this->bottomGridLayoutBox = new QWidget{};
	this->bottomGridLayout = new QGridLayout{};
	bottomGridLayoutBox->setLayout(bottomGridLayout);
	topGridLayout->addWidget(bottomGridLayoutBox);
	//populating bottom grid layout
	this->displayEvidence = new QLabel{};
	bottomGridLayout->addWidget(displayEvidence, 0, 0);
	this->idLine = new QLineEdit{};
	bottomGridLayout->addWidget(idLine, 1, 0);
	this->saveButton = new QPushButton{ "&Save" };
	bottomGridLayout->addWidget(saveButton, 1, 1);
	this->nextButton = new QPushButton{ "&Next" };
	bottomGridLayout->addWidget(nextButton, 1, 2);



	//creating the bottom vertical layout
	this->bottomLayoutBox = new QWidget{};
	this->bottomLayout = new QVBoxLayout{};
	bottomLayoutBox->setLayout(bottomLayout);
	mainLayout->addWidget(bottomLayoutBox);
	//populating bottom vertical layout
	this->savedEvidencesLabel = new QLabel{ "Saved evidences:" };
	bottomLayout->addWidget(savedEvidencesLabel);
	this->listOfEvidences = new QListWidget{};
	bottomLayout->addWidget(listOfEvidences);
	this->changeMode = new QPushButton{ "&SeniorClearance Level" };
	bottomLayout->addWidget(changeMode);

	//connecting the buttons
	connect(this->changeMode, &QPushButton::clicked, this, &StandardClearanceLevel::switchModes);
	connect(this->listButton, &QPushButton::clicked, this, &StandardClearanceLevel::list);
	connect(this->saveButton, &QPushButton::clicked, this, &StandardClearanceLevel::saveEvidence);
	connect(this->nextButton, &QPushButton::clicked, this, &StandardClearanceLevel::showNextEvidence);
	window->show();
	this->showSavedEvidences();
}

void StandardClearanceLevel::switchModes()
{
	this->window->close();
	this->seniorClearanceLevelMeniu = new SeniorClearanceLevel{this->evidences,this->savedEvidences};
	this->seniorClearanceLevelMeniu->show();
}

Controller<Evidence>* StandardClearanceLevel::getElementsMeasurementAndQuantity(char*measurement, int quantity) {
	Repository<Evidence>* temporaryRepository = new Repository<Evidence>();
	Controller<Evidence>* evidencesTmp = new Controller<Evidence>{ temporaryRepository };
	auto iterator = this->evidences->list();
	while (iterator.valid()) {
		try {
			Evidence* evidenceToAdd = iterator.getCurrent();
			if (strcmp(evidenceToAdd->getMeasurement(), measurement) == 0 && evidenceToAdd->getQuantity() <= quantity) {
				evidencesTmp->add(evidenceToAdd);
				iterator.next();
			}
			else {
				iterator.next();
			}
		}
		catch (std::exception) {
			return evidencesTmp;
		}
	}
	return evidencesTmp;
}
void StandardClearanceLevel::list()
{
	this->messageFlag = 0; //when is 0, a message will be displayed when the iteration will erach the end of the list
	std::string constArray = this->measurementTextBox->text().toStdString();
	char* measurement = new char[constArray.length() + 1];
	strcpy(measurement, constArray.c_str());
	if (strlen(measurement) == 0) {
		this->errorBox->showMessage(QString::fromLocal8Bit("Please insert the measurements!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}

	constArray = this->quantityTextBox->text().toStdString();
	char* quantityChar = new char[constArray.length() + 1];
	strcpy(quantityChar, constArray.c_str());
	if (strlen(quantityChar) == 0) {
		this->errorBox->showMessage(QString::fromLocal8Bit("Please insert the quantity!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}
	if (atoi(quantityChar) == 0) {
		this->errorBox->showMessage(QString::fromLocal8Bit("Invalid argument! Quantity must be a number!"), QString::fromLocal8Bit("Invalid data"));
		return;
	}
	int quantity = atoi(quantityChar);

	this->repositoryEvidencesWithTheseCharacteristics = this->getElementsMeasurementAndQuantity(measurement, quantity);
	if (this->repositoryEvidencesWithTheseCharacteristics->size() == 0) {
		this->errorBox->showMessage(QString::fromLocal8Bit("There are no evidences with this charactersitics!"), QString::fromLocal8Bit("Invalid data"));
		return;
	}

	RepositoryIterator<Evidence> evidencesToList = this->repositoryEvidencesWithTheseCharacteristics->list();
	if (evidencesToList.valid()) {
		try {
			auto evidence = evidencesToList.getCurrent();
			this->displayNextEvidence(evidence);
			evidencesToList.next();
		}
		catch (std::exception) {
			evidencesToList.first();
			auto evidence = evidencesToList.getCurrent();
			this->displayNextEvidence(evidence);
			evidencesToList.next();
		}
	}
	else {
		evidencesToList.first();
		auto evidence = evidencesToList.getCurrent();
		this->displayNextEvidence(evidence);
		evidencesToList.next();
	}
	this->evidencesIterated = 1;
}

void StandardClearanceLevel::showSavedEvidences()
{
	this->listOfEvidences->clear();
	RepositoryIterator<Evidence> iteratorRepository = this->savedEvidences->list();
	this->listOfEvidences->setAlternatingRowColors(Qt::gray);
	while (iteratorRepository.valid()) {
		Evidence* evidence = new Evidence();
		evidence = iteratorRepository.getCurrent();
		char str[400];
		strcpy(str, "Evidence ID: ");
		strcat(str, evidence->getId());
		strcat(str, " measurement: ");
		strcat(str, evidence->getMeasurement());
		strcat(str, " image clarity: ");
		std::string imageClarity = std::to_string(evidence->getImageClarityLevel());
		strcat(str, imageClarity.c_str());
		strcat(str, " quantity: ");
		std::string quantity = std::to_string(evidence->getQuantity());
		strcat(str, quantity.c_str());
		strcat(str, " photograph: ");
		strcat(str, evidence->getPhotograph());
		this->listOfEvidences->addItem(QString::fromLocal8Bit(str));
		iteratorRepository.next();
	}

}

void StandardClearanceLevel::saveEvidence()
{
	std::string constArray = this->idLine->text().toStdString();
	char* ID = new char[constArray.length() + 1];
	strcpy(ID, constArray.c_str());
	if (strlen(ID) == 0) {
		this->errorBox->showMessage(QString::fromLocal8Bit("Please insert the ID!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}
	int position = this->evidences->search(ID);
	delete[] ID;
	if (position == -1) {
		this->errorBox->showMessage(QString::fromLocal8Bit("Invalid ID! An evidence with this ID does not exist!"), QString::fromLocal8Bit("Invalid data"));
		return;
	}
	try {
		auto evidenceToSave = this->evidences->getElement(position);
		this->savedEvidences->add(evidenceToSave);
		this->errorBox->showMessage(QString::fromLocal8Bit("Evidence saved successfully!"), QString::fromLocal8Bit("Success"));
		this->showSavedEvidences();
	}
	catch (RepoError& error) {
		this->errorBox->showMessage(QString::fromLocal8Bit(error.what()), QString::fromLocal8Bit("Invalid data"));
		return;
	}
}

void StandardClearanceLevel::showNextEvidence()
{
	
	if (this->repositoryEvidencesWithTheseCharacteristics == NULL) {
		RepositoryIterator<Evidence> evidencesToList = this->evidences->list();
		this->getToNext(evidencesToList);
		this->evidencesIterated += 1;
	}
	else {
		RepositoryIterator<Evidence> evidencesToList = this->repositoryEvidencesWithTheseCharacteristics->list();
		this->getToNext(evidencesToList);
		this->evidencesIterated += 1;
	}
	
}

void StandardClearanceLevel::displayNextEvidence(Evidence* evidence)
{
	char str[400];
	strcpy(str, "Evidence ID: ");
	strcat(str, evidence->getId());
	strcat(str, " measurement: ");
	strcat(str, evidence->getMeasurement());
	strcat(str, " image clarity: ");
	std::string imageClarity = std::to_string(evidence->getImageClarityLevel());
	strcat(str, imageClarity.c_str());
	strcat(str, " quantity: ");
	std::string quantity = std::to_string(evidence->getQuantity());
	strcat(str, quantity.c_str());
	strcat(str, " photograph: ");
	strcat(str, evidence->getPhotograph());

	this->displayEvidence->setText(QString::fromLocal8Bit(str));
}

void StandardClearanceLevel::getToNext(RepositoryIterator<Evidence> evidencesToList)
{
	int i = 0;
	while (i != this->evidencesIterated) {
		if (evidencesToList.valid()) {
			try {
				evidencesToList.next();
			}
			catch (std::exception) {
				evidencesToList.first();
				evidencesToList.next();
			}
		}
		else {
			evidencesToList.first();
			evidencesToList.next();
		}
		i += 1;
	}
	if (evidencesToList.valid()) {
		try {
			auto evidence = evidencesToList.getCurrent();
			this->displayNextEvidence(evidence);
			evidencesToList.next();
		}
		catch (std::exception) {
			if (this->messageFlag == 0) {
				this->errorBox->showMessage(QString::fromLocal8Bit("This is the last evidence. From now on, when you reach the last one, all the evidences with this characteristics will be displayed again."));
				this->messageFlag = 1;
			}
			evidencesToList.first();
			auto evidence = evidencesToList.getCurrent();
			this->displayNextEvidence(evidence);
			evidencesToList.next();
		}
	}
	else {
		if (this->messageFlag == 0) {
			this->errorBox->showMessage(QString::fromLocal8Bit("This is the last evidence. From now on, when you reach the last one, all the evidences with this characteristics will be displayed again."));
			this->messageFlag = 1;
		}
		evidencesToList.first();
		auto evidence = evidencesToList.getCurrent();
		this->displayNextEvidence(evidence);
		evidencesToList.next();
	}
	
}


