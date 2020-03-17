#pragma once

#include <QWidget>
#include "ui_ViewCourseWidget.h"
#include "RegistryManager.h"
#include "CourseManager.h"
#include "Course.h"

class ViewCourseWidget : public QWidget {
	Q_OBJECT

public:
	ViewCourseWidget(CourseManager *cm, int index, RegistryManager *rm, QWidget *parent = Q_NULLPTR);
	~ViewCourseWidget();

protected slots:
	//查看助教的学生
	void viewAssistant(QListWidgetItem* item);
	//导入成绩
	void inputScore();
	//导入学生
	void inputStudent();
	//刷新
	void refresh();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::ViewCourseWidget ui;
	vector<QWidget*> childWidget;
	RegistryManager* rm;
	CourseManager* cm;
	int index;
	Course course;
	//同步到表格
	void syncTable();
};
