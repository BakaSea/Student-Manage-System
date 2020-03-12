#pragma once

#include <QWidget>
#include "ui_AdminMainWidget.h"
#include <vector>
#include "Course.h"
using namespace std;

class AdminMainWidget : public QWidget {
	Q_OBJECT

public:
	AdminMainWidget(QWidget* parent = Q_NULLPTR);
	~AdminMainWidget();

protected slots:
	void logout();
	void inputCourse();
	void viewCourse();

private:
	Ui::AdminMainWidget ui;
};
