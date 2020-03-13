#pragma once
#include <string>
#include <vector>
#include "Student.h"
using namespace std;

class Course {
	enum CourseType {SPEC, NONSPEC};
public:
	int id, cap;
	string name, teacher;
	CourseType type;
	Course();
	Course(int id, string name, string teacher, int cap, int cnt, CourseType type);
	string getTypeName();
	static CourseType getTypebyName(string type);
	static CourseType getTypebyIndex(int index);
	void update();
	void sync();
	vector<Student> vecStu;
	vector<Student> vecAssist;
	int getCnt();
	void setCnt(int x);
	void addCnt();
private:
	int cnt;
};