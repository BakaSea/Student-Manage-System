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

private:
	Ui::CourseWidget ui;
	vector<Course> vecCourse;
	void syncCourse();
	void updateCourse();
};