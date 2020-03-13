#pragma once
#include <string>
#include <vector>
#include "Student.h"
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
	//存储该课的学生
	vector<Student> vecStu;
	//存储该课的助教
	vector<Student> vecAssist;
	//获取已选人数
	int getCnt();
	//设置已选人数
	void setCnt(int x);
	//已选人数+1
	void addCnt();
	//判断是否已满
	bool full();
private:
	//已选人数
	int cnt;
};