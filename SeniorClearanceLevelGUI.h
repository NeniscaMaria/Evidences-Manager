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
#include <QGridLayout>
#include <vector>
#include <qerrormessage.h>
#include "UndoRedo.h"
class StandardClearanceLevel;

class SeniorClearanceLevel : public QWidget {
	Q_OBJECT
public:

	bool action;
	QErrorMessage* addError;
	QErrorMessage* removeError;
	QErrorMessage* updateError;

	//instances of the main window
	QVBoxLayout* mainLayout;
	QListWidget* listEvidences;
	QWidget* gridLayoutBox;
	QGridLayout* gridLayout;
	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;
	QPushButton* undoButton;
	QPushButton* redoButton;
	QPushButton* standardClearanceLevelButton;
	StandardClearanceLevel* standardClearanceLevelMeniu;
	
	//instances of the add meniu
	QWidget* addWindow;
	QGridLayout* addWindowLayout;
	QLabel* IDLabel;
	QLineEdit* IDLine;
	QLabel* measurementLabel;
	QLineEdit* measurementLine;
	QLabel* imageClarityLabel;
	QLineEdit* imageClarityLine;
	QLabel* quantityLabel;
	QLineEdit* quantityLine;
	QLabel* photographLabel;
	QLineEdit* photographLine;
	QPushButton* saveButton;

	//instances of the remove meniu
	QWidget* removeWindow;
	QGridLayout* removeWindowLayout;
	QPushButton* deleteButton;

	//instances of the update meniu
	QWidget* updateWindow;
	QGridLayout* updateWindowLayout;
	QPushButton* updateButtonMeniu;

	//instances for the graphic representation of data

	std::vector<UndoAction*> actions;
	int index;
	Controller<Evidence>* evidences;
	Controller<Evidence>* savedEvidences;
	SeniorClearanceLevel(Controller<Evidence>*, Controller<Evidence>*);
	~SeniorClearanceLevel() {};
public:
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
	void initGUI();
	void displayEvidences();
	void switchModes();
	void displayAddMeniu();
	void displayRemoveMeniu();
	void displayUpdateMeniu();

	void addEvidence();
	void removeEvidence();
	void updateEvidence();

	void undo();
	void redo();
};

