#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

class Student {
public:
	//学生id
	string id;
	Student();
	Student(string id);
	bool contain(int id);
	//增加课程
	void addCourse(int id);
	//删除课程
	void deleteCourse(int id);
	//设置助教
	void setAssistant(int id, Student assistant);
	//从文件中同步学生信息
	void sync();
	//将学生信息写入到文件中
	void update();
private:
	//存储课程ID和助教
	map<int, Student> mapCA;
};
