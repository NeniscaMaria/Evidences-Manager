#include "UndoRedo.h"

UndoAdd::UndoAdd(Evidence* evid, Controller<Evidence>* repo)
{
	this->addedEvidence = evid;
	this->repositoryEvidences = repo;
	this->undo = true;
	this->redo = true;
}

void UndoAdd::executeUndo()
{
	if (this->undo) {
		this->repositoryEvidences->remove(this->addedEvidence);
		this->undo = false;
		this->redo = true;
	}
}

void UndoAdd::executeRedo()
{
	if (this->redo) {
		this->repositoryEvidences->add(this->addedEvidence);
		this->undo = true;
		this->redo = false;
	}
}

UndoRemove::UndoRemove(Evidence* evid,  Controller<Evidence>* repo)
{
	this->removedEvidence = evid;
	this->repositoryEvidences = repo;
	this->undo = true;
	this->redo = true;
}

void UndoRemove::executeUndo()
{
	if (this->undo) {
		this->repositoryEvidences->add(this->removedEvidence);
		this->undo = false;
		this->redo = true;
	}
}

void UndoRemove::executeRedo()
{
	if (this->redo) {
		this->repositoryEvidences->remove(this->removedEvidence);
		this->undo = true;
		this->redo = false;
	}
}

UndoUpdate::UndoUpdate(Evidence * evid, Evidence* ev, Controller<Evidence>* repo)
{
	this->updatedEvidence = evid;
	this->evidenceUpdatedWith = ev;
	this->repositoryEvidences = repo;
	this->undo = true;
}

void UndoUpdate::executeUndo()
{
	if (this->undo) {
		this->repositoryEvidences->update(this->updatedEvidence);
		this->undo = false;
		this->redo = true;
	}
}

void UndoUpdate::executeRedo()
{
	if (this->redo) {
		this->repositoryEvidences->update(this->evidenceUpdatedWith);
		this->undo = true;
		this->redo = false;
	}
}
