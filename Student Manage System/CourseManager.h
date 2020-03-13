#pragma once
#include "Course.h"
#include <vector>
#include <map>
using namespace std;

class CourseManager {
public:
	CourseManager();
	~CourseManager();
	//��ȡ��index���γ�
	Course getCourse(int index);
	//���ӿγ�
	void addCourse(Course course);
	//ɾ���γ�
	void deleteCourse(int index);
	//�޸Ŀγ�
	void modifyCourse(int index, string teacher, int cap);
	//��ȡ��С
	int size();
	//�ж��Ƿ�Ϊ��
	bool empty();
	//���ѧ��
	void addStudent(int index, Student student);
	//�������
	void addAssistant(int index, Student student);
	//���ļ���ͬ���γ���Ϣ
	void sync();
	//���γ���Ϣд���ļ�
	void update();

private:
	vector<Course> vecCourse;
	map<int, int> mapCourse;
};
