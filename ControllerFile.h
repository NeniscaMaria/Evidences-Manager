#pragma once
#include "Controller.h"
#include <iostream>
#include <fstream>

using namespace std;

template <typename genericType>
class ControllerFile : public Controller<genericType> {
private:
	char* fileLocation;
public:
	ControllerFile(Repository<genericType>*, char*);
	ControllerFile(Repository<genericType>*, char*, std::vector<genericType*>);
	~ControllerFile();
	void readFromFile();
	void writeToFile();
	void add(genericType*) override;
	void remove(genericType*) override;
	void update(genericType*) override;
	genericType* getPointer(genericType&);

};

template <typename genericType>
ControllerFile<genericType>::ControllerFile(Repository<genericType>* repo, char* location, std::vector<genericType*> elems) {
	this->elements = repo;
	this->elements->setElements(elems);
	this->fileLocation = new char[strlen(location) + 1];
	strcpy(this->fileLocation, location);
	this->writeToFile();
}
template <typename genericType>
genericType* ControllerFile< genericType>::getPointer(genericType& evidenceFromFile) {
	genericType* evidence = new genericType{ evidenceFromFile.getId(),evidenceFromFile.getMeasurement(),evidenceFromFile.getImageClarityLevel(),evidenceFromFile.getQuantity(),evidenceFromFile.getPhotograph() };
	return evidence;
}

template <typename genericType>
void ControllerFile<genericType>::readFromFile() {
	/*
	This function reads all elements from a file and adds them to the repository-
	THROWS:ExistingElement if there is a duplicate element in the file
	*/
	ifstream file;
	file.open(this->fileLocation, ios::in);
	Evidence input{"hello","hello",2.0,3,"hello"};//just some initialization data
	if (file.is_open()) {
		while (file >> input) {
			Evidence* evidence = getPointer(input);
			Controller<genericType>::add(evidence);
		}
		file.close();
	}
}

template <typename genericType>
void ControllerFile<genericType>::writeToFile() {
	/*
	This function writes the content of the repository to the file
	*/
	ofstream file{ this->fileLocation, ios::out };
	for (auto evidence : this->elements->getElements())
	{
		file << evidence;
	}
	file.close();
}

template <typename genericType>
ControllerFile<genericType>::ControllerFile(Repository<genericType>* repo, char* location) {
	this->elements = repo;
	this->fileLocation = new char[strlen(location) + 1];
	strcpy(this->fileLocation, location);
	this->readFromFile();
}

template <typename genericType>
ControllerFile<genericType>::~ControllerFile() {
	//destructor
	delete[] fileLocation;
}

template <typename genericType>
void ControllerFile<genericType>::add(genericType* element) {
	/*
	This function adds a new element to the repository
	INPUT:element=genericType*
	POSTCOND:the element was aded to the repository and written to the file as well
	THROWS:ExistingElement if the element already existed
	*/
	Controller<genericType>::add(element);
	this->writeToFile();
}

template <typename genericType>
void ControllerFile<genericType>::remove(genericType* element) {/*
	This function removes an element from the repository
	POSTCOND:the element was removed and the new repository is written in the file
	THROWS:InexistingElement if the element does not exist
	*/
	Controller<genericType>::remove(element);
	this->writeToFile();
}

template <typename genericType>
void ControllerFile<genericType>::update(genericType* element) {
	/*
	This function updates an element from the repository
	POSTCOND:the element was updated and the new repository is written in the file
	THROWS:InexistingElement- if the element that we want to update does not exist
	*/
	Controller<genericType>::update(element);
	this->writeToFile();
}

