#pragma once
#include "Repository.h"

template <typename genericType>
class RepositoryIterator {
	template <typename genericType>
	friend class Repository;

private:
	//the iterator stores a reference to the container 
	const Repository<genericType>& repositoryConstant;
	int position;
	RepositoryIterator(const Repository<genericType>&);

public:
	//RepositoryIterator() {};
	bool valid() const;
	void next();
	void first();
	genericType* getCurrent() const;
};

template <typename genericType>
RepositoryIterator<genericType>::RepositoryIterator(const Repository<genericType>& repositoryFromUser) : repositoryConstant(repositoryFromUser) {
	//constructor
	this->position = 0;
}

template <typename genericType>
genericType* RepositoryIterator<genericType>::getCurrent() const {
	//gets the current element from the repository
	if (this->valid())
		return this->repositoryConstant.getElement(this->position);
	else
		throw std::invalid_argument("Invalid iterator.");
}

template <typename genericType>
bool RepositoryIterator<genericType>::valid() const {
	//checks if the iterator is valid
	return this->position < repositoryConstant.size();
}

template <typename genericType>
void RepositoryIterator<genericType>::next() {
	//goes to the next element
	if (this->valid())
		this->position++;
	else
		throw std::invalid_argument("Invalid iterator.");

}

template <typename genericType>
void RepositoryIterator<genericType>::first() {
	//reinitializing the iterator
	this->position = 0;
}
