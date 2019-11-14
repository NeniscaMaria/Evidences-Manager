#pragma once
#include "StandardClearanceLevelGUI.h"
#include "Repository.h"
#include"Controller.h"
#include"ControllerFile.h"
#include "ControllerHTML.h"
#include "MyListModel.h"

class MainWindow : public QWidget {
	Q_OBJECT
public:
	MyListModel* myListTable;
	//for the filePath meniu
	QWidget* window;
	QVBoxLayout* mainLayout;
	QWidget* topBox;
	QHBoxLayout* topLayout;
	QWidget* bottomBox;
	QVBoxLayout* bottomLayout;
	QWidget* myfileWidget;
	QHBoxLayout* myfileLayout;
	QWidget* anotherWidget;
	QHBoxLayout* anotherLayout;
	QLabel* mainFilePath;
	QLineEdit* mainLine;
	QLabel* mylistPath;
	QLineEdit* mylistLine;
	QPushButton* saveFileButton;
	QPushButton* displayMyList;

	QErrorMessage* errorWindowFiles;

	QWidget* mainWindow;
	QPushButton* standardClearanceButton;
	QPushButton* seniorClearanceButton;
	StandardClearanceLevel* standardClearanceLevelMeniu;
	SeniorClearanceLevel* seniorClearanceLevelMeniu;
	
	Repository<Evidence>* repo;
	Repository< Evidence > * savedRepo;
	Controller<Evidence>* evidences;
	Controller<Evidence>* savedEvidences;
	char* fileLocation;
	char* mylistLocation;
	int storageChoice;

	MainWindow(Repository<Evidence>*,Repository<Evidence>*,int);
	MainWindow(QWidget * parent = Q_NULLPTR);
	~MainWindow() {};
	
private:
	void initFileMeniu();
	void displaySeniorClearanceLevel();
	void displayStandardClearanceLevel();
	char* getFileType(char*);
	void saveFilePaths();
	void openMainWindow();
	void initiateFileControllers();
	void initiateMemoryControllers();
	void addValuesInEvidences();
};