#pragma once
#include <string>
#include <vector>
#include "Student.h"
#include <map>
using namespace std;

class Course {
public:
	enum CourseType {SPEC, NONSPEC};
	//课程id，上限人数
	int id, cap;
	//课程名称，授课教师
	string name, teacher;
	//课程类型
	CourseType type;
	Course();
	Course(int id, string name, string teacher, int cap, int cnt, CourseType type);
	string getTypeName();
	static CourseType getTypebyName(string type);
	static CourseType getTypebyIndex(int index);
	//将课程写入到文件中
	void update();
	//从文件中同步课程
	void sync();
	//获取已选人数
	int getCnt();
	//判断是否已满
	bool full();
	//增加学生
	void addStudent(Student student);
	//删除学生
	void deleteStudent(Student student);
	//增加助教
	void addAssistant(Student student);
	//删除助教
	void deleteAssistant(Student student);
	//获取第index个学生
	Student getStudent(int index);
	//获取助教人数
	int assistSize();
	//获取第index个助教
	Student getAssistant(int index);
	//判断是否存在该助教
	bool containAssistant(Student assistant);
	//向助教增加学生
	void addStudentToAssistant(Student assistant, Student student);
	//向助教删除学生
	void deleteStudentToAssistant(Student assistant, Student student);
	//获取该助教的学生
	vector<Student> getAStudent(Student assistant);

private:
	//存储该课的学生
	vector<Student> vecStu;
	map<Student, int> mapStu;
	//存储该课的助教
	vector<Student> vecAssist;
	map<Student, int> mapAssist;
	//存储该课的助教教的学生
	vector< vector<Student> > vecAStu;
	vector< map<Student, int> > mapAStu;
};