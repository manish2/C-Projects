/** 
 * Author: Manish Mallavarapu
 * Implementatino of Student.h file
 * stores information about a student object
 * and can also print student objects
 */ 
#include "Student.h"

using namespace std; 

void Student::setId(const string& id) { 
	id_ = id; 
}
void Student::clearGrades() { 
	grades_.clear(); 
}
void Student::setName(const pair<string, string>& name) { 
	name_ = name; 
}
void Student::setGrades(const pair<string,int>& grades) { 
	grades_.insert(grades); 
}
string Student::getId() const { 
	return id_; 
}
pair<string, string> Student::getName() const { 
	return name_; 
}
map<string, int> Student::getGrades() const { 
	return grades_; 
}
string Student::getFirstName() const { 
	return get<0>(name_); 
}
string Student::getLastName() const { 
	return get<1>(name_); 
}
void Student::display(ostream& os) const { 
	os << getId() << endl; 
	map<string, int> temp = getGrades();  
	os << getFirstName() << " " << getLastName() << endl; 
	for(map<string, int>::iterator it = temp.begin(); it != temp.end(); it++) { 
		os << it -> first << " " << it -> second << endl; 
	} 
}
void Student::displayId(std::ostream& os) const { 
	os << getId() << endl; 
}
