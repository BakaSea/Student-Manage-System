#pragma once

#include <QWidget>
#include "ui_ModifyCourseWidget.h"
#include "CourseWidget.h"

class ModifyCourseWidget : public QWidget {
	Q_OBJECT

public:
	ModifyCourseWidget(CourseWidget *father, int index, QWidget *parent = Q_NULLPTR);
	~ModifyCourseWidget();

protected slots:
	void confirm();

private:
	Ui::ModifyCourseWidget ui;
	CourseWidget* father;
	int index;
};
