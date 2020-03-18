#pragma once

#include <QWidget>
#include "ui_ViewCourseWidget.h"
#include "RegistryManager.h"
#include "Course.h"
#include "CourseManager.h"
#include "CourseWidget.h"

class ViewCourseWidget : public QWidget {
	Q_OBJECT

public:
	ViewCourseWidget(CourseManager *cm, int index, RegistryManager *rm, CourseWidget *father, QWidget *parent = Q_NULLPTR);
	~ViewCourseWidget();
	//同步到表格
	void syncTable();

protected slots:
	//查看助教的学生
	void viewAssistant(QListWidgetItem* item);
	//导入成绩
	void inputScore();
	//导入学生
	void addStudent();
	//刷新
	void refresh();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::ViewCourseWidget ui;
	vector<QWidget*> childWidget;
	RegistryManager* rm;
	CourseManager* cm;
	CourseWidget* father;
	Course* course;
	int index;
};
