#pragma once

#include <QWidget>
#include "ui_OwnCourseWidget.h"

class OwnCourseWidget : public QWidget {
	Q_OBJECT

public:
	OwnCourseWidget(QWidget *parent = Q_NULLPTR);
	~OwnCourseWidget();

private:
	Ui::OwnCourseWidget ui;
};
