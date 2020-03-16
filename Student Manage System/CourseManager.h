#pragma once
#include "Course.h"
#include <vector>
using namespace std;

class CourseManager {
public:
	CourseManager();
	~CourseManager();
	//获取第index个课程
	Course getCourse(int index);
	//获取课程ID为ID的课程
	Course getCourseByID(int id);
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
	//删除学生
	void deleteStudent(int id, Student student);
	//添加助教
	void addAssistant(int id, Student student);
	//删除助教
	void deleteAssistant(int id, Student student);
	//向助教添加学生
	void addStudentToAssistant(int id, Student assistant, Student student);
	//向助教删除学生
	void deleteStudentToAssistant(int id, Student assistant, Student student);
	//设置课程的学生免修不免考
	void setExempt(int id, Student student, bool exempt);
	//判断课程的学生是否免修不免考
	bool isExempt(int id, Student student);
	//设置课程的学生的成绩
	void setScore(int id, Student student, int score);
	//获取课程的学生的成绩
	int getScore(int id, Student student);
	//从文件中同步课程信息
	void sync();
	//将课程信息写入文件
	void update();
	//将助教信息写入文件
	void updateAssistant();

private:
	vector<Course> vecCourse;
};
