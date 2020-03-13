#pragma once

#include <QWidget>
#include "ui_AdminMainWidget.h"
#include <vector>
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

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::AdminMainWidget ui;
	vector<QWidget*> childWidget;
};
