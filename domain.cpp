#pragma once
#include "domain.h"

Evidence::Evidence(char* idFromUser, char* measurementFromUser, double imageClarityFromUser, int quantityFromUser, char* photographFromUser) {
	//constructor
	this->ID = new char[strlen(idFromUser) + 1];
	strcpy(this->ID, idFromUser);
	this->measurement = new char[strlen(measurementFromUser) + 1];
	strcpy(this->measurement, measurementFromUser);
	this->imageClarityLevel = imageClarityFromUser;
	this->quantity = quantityFromUser;
	this->photograph = new char[strlen(photographFromUser) + 1];
	strcpy(this->photograph, photographFromUser);
}

Evidence::Evidence() {
	//second constructor
}
Evidence* Evidence::operator=(Evidence* evidence) {
	//"copy constructor"
	char *ID = new char[strlen(evidence->ID) + 1];
	strcpy(ID, evidence->ID);
	char* measurement = new char[strlen(evidence->measurement) + 1];
	strcpy(measurement, evidence->measurement);
	double imageClarityLevel = evidence->imageClarityLevel;
	int quantity = evidence->quantity;
	char* photograph = new char[strlen(evidence->photograph) + 1];
	strcpy(this->photograph, evidence->photograph);
	strcpy(this->ID, ID);
	strcpy(this->measurement, measurement);
	this->imageClarityLevel = imageClarityLevel;
	this->quantity = quantity;
	strcpy(this->photograph, photograph);
	return this;
}
Evidence::~Evidence() {
	//destructor
	if(photograph!=NULL)
		delete[] photograph;
	if(measurement!=NULL)
		delete[] measurement;
	if(ID!=NULL)
		delete[] ID;
}

bool Evidence::operator==(Evidence* evidence) {
	//defining the equality of 2 objects Evidence
	return strcmp(this->ID, evidence->ID) == 0;
}

std::istream& operator>> (std::istream& is, Evidence& evid)
{
	std::string line;
	getline(is, line);
	char* lineArray = new char[40];
	char* copyLineArray = new char[40];
	strcpy(lineArray, line.c_str());
	strcpy(copyLineArray, line.c_str());
	std::vector<char*> tokens;
	char* token;
	token = strtok(lineArray, ",");
	while (token != NULL) {
		tokens.push_back(token);
		token = strtok(NULL, ",");
	}
	if (tokens.size() != 1) {
		if (tokens.size() != 5)
			return is;
		evid.ID = new char[strlen(tokens[0]) + 1];
		strcpy(evid.ID, tokens[0]);
		evid.measurement = new char[strlen(tokens[1]) + 1];
		strcpy(evid.measurement, tokens[1]);
		evid.imageClarityLevel = atof(tokens[2]);
		evid.quantity = atoi(tokens[3]);
		evid.photograph = new char[strlen(tokens[4]) + 1];
		strcpy(evid.photograph, tokens[4]);
		return is;
	}
	else {
		tokens.clear();
		char* token;
		token = strtok(copyLineArray, " ");
		while (token != NULL) {
			tokens.push_back(token);
			token = strtok(NULL, " ");
		}
		if (tokens.size() != 5)
			return is;
		evid.ID = new char[strlen(tokens[0]) + 1];
		strcpy(evid.ID, tokens[0]);
		evid.measurement = new char[strlen(tokens[1]) + 1];
		strcpy(evid.measurement, tokens[1]);
		evid.imageClarityLevel = atof(tokens[2]);
		evid.quantity = atoi(tokens[3]);
		evid.photograph = new char[strlen(tokens[4]) + 1];
		strcpy(evid.photograph, tokens[4]);
		return is;
	}
}

std::ostream & operator<<(std::ostream & os, const Evidence* evid)
{
	os << evid->getId() << "," << evid->getMeasurement() << "," << evid->getImageClarityLevel() << "," << evid->getQuantity() << "," << evid->getPhotograph() << "\n";
	return os;
}
