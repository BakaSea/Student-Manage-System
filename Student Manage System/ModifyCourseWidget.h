#pragma once

#include <QWidget>
#include "ui_ModifyCourseWidget.h"
#include "CourseWidget.h"
#include "CourseManager.h"

class ModifyCourseWidget : public QWidget {
	Q_OBJECT

public:
	ModifyCourseWidget(CourseWidget *father, CourseManager *cm, int index, QWidget *parent = Q_NULLPTR);
	~ModifyCourseWidget();

protected slots:
	//确定修改课程
	void confirm();

private:
	Ui::ModifyCourseWidget ui;
	CourseWidget* father;
	CourseManager* cm;
	int index;
};
