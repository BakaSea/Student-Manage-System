#include "Course.h"
#include <qdebug.h>
#include <qdir.h>
#include <qfile.h>
#include <qiodevice.h>

Course::Course() : id(0), name(""), teacher(""), cap(0), type(SPEC) {
	init();
}

Course::Course(int id, string name, string teacher, int cap, int cnt, CourseType type) : 
	id(id), name(name), teacher(teacher), cap(cap), type(type) {
	init();
}

string Course::getTypeName() {
	return type == SPEC ? "专业课" : "非专业课";
}

Course::CourseType Course::getTypebyName(string type) {
	return type == "专业课" ? SPEC : NONSPEC;
}

Course::CourseType Course::getTypebyIndex(int index) {
	return index ? NONSPEC : SPEC;
}

int Course::getCnt() {
	return vecStu.size();
}

bool Course::full() {
	return vecStu.size() >= cap;
}

void Course::addStudent(Student student) {
	vecStu.push_back(student);
	mapExempt[student.id] = false;
}

void Course::deleteStudent(Student student) {
	for (int i = 0; i < vecStu.size(); ++i) {
		if (vecStu[i] == student) {
			vecStu.erase(vecStu.begin() + i);
			break;
		}
	}
}

void Course::addAssistant(Student student) {
	vecAssist.push_back(student);
	vecAStu.push_back(vector<Student>());
}

void Course::deleteAssistant(Student student) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == student) {
			vecAssist.erase(vecAssist.begin() + i);
			vecAStu.erase(vecAStu.begin() + i);
			break;
		}
	}
}

Student Course::getStudent(int index) {
	return vecStu[index];
}

bool Course::containStudent(Student student) {
	return mapExempt.find(student.id) != mapExempt.end();
}

int Course::assistSize() {
	return vecAssist.size();
}

Student Course::getAssistant(int index) {
	return vecAssist[index];
}

bool Course::containAssistant(Student assistant) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			return true;
		}
	}
	return false;
}

void Course::addStudentToAssistant(Student assistant, Student student) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			vecAStu[i].push_back(student);
		}
	}
}

void Course::deleteStudentToAssistant(Student assistant, Student student) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			for (int j = 0; j < vecAStu[i].size(); ++i) {
				if (vecAStu[i][j] == student) {
					vecAStu[i].erase(vecAStu[i].begin() + j);
					break;
				}
			}
			break;
		}
	}
}

vector<Student> Course::getAStudent(Student assistant) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			return vecAStu[i];
		}
	}
	return vector<Student>();
}

void Course::setExempt(Student student, bool exempt) {
	if (exempt) {
		mapExempt[student.id] = true;
	} else {
		mapExempt.erase(student.id);
	}
}

bool Course::isExempt(Student student) {
	return mapExempt[student.id];
}

vector<Student> Course::getExemptStudent() {
	vector<Student> vecExempt;
	vecExempt.clear();
	for (unordered_map<string, bool>::iterator iter = mapExempt.begin(); iter != mapExempt.end(); ++iter) {
		vecExempt.push_back(Student(iter->first));
	}
	return vecExempt;
}

void Course::setScore(Student student, int score) {
	mapScore[student.id] = score;
}

int Course::getScore(Student student) {
	unordered_map<string, int>::iterator iter = mapScore.find(student.id);
	return iter == mapScore.end() ? -1 : iter->second;
}

void Course::init() {
	vecStu.clear();
	vecAssist.clear();
	vecAStu.clear();
	mapExempt.clear();
	mapScore.clear();
}
