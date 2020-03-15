#pragma once

#include <QWidget>
#include "ui_ViewAssistantWidget.h"
#include "Course.h"
#include "Student.h"
#include <vector>
using namespace std;

class ViewAssistantWidget : public QWidget
{
	Q_OBJECT

public:
	ViewAssistantWidget(Course course, Student assistant, QWidget *parent = Q_NULLPTR);
	~ViewAssistantWidget();

private:
	Ui::ViewAssistantWidget ui;
	Course course;
	Student assistant;
	vector<Student> vecAStudent;
};
