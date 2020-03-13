#pragma once

#include <QWidget>
#include "ui_AddCourseWidget.h"
#include "CourseWidget.h"

class AddCourseWidget : public QWidget {
	Q_OBJECT

public:
	AddCourseWidget(CourseWidget *father, QWidget *parent = Q_NULLPTR);
	~AddCourseWidget();

protected slots:
	//确定增加课程
	void confirm();

private:
	Ui::AddCourseWidget ui;
	CourseWidget* father;
};
