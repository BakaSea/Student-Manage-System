#pragma once

#include <QWidget>
#include "ui_StudentMainWidget.h"
#include <vector>
using namespace std;

class StudentMainWidget : public QWidget {
	Q_OBJECT

public:
	StudentMainWidget(QWidget *parent = Q_NULLPTR);
	~StudentMainWidget();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::StudentMainWidget ui;
	vector<QWidget*> childWidget;
};
