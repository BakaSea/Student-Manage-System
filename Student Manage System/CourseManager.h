#pragma once
#include "Course.h"
#include <vector>
#include <map>
using namespace std;

class CourseManager {
public:
	CourseManager();
	~CourseManager();
	//获取第index个课程
	Course getCourse(int index);
	//增加课程
	void addCourse(Course course);
	//删除课程
	void deleteCourse(int index);
	//修改课程
	void modifyCourse(int index, string teacher, int cap);
	//获取大小
	int size();
	//判断是否为空
	bool empty();
	//添加学生
	void addStudent(int index, Student student);
	//添加助教
	void addAssistant(int index, Student student);
	//从文件中同步课程信息
	void sync();
	//将课程信息写入文件
	void update();

private:
	vector<Course> vecCourse;
	map<int, int> mapCourse;
};
