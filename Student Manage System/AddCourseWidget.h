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
	void confirm();

private:
	Ui::AddCourseWidget ui;
	CourseWidget* father;
};
