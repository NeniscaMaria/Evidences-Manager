#pragma once
#include <string>
#include <vector>

class Evidence {
private:
	char* ID;
	char* measurement;
	double imageClarityLevel;
	int quantity;
	char* photograph;

public:
	Evidence(char*, char*, double, int, char*);
	Evidence();
	~Evidence();
	inline char* getId() const { return this->ID; }
	inline char* getMeasurement() const { return this->measurement; }
	inline double getImageClarityLevel() const { return this->imageClarityLevel; }
	inline int getQuantity() const { return this->quantity; }
	inline char* getPhotograph() const { return this->photograph; }
	bool operator==(Evidence*);
	Evidence* operator=(Evidence*);
	friend std::istream& operator>>(std::istream&, Evidence&);
	friend std::ostream& operator<<(std::ostream&, const Evidence*);
};

