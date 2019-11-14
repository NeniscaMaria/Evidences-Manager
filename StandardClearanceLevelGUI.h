
#pragma once
#include "Controller.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include "SeniorClearanceLevelGUI.h"
#include <qerrormessage.h>
class StandardClearanceLevel : public QWidget
{
	Q_OBJECT
public:
	QErrorMessage* errorBox;
	QWidget* window;
	QVBoxLayout* mainLayout;
	QWidget* topLayoutBox;
	QHBoxLayout* topLayout;
	QWidget* topGridLayoutBox;
	QGridLayout* topGridLayout;
	QLineEdit* measurementTextBox;
	QLabel* measurementLabel;
	QLineEdit* quantityTextBox;
	QLabel* quantityLabel;
	QPushButton* listButton;
	QWidget* bottomGridLayoutBox;
	QGridLayout* bottomGridLayout;

	QLabel* displayEvidence;

	QLineEdit* idLine;
	QPushButton* saveButton;
	QPushButton* nextButton;
	QWidget* bottomLayoutBox;
	QVBoxLayout* bottomLayout;
	QLabel* savedEvidencesLabel;
	QListWidget* listOfEvidences;
	QPushButton* changeMode;
	SeniorClearanceLevel* seniorClearanceLevelMeniu;

	Controller<Evidence>* savedEvidences;
	Controller<Evidence>* evidences;

	Controller<Evidence>* repositoryEvidencesWithTheseCharacteristics;

	int evidencesIterated;
	int messageFlag;
	StandardClearanceLevel(QWidget * parent = Q_NULLPTR);
	StandardClearanceLevel(Controller<Evidence>* savedEvidences, Controller<Evidence>*);
	~StandardClearanceLevel() {};
	
private:
	void initGUI();
	void switchModes();

	Controller<Evidence>* getElementsMeasurementAndQuantity(char*, int);
	void list();
	void showSavedEvidences();
	void saveEvidence();
	void showNextEvidence();
	void displayNextEvidence(Evidence*);
	void getToNext(RepositoryIterator<Evidence>);
};

