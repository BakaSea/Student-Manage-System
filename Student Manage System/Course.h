#pragma once
#include <string>
using namespace std;

class Course {
	enum CourseType {SPEC, NONSPEC};
public:
	int id, cap, cnt;
	string name, teacher;
	CourseType type;
	Course() {}
	Course(int id, string name, string teacher, int cap, int cnt, CourseType type) : id(id), name(name), teacher(teacher), cap(cap), cnt(cnt), type(type) {}
	string getTypeName();
	static CourseType getTypebyName(string type);
	static CourseType getTypebyIndex(int index);
};