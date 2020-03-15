#pragma once

#include <QWidget>
#include "ui_ViewCourseWidget.h"
#include "Course.h"

class ViewCourseWidget : public QWidget {
	Q_OBJECT

public:
	ViewCourseWidget(Course course, QWidget *parent = Q_NULLPTR);
	~ViewCourseWidget();

protected slots:
	void viewAssistant(QListWidgetItem *item);

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::ViewCourseWidget ui;
	Course course;
	vector<QWidget*> childWidget;
};
