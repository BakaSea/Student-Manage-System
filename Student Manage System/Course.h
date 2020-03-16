#pragma once
#include <string>
#include <vector>
#include "Student.h"
#include <unordered_map>
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
	//设置某个学生免修不免考
	void setExempt(Student student, bool exempt);
	//判断某个学生是否免修不免考
	bool isExempt(Student student);
	//获取免修不免考的学生
	vector<Student> getExemptStudent();
	//设置某个学生的成绩
	void setScore(Student student, int score);
	//获取某个学生的成绩
	int getScore(Student student);

private:
	//存储该课的学生
	vector<Student> vecStu;
	//存储该课的助教
	vector<Student> vecAssist;
	//存储该课的助教教的学生
	vector< vector<Student> > vecAStu;
	//存储学生是否免修不免考
	unordered_map<string, bool> mapExempt;
	//存储学生成绩
	unordered_map<string, int> mapScore;
	void init();
};