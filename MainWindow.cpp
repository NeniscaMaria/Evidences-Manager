#include "MainWindow.h"

MainWindow::MainWindow(Repository<Evidence>* repository,Repository<Evidence>* savedRepository, int storage) {

	this->repo = repository;
	this->savedRepo = savedRepository;
	this->fileLocation = NULL;
	this->mylistLocation = NULL;
	this->storageChoice = storage;
	if (this->storageChoice == 1) {
		this->initFileMeniu();
	}
	else {
		this->initiateMemoryControllers();
		this->openMainWindow();
	}
}
MainWindow::MainWindow(QWidget * parent)
{
	this->initFileMeniu();
}

char* MainWindow::getFileType(char* command) {
	char* fileType, *parameter;
	fileType = new char[10];
	parameter = strtok(command, ".");
	while (parameter != NULL) {
		strcpy(fileType, parameter);
		parameter = strtok(NULL, ".");
	}
	return fileType;
}
void MainWindow::displaySeniorClearanceLevel()
{
	this->mainWindow->close();
	this->seniorClearanceLevelMeniu = new SeniorClearanceLevel{this->evidences,this->savedEvidences};
	this->seniorClearanceLevelMeniu->show();
}

void MainWindow::displayStandardClearanceLevel()
{
	this->mainWindow->close();
	this->standardClearanceLevelMeniu = new StandardClearanceLevel{this->savedEvidences,this->evidences};
	//this->standardClearanceLevelMeniu->show();
}

void MainWindow::initFileMeniu() {
	//filePath meniu
	this->errorWindowFiles = new QErrorMessage{};
	this->window = new QWidget{};
	this->window->setWindowTitle("Welcome!");
	this->mainLayout = new QVBoxLayout{};
	this->window->setLayout(this->mainLayout);

	this->topBox = new QWidget{};
	this->topLayout = new QHBoxLayout{};
	this->topBox->setLayout(this->topLayout);

	this->bottomBox = new QWidget{};
	this->bottomLayout = new QVBoxLayout{};
	this->bottomBox->setLayout(this->bottomLayout);

	this->mainLayout->addWidget(this->topBox);
	this->mainLayout->addWidget(this->bottomBox);

	this->myfileWidget = new QWidget{};
	this->myfileLayout = new QHBoxLayout{};
	this->myfileWidget->setLayout(this->myfileLayout);
	this->bottomLayout->addWidget(this->myfileWidget);

	this->mainFilePath = new QLabel{ "            File path: " };
	this->topLayout->addWidget(this->mainFilePath);
	this->mainLine = new QLineEdit{};
	this->topLayout->addWidget(this->mainLine);

	this->mylistPath = new QLabel{ "mylist file path: " };
	this->myfileLayout->addWidget(this->mylistPath);
	this->mylistLine = new QLineEdit{};
	this->myfileLayout->addWidget(this->mylistLine);

	this->anotherWidget = new QWidget{};
	this->anotherLayout = new QHBoxLayout{};
	this->anotherWidget->setLayout(this->anotherLayout);
	this->bottomLayout->addWidget(this->anotherWidget);
	this->saveFileButton = new QPushButton{ "&Save" };
	this->anotherLayout->addWidget(this->saveFileButton);

	//connecting buttons
	connect(this->saveFileButton, &QPushButton::clicked, this, &MainWindow::saveFilePaths);

	this->window->show();
}
void MainWindow::saveFilePaths()
{
	std::string constArray = this->mainLine->text().toStdString();
	this->fileLocation = new char[constArray.length() + 1];
	strcpy(this->fileLocation, constArray.c_str());
	std::string array = this->mylistLine->text().toStdString().c_str();
	this->mylistLocation = new char[array.length() + 1];
	strcpy(this->mylistLocation, array.c_str());
	if (strlen(this->fileLocation) != 0 && strlen(this->mylistLocation) != 0) {
		this->window->close();
		this->initiateFileControllers();
	}
	else {
		this->errorWindowFiles->showMessage(QString::fromLocal8Bit("Please insert both files!"));
	}
}

void MainWindow :: addValuesInEvidences() {
	ifstream file;
	file.open("dataInitialization.txt", ios::in);
	Evidence evidenceFromFile{ "...........","..................",2.0,3,"................................................................" };//just some initialization data
	if (file.is_open()) {
		while (file >> evidenceFromFile) {
			Evidence* evidence = new Evidence{ evidenceFromFile.getId(),evidenceFromFile.getMeasurement(),evidenceFromFile.getImageClarityLevel(),evidenceFromFile.getQuantity(),evidenceFromFile.getPhotograph() };;
			try {
				this->evidences->add(evidence);
			}
			catch (ExistingElement) {};
		}
		file.close();
	}
}

void MainWindow::initiateFileControllers(){
	this->evidences = new ControllerFile<Evidence>{ this->repo,this->fileLocation };
	char* copyLocation = new char[strlen(this->mylistLocation) + 1];
	strcpy(copyLocation, this->mylistLocation);
	char* fileType = this->getFileType(copyLocation);
	if (strcmp(fileType, "txt") == 0)
		this->savedEvidences = new ControllerFile<Evidence>(this->savedRepo, this->mylistLocation);
	else
		if (strcmp(fileType, "csv") == 0)
			this->savedEvidences = new ControllerFile<Evidence>(this->savedRepo, this->mylistLocation);
		else if (strcmp(fileType, "html") == 0)
 			this->savedEvidences = new ControllerHTML<Evidence>(this->savedRepo, this->mylistLocation);
	this->addValuesInEvidences();
	delete[] fileType;
	delete[] copyLocation;
	this->openMainWindow();
}

void MainWindow::initiateMemoryControllers()
{
	this->evidences = new Controller<Evidence>{this->repo};
	this->savedEvidences = new Controller<Evidence>{ this->savedRepo };
	this->addValuesInEvidences();
}

void MainWindow::openMainWindow() {
	this->mainWindow = new QWidget{};
	this->mainWindow->setWindowTitle("Welcome!"); // setting the title of the window

	this->mainLayout = new QVBoxLayout{};
	this->mainWindow->setLayout(this->mainLayout);

	this->seniorClearanceButton = new QPushButton{ "&Senior clearance level" };
	this->mainLayout->addWidget(this->seniorClearanceButton);

	this->standardClearanceButton = new QPushButton{ "&Standard clearance level" };
	this->mainLayout->addWidget(this->standardClearanceButton);

	//this->displayMyList = new QPushButton{ "&Show evidences from mylist" };
	//this->mainLayout->addWidget(this->displayMyList);

	
	//connecting the buttons
	connect(this->standardClearanceButton, &QPushButton::clicked, this, &MainWindow::displayStandardClearanceLevel);
	connect(this->seniorClearanceButton, &QPushButton::clicked, this, &MainWindow::displaySeniorClearanceLevel);
	this->myListTable = new MyListModel{ this->savedRepo };
	this->myListTable->show();
	this->mainWindow->show();
}
