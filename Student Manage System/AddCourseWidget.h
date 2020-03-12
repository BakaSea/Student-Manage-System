#pragma once

#include <QWidget>
#include "ui_AddCourseWidget.h"

class AddCourseWidget : public QWidget {
	Q_OBJECT

public:
	AddCourseWidget(QWidget *parent = Q_NULLPTR);
	~AddCourseWidget();

private:
	Ui::AddCourseWidget ui;
};
