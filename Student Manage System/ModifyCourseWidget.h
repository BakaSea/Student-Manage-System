#pragma once

#include <QWidget>
#include "ui_ModifyCourseWidget.h"

class ModifyCourseWidget : public QWidget {
	Q_OBJECT

public:
	ModifyCourseWidget(QWidget *parent = Q_NULLPTR);
	~ModifyCourseWidget();

private:
	Ui::ModifyCourseWidget ui;
};
