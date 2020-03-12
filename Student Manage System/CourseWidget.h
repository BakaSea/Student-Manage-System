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

protected slots:
	void addCourse();
	void deleteCourse();
	void modifyCourse();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::CourseWidget ui;
	vector<QWidget*> childWidget;
	vector<Course> vecCourse;
	void syncCourse();
	void syncTable();
	void updateCourse();
};
