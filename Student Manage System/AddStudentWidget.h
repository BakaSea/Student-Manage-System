#pragma once

#include <QWidget>
#include "ui_AddStudentWidget.h"
#include "CourseManager.h"
#include "RegistryManager.h"
#include "Student.h"
#include "ViewCourseWidget.h"
#include "CourseWidget.h"

class AddStudentWidget : public QWidget {
	Q_OBJECT

public:
	AddStudentWidget(CourseManager *cm, int index, RegistryManager *rm, ViewCourseWidget *father, CourseWidget *grandFather, QWidget *parent = Q_NULLPTR);
	~AddStudentWidget();

protected slots:
	//确定添加学生
	void confirm();

private:
	Ui::AddStudentWidget ui;
	CourseManager* cm;
	RegistryManager* rm;
	ViewCourseWidget* father;
	CourseWidget* grandFather;
	int index;
	//存储学生信息
	vector<Student> vecStu;
	//同步到表格
	void syncTable();
};
