#pragma once
#include "DAIterator.h"
#include "domain.h"

class RepoError : public std::exception {
public:
	virtual const char* what() const throw() = 0;
};

class InexistingElement :public RepoError {
public:
	virtual const char* what() const throw()
	{
		return "There is no such element!\n";
	}
};

class ExistingElement :public RepoError {
public:
	virtual const char* what() const throw()
	{
		return "This element already exists!\n";
	}
};

class InvalidPosition :public RepoError {
public:
	virtual const char* what() const throw()
	{
		return "That is an invalid position!\n";
	}
};

template <typename genericType>

class Repository {
	friend class RepositoryIterator<genericType>;
public:
	std::vector<genericType*> elements;
public:
	Repository();
	~Repository();
	int size() const { return this->elements.size(); }
	genericType* getElement(int) const;
	void setElement(int, genericType*);
	void addToEnd(genericType*);
	void addToPosition(int, genericType*);
	void remove(int);
	void removeElement(genericType*);
	RepositoryIterator<genericType> iterator() const;
	int search(char*);
	inline std::vector<genericType*> getElements() { return this->elements; }
	void setElements(std::vector<genericType*>);
	void updateEvidence(int,genericType* evid);
private:
	void clearRepository();

};

template <typename genericType>
Repository<genericType>::Repository() {
}
template <typename genericType>
void Repository<genericType>::setElements(std::vector<genericType*> elems) {
	this->elements.clear();
	this->elements = elems;
}
template<typename genericType>
inline void Repository<genericType>::updateEvidence(int position,genericType * evidence)
{
	this->setElement(position, evidence);
}
template <typename genericType>
genericType* Repository<genericType>::getElement(int positionFromUser) const {
	/*
	This function gets an element from a given position
	INPUT:positionFromUser=int
	PRECOND:position >0 and < the size of the vector
	POSTCOND:-
	OUTPUT:the element from the given position=genericType*
	THROWS:InvalidPosition if the position is invalid
	*/
	if (positionFromUser >= this->elements.size() || positionFromUser < 0)
		throw InvalidPosition();
	return this->elements[positionFromUser];
}

template <typename genericType>
void Repository<genericType>::setElement(int positionFromUser, genericType* newElement) {
	/*
	This function sets the element from position positionFromUser to newElement
	INPUT:positionFromUser=int, newElement=genericType*
	PRECOND:the position must be valid
	POSTCOND:-
	OUTPUT:-
	THROWS:InvalidPosition is the position is invalid
	*/
	if (positionFromUser >= this->elements.size()) {
		throw InvalidPosition();
	}
	this->elements[positionFromUser] = newElement;
}

template <typename genericType>
void Repository<genericType>::addToEnd(genericType* newElement) {
	/*
	This function adds newElemnt to the end of the repository
	INPUT:newElement=genericType*
	PRECOND:-
	POSTCOND:-
	OUTPUT:-
	THROWS:-
	*/
	this->elements.push_back(newElement);
}

template <typename genericType>
void Repository<genericType>::addToPosition(int positionFromUser, genericType* newElement) {
	/*
	This function adds newElemnet to a given position
	INPUT:positionFromUser-integer and newElement=genericType*
	PRECOND:position must be valid
	POSTCOND:-
	OUTPUT:-
	THROWS:InvalidPosition if the position is invalid
	*/

	if (positionFromUser > this->elements.size()) {
		throw InvalidPosition();
	}
	this->elements.insert(this->elements.begin() + positionFromUser, newElement);
}

template <typename genericType>
void Repository<genericType>::removeElement(genericType* element) {
	/*
	This function removes an element from the repository
	INPUT:element=genericType*
	PRECOND:the element must be in the repository
	POSTCOND:-
	OUTPUT:-
	THROWS:InexistingElement if the element does not exits in the repository
	*/
	int position = 0;
	for (int i = 0; i < this->elements.size(); i++) {
		if (strcmp(this->elements[i]->getId(), element->getId()) == 0) {
			position = i;
			break;
		}
	}
	if (position == this->elements.size())
		throw InexistingElement();
	else
		this->elements.erase(this->elements.begin() + position);
}

template <typename genericType>
void Repository<genericType>::remove(int positionFromUser) {
	/*
	This function removes an element from a given position
	INPUT:positionFromUser=int
	PRECOND:position must be valid
	POSTCOND:-
	OUTPUT:-
	THROWS:InvalidPosition if the
position is invalid
	*/
	if (positionFromUser >= this->elements.size()) {
		throw InvalidPosition();
	}
	this->elements.erase(this->elements.begin() + positionFromUser);
}

template <typename genericType>
int Repository<genericType>::search(char* ID) {
	/*
	This function searches for an element with a given ID
	INPUT:ID=char*=the ID of the element
	PRECOND:-
	POSTCOND:the returned position is the position on which the element was found. If it is -1, than the element was not found
	OUTPUT:i=integer
	THROWS:-
	*/
	int i;
	for (i = 0; i < this->elements.size(); i++)
		if (strcmp(this->elements[i]->getId(), ID) == 0)
			return i;
	return -1;
}

template <typename genericType>
RepositoryIterator<genericType> Repository<genericType>::iterator() const {
	/*
	This function returns an iterator of the repository
	OUTPUT:RepositoryIterator
	*/
	return RepositoryIterator<genericType>(*this);
}

template <typename genericType>
void Repository<genericType>::clearRepository() {
	/*
	This function clears the repository,i,e deletes all its elements
	INPUT:-
	*/
	this->elements.clear();
}

template <typename genericType>
Repository<genericType>::~Repository() {
	for (int position = 0; position < this->elements.size(); position++)
		delete this->elements[position];
}
