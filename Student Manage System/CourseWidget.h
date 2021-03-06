﻿#pragma once

#include <QWidget>
#include "ui_CourseWidget.h"
#include "Course.h"
#include <vector>
#include "Student.h"
#include "CourseManager.h"
#include "RegistryManager.h"
using namespace std;

class CourseWidget : public QWidget {
	Q_OBJECT

public:
	enum UserType {STUDENT, ADMIN};
	//管理员登录
	CourseWidget(UserType userType, RegistryManager *rm, QWidget *parent = Q_NULLPTR);
	//学生登录
	CourseWidget(UserType userType, Student *student, RegistryManager *rm, QWidget* parent = Q_NULLPTR);
	~CourseWidget();
	//将课程信息同步到表格
	void syncTable();

protected slots:
	//增加课程
	void addCourse();
	//删除课程
	void deleteCourse();
	//修改课程
	void modifyCourse();
	//查看具体课程信息
	void viewCourse(int row, int col);
	//选课
	void selectCourse();
	//刷新
	void refresh();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::CourseWidget ui;
	vector<QWidget*> childWidget;
	RegistryManager* rm;
	//管理所有课程信息
	CourseManager* cm;
	//同步课程信息
	void syncCourse();
	//用户类型
	UserType userType;
	//当前操作的学生
	Student *student;
};
