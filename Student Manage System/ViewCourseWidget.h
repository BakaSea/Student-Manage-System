#pragma once

#include <QWidget>
#include "ui_ViewCourseWidget.h"
#include "CourseWidget.h"

class ViewCourseWidget : public QWidget {
	Q_OBJECT

public:
	ViewCourseWidget(CourseWidget *father, int index, QWidget *parent = Q_NULLPTR);
	~ViewCourseWidget();

private:
	Ui::ViewCourseWidget ui;
	CourseWidget* father;
	int index;
};
