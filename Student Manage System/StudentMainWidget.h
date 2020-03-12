#pragma once

#include <QWidget>
#include "ui_StudentMainWidget.h"

class StudentMainWidget : public QWidget {
	Q_OBJECT

public:
	StudentMainWidget(QWidget *parent = Q_NULLPTR);
	~StudentMainWidget();

private:
	Ui::StudentMainWidget ui;
};
