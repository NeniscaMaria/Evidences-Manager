#pragma once
#include "Controller.h"

template <typename genericType>
class ControllerHTML : public Controller<genericType> {
private:
	char* fileLocation;
public:
	ControllerHTML(Repository<genericType>*, char*);
	ControllerHTML(Repository<genericType>*, char*, std::vector<genericType*>);
	~ControllerHTML();
	//void readFromFile();
	void writeToFile();
	void add(genericType*) override;
	void remove(genericType*) override;
	void update(genericType*) override;
};
template <typename genericType>
ControllerHTML<genericType>::ControllerHTML(Repository<genericType>* repo, char* location, std::vector<genericType*> elems) {
	this->elements = repo;
	this->elements->setElements(elems);
	this->fileLocation = new char[strlen(location) + 1];
	strcpy(this->fileLocation, location);
	this->writeToFile();
}
template <typename genericType>
ControllerHTML<genericType>::ControllerHTML(Repository<genericType>* repo, char* location) {
	this->elements = repo;
	this->fileLocation = new char[strlen(location) + 1];
	strcpy(this->fileLocation, location);
}

template <typename genericType>
ControllerHTML<genericType>::~ControllerHTML() {
	delete[] fileLocation;
}

template <typename genericType>
void ControllerHTML<genericType>::writeToFile() {
	ofstream file{ this->fileLocation, ios::out };
	file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Saved evidences</title>\n</head>\n<body>\n<table border=" << '"' << "1" << '"' << ">\n <tr>\n<td>ID</td>\n<td>Measurement</td>\n<td>Image clarity level</td>\n<td>Quantity</td>\n<td>Photograph</td>\n";
	for (auto evidence : this->elements->getElements())
	{
		file << "</tr>\n<tr>\n<td>" << evidence->getId() << "</td>\n<td>" << evidence->getMeasurement() << "</td>\n<td>" << evidence->getImageClarityLevel() << "</td>\n<td>" << evidence->getQuantity() << "</td>\n<td>" << evidence->getPhotograph() << "</td>\n</tr>\n<tr>\n";
	}
	file << "</table>\n</body>\n</html> ";
	file.close();
}

template <typename genericType>
void ControllerHTML<genericType>::add(genericType* element) {
	Controller<genericType>::add(element);
	this->writeToFile();
}

template <typename genericType>
void ControllerHTML<genericType>::remove(genericType* element) {
	Controller<genericType>::remove(element);
	this->writeToFile();
}

template <typename genericType>
void ControllerHTML<genericType>::update(genericType* element) {
	Controller<genericType>::update(element);
	this->writeToFile();
}

