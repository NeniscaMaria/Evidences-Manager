#pragma once
#include "Controller.h"
class UndoAction {
public:
	virtual ~UndoAction() {};
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class UndoAdd : public UndoAction{
private:
	Evidence* addedEvidence;
	Controller<Evidence>* repositoryEvidences;
	bool undo;
	bool redo;
public:
	UndoAdd(Evidence*, Controller<Evidence>*);
	void executeUndo();
	void executeRedo();
};

class UndoRemove : public UndoAction {
private:
	Evidence* removedEvidence;
	Controller<Evidence>* repositoryEvidences;
	bool undo;
	bool redo;
public:
	UndoRemove(Evidence*, Controller<Evidence>*);
	void executeUndo();
	void executeRedo();
};

class UndoUpdate : public UndoAction {
private:
	Evidence* updatedEvidence;
	Evidence* evidenceUpdatedWith;
	Controller<Evidence>* repositoryEvidences;
	bool undo;
	bool redo;
public:
	UndoUpdate(Evidence*,Evidence*, Controller<Evidence>*);
	void executeUndo();
	void executeRedo();
};

