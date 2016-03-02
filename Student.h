#include <iostream>
/** 
 * Author: Manish Mallavarapu
 * Header file for student functions 
 * related to grades and courses 
 */ 
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std; 
typedef std::pair<std::string, std::string> Name;    // first name, last name
typedef std::map<std::string, int>          Grades; // map courses to scores

class Student {
	public:
		void display(ostream& os) const;
		void displayId(ostream& os) const; 
		void setId(const string& id); 
		void setName(const pair<string, string>& name); 
		void setGrades(const pair<string,int>& grades);
		void clearGrades(); 
		string getId() const; 
		pair<string, string> getName() const; 
		string getFirstName() const; 
		string getLastName() const; 
		map<string, int> getGrades() const; 
	private:
		std::string id_; // e.g. "a22222222"
		Name name_; // e.g. {"ned", "flanders"}
		Grades grades_; // e.g. {{"comp1510", 90}, {"comp2510", 85}}
};