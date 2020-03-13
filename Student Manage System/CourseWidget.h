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
	vector<Course> vecCourse;
	void updateCourse();
	void syncTable();

protected slots:
	void addCourse();
	void deleteCourse();
	void modifyCourse();
	void viewCourse(int row, int col);

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::CourseWidget ui;
	vector<QWidget*> childWidget;
	void syncCourse();
};
