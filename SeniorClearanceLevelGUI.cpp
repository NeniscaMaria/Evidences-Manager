#include "SeniorClearanceLevelGUI.h"
#include "StandardClearanceLevelGUI.h"
#include <QString>
#include <QKeyEvent>
#include <qdebug.h>
SeniorClearanceLevel::SeniorClearanceLevel(Controller<Evidence>* ctrl, Controller<Evidence>* ctrlSaved)
{
	this->evidences = ctrl;
	this->savedEvidences = ctrlSaved;
	this->initGUI();
}

void SeniorClearanceLevel::initGUI() {
	this->action = false;
	this->index = -1;
	//creating the main layout <=> vertical layout
	this->mainLayout = new QVBoxLayout{};
	this->setLayout(mainLayout);

	//at the top we have the lists of evidences
	this->listEvidences = new QListWidget{};
	this->mainLayout->addWidget(this->listEvidences);

	//the maion layout has at the bottom a grid layout
	this->gridLayoutBox = new QWidget{};
	this->gridLayout = new QGridLayout{};
	this->gridLayoutBox->setLayout(gridLayout);
	this->mainLayout->addWidget(gridLayoutBox);

	//adding widget to the grid layout
	this->addButton = new QPushButton{ "&Add" };
	this->removeButton = new QPushButton{ "&Remove" };
	this->updateButton = new QPushButton{ "&Update" };
	this->undoButton = new QPushButton{ "&Undo" };
	this->redoButton = new QPushButton{ "&Redo" };
	this->standardClearanceLevelButton = new QPushButton{"&Standard Clearance Level"};
	this->gridLayout->addWidget(this->addButton, 0, 0);
	this->gridLayout->addWidget(this->updateButton, 0, 1);
	this->gridLayout->addWidget(this->removeButton, 0, 2);
	this->gridLayout->addWidget(this->undoButton, 1, 0);
	this->gridLayout->addWidget(this->redoButton, 1, 2);
	this->gridLayout->addWidget(this->standardClearanceLevelButton, 3, 0);

	//connecting the buttons
	connect(this->standardClearanceLevelButton, &QPushButton::clicked, this, &SeniorClearanceLevel::switchModes);
	connect(this->addButton, &QPushButton::clicked, this, &SeniorClearanceLevel::displayAddMeniu);
	connect(this->removeButton, &QPushButton::clicked, this, &SeniorClearanceLevel::displayRemoveMeniu);
	connect(this->updateButton, &QPushButton::clicked, this, &SeniorClearanceLevel::displayUpdateMeniu);
	connect(this->undoButton, &QPushButton::clicked, this, &SeniorClearanceLevel::undo);
	connect(this->redoButton, &QPushButton::clicked, this, &SeniorClearanceLevel::redo);
	this->displayEvidences();
}

void SeniorClearanceLevel::displayEvidences()
{
	this->listEvidences->clear();
	RepositoryIterator<Evidence> iteratorRepository = this->evidences->list();
	this->listEvidences->setAlternatingRowColors(Qt::gray);
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
		std::string quantity = std::to_string( evidence->getQuantity());
		strcat(str, quantity.c_str());
		strcat(str, " photograph: ");
		strcat(str, evidence->getPhotograph());
		this->listEvidences->addItem(QString::fromLocal8Bit(str));
		iteratorRepository.next();
	}
	
}

void SeniorClearanceLevel::switchModes()
{
	this->close();
	this->standardClearanceLevelMeniu = new StandardClearanceLevel{ this->savedEvidences,this->evidences };
	this->standardClearanceLevelMeniu->show();
}

void SeniorClearanceLevel::displayAddMeniu()
{
	this->addError = new QErrorMessage{};
	this->addWindow = new QWidget{};
	this->addWindowLayout = new QGridLayout{};
	this->addWindow->setLayout(this->addWindowLayout);

	this->IDLabel = new QLabel{ "ID: " };
	this->addWindowLayout->addWidget(this->IDLabel, 0, 0);
	this->IDLine = new QLineEdit{};
	this->addWindowLayout->addWidget(this->IDLine, 0, 1);

	this->measurementLabel = new QLabel{ "Measurement: " };
	this->addWindowLayout->addWidget(this->measurementLabel, 1, 0);
	this->measurementLine = new QLineEdit{};
	this->addWindowLayout->addWidget(this->measurementLine, 1, 1);

	this->imageClarityLabel = new QLabel{ "Image clarity: " };
	this->addWindowLayout->addWidget(this->imageClarityLabel, 2, 0);
	this->imageClarityLine = new QLineEdit{};
	this->addWindowLayout->addWidget(this->imageClarityLine, 2, 1);

	this->quantityLabel = new QLabel{ "Quantity: " };
	this->addWindowLayout->addWidget(this->quantityLabel, 3, 0);
	this->quantityLine = new QLineEdit{};
	this->addWindowLayout->addWidget(this->quantityLine, 3, 1);

	this->photographLabel = new QLabel{ "Photograph: " };
	this->addWindowLayout->addWidget(this->photographLabel, 4, 0);
	this->photographLine = new QLineEdit{};
	this->addWindowLayout->addWidget(this->photographLine, 4, 1);

	this->saveButton = new QPushButton{"Save"};
	this->addWindowLayout->addWidget(this->saveButton, 6, 2);

	//connecting the button
	connect(this->saveButton, &QPushButton::clicked, this, &SeniorClearanceLevel::addEvidence);
	this->addWindow->show();
}

void SeniorClearanceLevel::displayRemoveMeniu()
{
	this->removeError = new QErrorMessage{};
	this->removeWindow = new QWidget{};
	this->removeWindowLayout = new QGridLayout{};
	this->removeWindow->setLayout(this->removeWindowLayout);

	this->IDLabel = new QLabel{ "ID: " };
	this->removeWindowLayout->addWidget(this->IDLabel, 0, 0);
	this->IDLine = new QLineEdit{};
	this->removeWindowLayout->addWidget(this->IDLine, 0, 1);

	this->deleteButton = new QPushButton{ "Remove evidence" };
	this->removeWindowLayout->addWidget(this->deleteButton, 3, 2);

	//connecting button
	connect(this->deleteButton, &QPushButton::clicked, this, &SeniorClearanceLevel::removeEvidence);
	this->removeWindow->show();
}

void SeniorClearanceLevel::displayUpdateMeniu()
{
	this->updateError = new QErrorMessage{};
	this->updateWindow = new QWidget{};
	this->updateWindowLayout = new QGridLayout{};
	this->updateWindow->setLayout(this->updateWindowLayout);

	this->IDLabel = new QLabel{ "ID: " };
	this->updateWindowLayout->addWidget(this->IDLabel, 0, 0);
	this->IDLine = new QLineEdit{};
	this->updateWindowLayout->addWidget(this->IDLine, 0, 1);

	this->measurementLabel = new QLabel{ "Measurement: " };
	this->updateWindowLayout->addWidget(this->measurementLabel, 1, 0);
	this->measurementLine = new QLineEdit{};
	this->updateWindowLayout->addWidget(this->measurementLine, 1, 1);

	this->imageClarityLabel = new QLabel{ "Image clarity: " };
	this->updateWindowLayout->addWidget(this->imageClarityLabel, 2, 0);
	this->imageClarityLine = new QLineEdit{};
	this->updateWindowLayout->addWidget(this->imageClarityLine, 2, 1);

	this->quantityLabel = new QLabel{ "Quantity: " };
	this->updateWindowLayout->addWidget(this->quantityLabel, 3, 0);
	this->quantityLine = new QLineEdit{};
	this->updateWindowLayout->addWidget(this->quantityLine, 3, 1);

	this->photographLabel = new QLabel{ "Photograph: " };
	this->updateWindowLayout->addWidget(this->photographLabel, 4, 0);
	this->photographLine = new QLineEdit{};
	this->updateWindowLayout->addWidget(this->photographLine, 4, 1);

	this->updateButtonMeniu = new QPushButton{ "Update" };
	this->updateWindowLayout->addWidget(this->updateButtonMeniu, 6, 2);

	//connecting the button
	connect(this->updateButtonMeniu, &QPushButton::clicked, this, &SeniorClearanceLevel::updateEvidence);

	this->updateWindow->show();
}

void SeniorClearanceLevel::addEvidence()
{

	std::string constArray = this->IDLine->text().toStdString();
	char* ID = new char[constArray.length() + 1];
	strcpy(ID, constArray.c_str());
	if (strlen(ID) == 0) {
		this->addError->showMessage(QString::fromLocal8Bit("Please insert the ID!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}

	constArray = this->measurementLine->text().toStdString();
	char* measurement = new char[constArray.length() + 1];
	strcpy(measurement, constArray.c_str());
	if (strlen(measurement) == 0) {
		this->addError->showMessage(QString::fromLocal8Bit("Please insert the measurements!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}

	constArray = this->imageClarityLine->text().toStdString();
	char* imageClarity = new char[constArray.length() + 1];
	strcpy(imageClarity, constArray.c_str());
	if (strlen(imageClarity) == 0) {
		this->addError->showMessage(QString::fromLocal8Bit("Please insert the image clarity level!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}
	if (atof(imageClarity) == 0) {
		this->addError->showMessage(QString::fromLocal8Bit("Invalid argument! Image clarity must be a number!"), QString::fromLocal8Bit("Invalid data"));
		return;
	}
	float imageClarityLevel = atof(imageClarity);

	constArray = this->quantityLine->text().toStdString();
	char* quantityChar = new char[constArray.length() + 1];
	strcpy(quantityChar, constArray.c_str());
	if (strlen(quantityChar) == 0) {
		this->addError->showMessage(QString::fromLocal8Bit("Please insert the quantity!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}
	if (atoi(quantityChar) == 0) {
		this->addError->showMessage(QString::fromLocal8Bit("Invalid argument! Quantity must be a number!"), QString::fromLocal8Bit("Invalid data"));
		return;
	}
	int quantity = atoi(quantityChar);

	constArray = this->photographLine->text().toStdString();
	char* photograph = new char[constArray.length() + 1];
	strcpy(photograph, constArray.c_str());
	if (strlen(photograph) == 0) {
		this->addError->showMessage(QString::fromLocal8Bit("Please insert the photograph!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}

	Evidence* evidenceToAdd = new Evidence{ ID, measurement, imageClarityLevel, quantity, photograph };
	try {
		this->evidences->add(evidenceToAdd);
		this->addError->showMessage(QString::fromLocal8Bit("Element added successfully!"), QString::fromLocal8Bit("Success"));
		this->addWindow->close();
		this->displayEvidences();
		if (this->index < this->actions.size() - 1)
		{
			this->actions.erase(this->actions.begin() + this->index, this->actions.end());
			this->index--;
		}
		UndoAdd* action = new UndoAdd{ evidenceToAdd, this->evidences };
		this->index++;
		this->actions.push_back(action);
	}
	catch (RepoError& error) {
		this->addError->showMessage(QString::fromLocal8Bit(error.what()), QString::fromLocal8Bit("RepoError"));
	}
}

void SeniorClearanceLevel::removeEvidence()
{
	std::string constArray = this->IDLine->text().toStdString();
	char* ID = new char[constArray.length() + 1];
	strcpy(ID, constArray.c_str());
	if (strlen(ID) == 0) {
		this->removeError->showMessage(QString::fromLocal8Bit("Please insert the ID!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}
	int position = this->evidences->search(ID);
	if (position == -1) {
		this->removeError->showMessage(QString::fromLocal8Bit("Invalid ID! This evidence does not exist!"), QString::fromLocal8Bit("Invalid data"));
		this->removeWindow->close();
		return;
	}
	Evidence* evidenceToDelete = this->evidences->getElement(position);
	this->evidences->remove(evidenceToDelete);
	this->removeWindow->close();
	this->removeError->showMessage(QString::fromLocal8Bit("Evidence removed successfully!"), QString::fromLocal8Bit("Success"));
	this->displayEvidences();
	if (this->index < this->actions.size() - 1)
	{
		this->actions.erase(this->actions.begin() + this->index, this->actions.end());
		this->index--;
	}
	this->index++;
	UndoRemove* action = new UndoRemove { evidenceToDelete, this->evidences };
	this->actions.push_back(action);
}

void SeniorClearanceLevel::updateEvidence()
{
	std::string constArray = this->IDLine->text().toStdString();
	char* ID = new char[constArray.length() + 1];
	strcpy(ID, constArray.c_str());
	if (strlen(ID) == 0) {
		this->updateError->showMessage(QString::fromLocal8Bit("Please insert the ID!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}

	constArray = this->measurementLine->text().toStdString();
	char* measurement = new char[constArray.length() + 1];
	strcpy(measurement, constArray.c_str());
	if (strlen(measurement) == 0) {
		this->updateError->showMessage(QString::fromLocal8Bit("Please insert the measurements!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}

	constArray = this->imageClarityLine->text().toStdString();
	char* imageClarity = new char[constArray.length() + 1];
	strcpy(imageClarity, constArray.c_str());
	if (strlen(imageClarity) == 0) {
		this->updateError->showMessage(QString::fromLocal8Bit("Please insert the image clarity level!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}
	if (atof(imageClarity) == 0) {
		this->updateError->showMessage(QString::fromLocal8Bit("Invalid argument! Image clarity must be a number!"), QString::fromLocal8Bit("Invalid data"));
		return;
	}
	float imageClarityLevel = atof(imageClarity);

	constArray = this->quantityLine->text().toStdString();
	char* quantityChar = new char[constArray.length() + 1];
	strcpy(quantityChar, constArray.c_str());
	if (strlen(quantityChar) == 0) {
		this->updateError->showMessage(QString::fromLocal8Bit("Please insert the quantity!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}
	if (atoi(quantityChar) == 0) {
		this->updateError->showMessage(QString::fromLocal8Bit("Invalid argument! Quantity must be a number!"), QString::fromLocal8Bit("Invalid data"));
		return;
	}
	int quantity = atoi(quantityChar);

	constArray = this->photographLine->text().toStdString();
	char* photograph = new char[constArray.length() + 1];
	strcpy(photograph, constArray.c_str());
	if (strlen(photograph) == 0) {
		this->updateError->showMessage(QString::fromLocal8Bit("Please insert the photograph!"), QString::fromLocal8Bit("Incomplete data"));
		return;
	}

	Evidence* evidenceToUpdate = new Evidence{ ID, measurement, imageClarityLevel, quantity, photograph };
	try {
		Evidence* evidence = this->evidences->getElement(this->evidences->search(evidenceToUpdate->getId()));
		this->evidences->update(evidenceToUpdate);
		this->updateError->showMessage(QString::fromLocal8Bit("Element updated successfully!"), QString::fromLocal8Bit("Success"));
		this->updateWindow->close();
		this->displayEvidences();
		if (this->index < this->actions.size() - 1)
		{
			this->actions.erase(this->actions.begin() + this->index, this->actions.end());
			this->index--;
		}
		UndoUpdate* action = new UndoUpdate{ evidence, evidenceToUpdate, this->evidences };
		this->index++;
		this->actions.push_back(action);
	}
	catch (RepoError& error) {
		this->updateWindow->close();
		this->updateError->showMessage(QString::fromLocal8Bit(error.what()), QString::fromLocal8Bit("RepoError"));
	}
}

void SeniorClearanceLevel::keyPressEvent(QKeyEvent *event)
{
	QWidget::keyPressEvent(event);
	QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
	if (keyEvent->matches(QKeySequence::Undo)) {
		qDebug() << "CTRL-Z Key pressed" << keyEvent->key();
		this->undo();
	}
	else {
		if(keyEvent->matches(QKeySequence::Redo)) {
			qDebug() << "CTRL-Y Key pressed" << keyEvent->key();
			this->redo();
		}
	}
}

void SeniorClearanceLevel::undo()
{
	if (this->index != -1) {
		this->actions[index]->executeUndo();
		this->index--;
		this->displayEvidences();
	}
	else {
		this->addError = new QErrorMessage{};
		this->addError->showMessage(QString::fromLocal8Bit("No undos possible"));
	}
}

void SeniorClearanceLevel::redo()
{
	//weird behaviour when you perform one operation, undo it and then you want to redo it, i.e. doesn't redo it
	qDebug() << "redo index " << this ->index<< this->actions.size() - 1;
	if (this->index>=-1 && this->index<=this->actions.size()-1 && this->actions.size()!=0) {
		this->actions[this->index+1]->executeRedo();
		this->index++;
		this->displayEvidences();
	}
	else {
		this->addError = new QErrorMessage{};
		this->addError->showMessage(QString::fromLocal8Bit("No redos possible"));
	}

}




