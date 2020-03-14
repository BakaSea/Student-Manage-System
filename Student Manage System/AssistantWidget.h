#pragma once

#include <QWidget>
#include "ui_AssistantWidget.h"
#include "CourseManager.h"
#include "Student.h"
#include <string.h>
using namespace std;

class AssistantWidget : public QWidget {
	Q_OBJECT

public:
	AssistantWidget(Student *student, CourseManager *cm, int id, QWidget *parent = Q_NULLPTR);
	~AssistantWidget();

protected slots:
	//报名助教
	void enrollAssistant();
	//选择个人助教
	void selectAssistant();

private:
	string ENROLL_STR = "报名助教", UNENROLL_STR = "取消报名";
	Ui::AssistantWidget ui;
	CourseManager* cm;
	Student* student;
	Course course;
	//当前课程
	int id;
	//同步到列表
	void syncList();
};
