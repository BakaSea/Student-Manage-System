#pragma once

#include <QWidget>
#include "ui_OwnCourseWidget.h"
#include "Student.h"
#include "CourseManager.h"
#include <vector>
using namespace std;

class OwnCourseWidget : public QWidget {
	Q_OBJECT

public:
	OwnCourseWidget(Student *student, QWidget *parent = Q_NULLPTR);
	~OwnCourseWidget();
	//将课程信息同步到表格
	void syncTable();

protected slots:
	//退课
	void dropCourse();
	//进入课程助教信息界面
	void courseAssistant(int row, int col);
	//刷新
	void refresh();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::OwnCourseWidget ui;
	vector<QWidget*> childWidget;
	//当前操作的学生
	Student *student;
	//管理课程信息
	CourseManager* cm;
	//存储课表中的课程信息
	vector< pair<int, Student> > vecCourse;
	//同步课程
	void syncCourse();
};
