/** 
 * Author: Manish Mallavarapu
 * Contains methods to sort students read
 * from file and handles program flow
 */ 
#include "Student.h"

using namespace std;
/** 
 * Used whenever we want to read a student 
 * from the istream 
*/
istream& operator >> (istream& is, Student& s) {
	s.clearGrades();  
	string id, firstName, lastName,course; 
	int numCourses, grade; 
	is >> id >> firstName >> lastName >> numCourses; 
	s.setId(id); 
	s.setName({firstName,lastName}); 
	for(int i = 0; i < numCourses; i++) {
		 is >> course >> grade;  
		 s.setGrades({course,grade});
	} 
	return is; 
} 
bool compareByIdAscending(const Student& s1, const Student &s2);
bool compareByIdDesc(const Student& s1, const Student &s2);
void evaluateName(const string& firstName, const string& lastName, 
				  const vector<Student>& students); 
void evaluateNameById(const string& firstName, const string& lastName, 
				 	  const vector<Student>& students);
void findStudentWithScoreById(const string& course, const int grade,
	                      const vector<Student>& students);
void findStudentWithScore(const string& course, const int grade,
	                      const vector<Student>& students);
void findStudentWithScoreRangeById(const string& course, const int grade1,
	                               const int grade2,const vector<Student>& students);
void findStudentWithScoreRange(const string& course, const int grade1,
	                           const int grade2,const vector<Student>& students);
/**
 * Where the program starts 
*/ 
int main(int argc, char *argv[]) {
	vector<Student> students; 
	vector<string> commands; 
	Student s; 
	string line; 
	string cmd; 
	//string subCommand; 
	if(argc != 2) { 
		cerr << "Usage: " << argv[0] << " [input_file]" << endl;
		exit(1); //print usage and exit if file is not specified
	}
	ifstream input_file(argv[1]);
	if(!input_file) { 
		cerr << "Not able to open file " << argv[1] << endl; 
		exit(1); //print error message if we cannot open the file
	}
	students.clear(); //clear students vector to make sure it is empty
	while(input_file >> s) {  //while we can read a student we add it to our vector.
		students.push_back(s); 
	}
	cerr << "Please enter a command: " << endl; //our prompt for the user to enter commands
	while(getline(cin, line)) { //while we can read a line from standard input
		istringstream iss(line);
		while(iss >> cmd) { 
			commands.push_back(cmd); //push commands onto our vector
		} 
		//process all prompts by iterating through the command vector
		vector<string>::iterator it; 
		for(it = commands.begin(); it != commands.end(); it++) { //iterate through the command list and execute
			int size = commands.size(); 
			switch(size) { 
				case 1: 
					if(*it == "show") { 
						sort(students.begin(), students.end(),compareByIdAscending); 
						for(Student& s : students) { 
							s.display(cout); 
						}  
					}
					else if(*it == "-show") {
						sort(students.begin(), students.end(),compareByIdDesc); 
						for(Student& s : students) { 
							s.display(cout); 
						}  
					}
					else if(*it == "showid") { 
						sort(students.begin(), students.end(),compareByIdAscending); 
						for(Student& s : students) { 
							s.displayId(cout); 
						}  
					} 
					else if(*it == "-showid") { 
						sort(students.begin(), students.end(),compareByIdDesc); 
						for(Student& s : students) { 
							s.displayId(cout); 
						} 
					}
					break; 
				case 3: 	
					if(*it == "show" && *(it + 1) == "id") {
						string id = *(it + 2);  
						sort(students.begin(), students.end(),compareByIdAscending);
						for(Student& s : students) { 
							if(s.getId() == id) { 
								s.display(cout); 
							}
						}  
					}
					else if(*it == "-show" && *(it + 1) == "id") {
						sort(students.begin(), students.end(),compareByIdDesc); 
						string id = *(it + 2); 
						for(Student& s : students) {
							if(s.getId() == id) {
								s.display(cout);
							}  
						}  
					}
					else if(*it == "showid" && *(it + 1) == "id") { 
						sort(students.begin(), students.end(),compareByIdAscending); 
						string id = *(it + 2);
						for(Student& s : students) {
							if(s.getId() == id) { 
								s.displayId(cout); 
							}
						}  
					} 
					else if(*it == "-showid" && *(it + 1) == "id") { 
						sort(students.begin(), students.end(),compareByIdDesc); 
						string id = *(it + 2);
						for(Student& s : students) { 
							if(s.getId() == id) { 
								s.displayId(cout); 
							}
						} 
					}
					break; 
				case 4: 
					if(*it == "show" && *(it + 1) == "name") { 
						 sort(students.begin(), students.end(),compareByIdAscending); 
						 string firstName = *(it + 2); 
						 string lastName = *(it + 3); 
						 evaluateName(firstName, lastName, students); 
					}
					else if(*it == "-show" && *(it + 1) == "name") { 
						 sort(students.begin(), students.end(),compareByIdDesc); 
						 string firstName = *(it + 2); 
						 string lastName = *(it + 3); 
						 evaluateName(firstName,lastName,students); 
					}
					else if(*it == "showid" && *(it + 1) == "name") { 
						 sort(students.begin(), students.end(),compareByIdAscending); 
						 string firstName = *(it + 2); 
						 string lastName = *(it + 3); 
						 evaluateNameById(firstName,lastName,students); 
					}
					else if(*it == "-showid" && *(it + 1) == "name") { 
						 sort(students.begin(), students.end(),compareByIdDesc); 
						 string firstName = *(it + 2); 
						 string lastName = *(it + 3); 
						 evaluateNameById(firstName,lastName,students); 
					}	
					if(*it == "showid" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdAscending);
						string s = *(it + 2) + " " + *(it + 3);  
						string course; 
						int grade; 
						istringstream iss(s);
						if(iss >> course >> grade) { 
							findStudentWithScoreById(course,grade,students); 
						}
					}
					else if(*it == "-showid" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdDesc);
						string s = *(it + 2) + " " + *(it + 3);  
						string course; 
						int grade; 
						istringstream iss(s);
						if(iss >> course >> grade) { 
							findStudentWithScoreById(course,grade,students); 
						}
					}
					else if(*it == "show" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdAscending);
						string s = *(it + 2) + " " + *(it + 3);  
						string course; 
						int grade; 
						istringstream iss(s);
						if(iss >> course >> grade) { 
							findStudentWithScore(course,grade,students); 
						}
					}
					else if(*it == "-show" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdDesc);
						string s = *(it + 2) + " " + *(it + 3);  
						string course; 
						int grade; 
						istringstream iss(s);
						if(iss >> course >> grade) { 
							findStudentWithScore(course,grade,students); 
						}
					}
					break; 
				case 5: 
					if(*it == "showid" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdAscending);
						string s = *(it + 2) + " " + *(it + 3) + " " + *(it + 4);  
						string course; 
						int grade; 
						int grade2; 
						istringstream iss(s);
						if(iss >> course >> grade >> grade2) { 
							findStudentWithScoreRangeById(course,grade,grade2,students); 
						}
					}
					if(*it == "-showid" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdDesc);
						string s = *(it + 2) + " " + *(it + 3) + " " + *(it + 4);  
						string course; 
						int grade; 
						int grade2; 
						istringstream iss(s);
						if(iss >> course >> grade >> grade2) { 
							findStudentWithScoreRangeById(course,grade,grade2,students); 
						}
					}
					if(*it == "show" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdAscending);
						string s = *(it + 2) + " " + *(it + 3) + " " + *(it + 4);  
						string course; 
						int grade; 
						int grade2; 
						istringstream iss(s);
						if(iss >> course >> grade >> grade2) { 
							findStudentWithScoreRange(course,grade,grade2,students); 
						}
					}
					if(*it == "-show" && *(it + 1) == "grade") { 
						sort(students.begin(), students.end(),compareByIdDesc);
						string s = *(it + 2) + " " + *(it + 3) + " " + *(it + 4);  
						string course; 
						int grade; 
						int grade2; 
						istringstream iss(s);
						if(iss >> course >> grade >> grade2) { 
							findStudentWithScoreRange(course,grade,grade2,students); 
						}
					}
					break; 
			}
			continue; 
		}
		cout << endl; 
		commands.clear(); 
		cerr << "Please enter a command: " << endl; //our prompt for the user to enter commands
	}
}
//compare function to be used with sort to sort student ids in ascending order
bool compareByIdAscending(const Student& s1, const Student& s2) { 
	return s1.getId() < s2.getId(); 
}
//compare function to be used with sort to sort student ids in descending order
bool compareByIdDesc(const Student& s1, const Student& s2) { 
	return s1.getId() > s2.getId(); 
}
//search and print names 
void evaluateName(const string& firstName, const string& lastName, 
				  const vector<Student>& students) { 
	if(firstName == "*" && lastName == "*") { 
		for(const Student& s : students) { 
			s.display(cout); 
		}
	}
	else if(firstName != "*" && lastName == "*") { 
		for(const Student& s : students) { 
			if(s.getFirstName() == firstName) {
				s.display(cout); 
			}
		}
	}
	else if(firstName == "*" && lastName != "*") { 
		for(const Student& s : students) { 
			if(s.getLastName() == lastName) {
				s.display(cout); 
			}
		}
	}
	else if(firstName != "*" && lastName != "*") { 
		for(const Student& s : students) { 
			if(s.getFirstName() == firstName && s.getLastName() == lastName) {
				s.display(cout); 
			}
		}
	}
}
//Search name and print ID of student
void evaluateNameById(const string& firstName, const string& lastName, 
				 	  const vector<Student>& students) { 
	if(firstName == "*" && lastName == "*") { 
		for(const Student& s : students) { 
			s.displayId(cout); 
		}
	}
	else if(firstName != "*" && lastName == "*") { 
		for(const Student& s : students) { 
			if(s.getFirstName() == firstName) {
				s.displayId(cout); 
			}
		}
	}
	else if(firstName == "*" && lastName != "*") { 
		for(const Student& s : students) { 
			if(s.getLastName() == lastName) {
				s.displayId(cout); 
			}
		}
	}
	else if(firstName != "*" && lastName != "*") { 
		for(const Student& s : students) { 
			if(s.getFirstName() == firstName && s.getLastName() == lastName) {
				s.displayId(cout); 
			}
		}
	}
}
void findStudentWithScoreById(const string& course, const int grade,const vector<Student>& students) { 
	for(const Student& s : students) { 
		map<string, int> studentGrades = s.getGrades(); 
		for(map<string, int>::iterator it = studentGrades.begin(); it != studentGrades.end(); ++it) { 
			if(it -> first == course && it -> second == grade) { 
				s.displayId(cout); 
			} 
		}
	}
}
void findStudentWithScore(const string& course, const int grade,const vector<Student>& students) { 
	for(const Student& s : students) { 
		map<string, int> studentGrades = s.getGrades(); 
		for(map<string, int>::iterator it = studentGrades.begin(); it != studentGrades.end(); ++it) { 
			if(it -> first == course && it -> second == grade) { 
				s.display(cout); 
			} 
		}
	}
}
void findStudentWithScoreRangeById(const string& course, const int grade1,const int grade2,const vector<Student>& students) { 
	for(const Student& s : students) { 
		map<string, int> studentGrades = s.getGrades(); 
		for(map<string, int>::iterator it = studentGrades.begin(); it != studentGrades.end(); ++it) { 
			if(it -> first == course && it -> second >= grade1 && it -> second <= grade2) { 
				s.displayId(cout); 
			} 
		}
	}
}
void findStudentWithScoreRange(const string& course, const int grade1,const int grade2,const vector<Student>& students) { 
	for(const Student& s : students) { 
		map<string, int> studentGrades = s.getGrades(); 
		for(map<string, int>::iterator it = studentGrades.begin(); it != studentGrades.end(); ++it) { 
			if(it -> first == course && it -> second >= grade1 && it -> second <= grade2) { 
				s.display(cout); 
			} 
		}
	}
}
