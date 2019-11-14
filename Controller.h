#pragma once
#include "Repository.h"

template <typename genericType>
class Controller {
	friend class Repository<genericType>;
public:
	Repository<genericType>* elements;
public:
	Controller(Repository<genericType>*);//constructor
	Controller() {};
	~Controller();//destructor
	virtual void add(genericType*);
	virtual void remove(genericType*);
	virtual void update(genericType*);
	virtual RepositoryIterator<genericType> list();
	virtual int size();
	virtual int search(char* ID);
	virtual genericType* getElement(int);
	void clearEvidences();
};

template <typename genericType>
Controller<genericType>::Controller(Repository<genericType>* repositoryEvidences) {
	//constructor
	this->elements = repositoryEvidences;
}

template <typename genericType>
Controller<genericType>::~Controller() {
	//destructor
	delete elements;
}

template <typename genericType>
genericType* Controller< genericType>::getElement(int position) {
	/*
	This function gets an element from a position
	INPUT:position-integer
	PRECOND:position must be valid
	POSTCOND:-
	OUTPUT: the element from the given position
	THROWS:InvalidPosition if the position is invalid
	*/
	return this->elements->getElement(position);
}

template <typename genericType>
void Controller<genericType>::add(genericType* evidence) {
	/*
	This function adds a new evidence in the repository
	INPUT:evidence=genericType*
	PRECOND:the evidence must not be in the repository
	POSTCOND:-
	OUTPUT:-
	THROWS:ExistingElement if the element already exists
	*/
	if (this->size() != 0 && this->search(evidence->getId()) != -1)
		throw ExistingElement();
	this->elements->addToEnd(evidence);
}

template <typename genericType>
void Controller<genericType>::remove(genericType* evidence) {
	//removes an evidence from the repository
	//HROWS:InexistingElement if the element does not exist
	this->elements->removeElement(evidence);
}

template <typename genericType>
void  Controller< genericType >::update(genericType* evidence) {
	/*
	This function updates an evidence
	INPUT:evidence=genericType*
	PRECOND:the given evidence is the evidence that will be put on the position of the old one
	POSTCOND:-
	OUTPUT:-
	THROWS:InexistingElement if there is no evidence with the same ID as the given evidence
	*/
	int position = this->elements->search(evidence->getId());
	if (position == -1) {
		throw InexistingElement();
	}
	this->elements->setElement(position, evidence);
}

template <typename genericType>
RepositoryIterator< genericType >  Controller< genericType >::list() {
	//returns iterator to the elements of the repository
	return this->elements->iterator();
}


template <typename genericType>
int Controller< genericType>::search(char* ID) {
	//searches a given evidence in the repository
	return this->elements->search(ID);
}

template <typename genericType>
int Controller< genericType>::size() {
	//gets the size of the repository
	return this->elements->size();
}

template <typename genericType>
void Controller< genericType>::clearEvidences() {
	this->elements->clearRepository();
}


