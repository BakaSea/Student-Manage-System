#pragma once

#include <QWidget>
#include "ui_CourseWidget.h"
#include "Course.h"
#include <vector>
using namespace std;

class CourseWidget : public QWidget {
	Q_OBJECT

public:
	CourseWidget(QWidget *parent = Q_NULLPTR);
	~CourseWidget();
	//存储课程信息
	vector<Course> vecCourse;
	//将课程信息写入到文件
	void updateCourse();
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

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::CourseWidget ui;
	vector<QWidget*> childWidget;
	//从文件中同步课程信息
	void syncCourse();
};
