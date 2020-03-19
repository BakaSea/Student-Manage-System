#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Student {
public:
	//学生id
	string id;
	Student();
	Student(string id);
	Student(const Student &A);
	bool operator == (const Student& A) const;
	bool operator < (const Student& A) const;
	//获取所选课程的多少
	int size();
	//判断是否包含该课程ID的课程
	bool contain(int id);
	//将map转换成vector
	vector< pair<int, Student> > getVector();
	//增加课程
	void addCourse(int id);
	//删除课程
	void deleteCourse(int id);
	//设置助教
	void setAssistant(int id, Student assistant);
	//删除助教
	void deleteAssistant(int id);
	//获取课程ID为id的课程的个人选择的助教
	Student getAssistant(int id);
	//设置免修不免考
	void setExempt(int id, bool exempt);
	//判断是否免修不免考
	bool isExempt(int id);
	//设置成绩
	void setScore(int id, int score);
	//获取成绩
	int getScore(int id);
	//从文件中同步学生信息
	void sync();
	//将学生信息写入到文件中
	void update();
private:
	//存储课程ID和个人选择的助教
	map<int, Student> mapCA;
	unordered_map<int, bool> mapExempt;
	unordered_map<int, int> mapScore;
};
