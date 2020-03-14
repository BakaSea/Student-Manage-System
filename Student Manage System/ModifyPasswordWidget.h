#pragma once

#include <QWidget>
#include "ui_ModifyPasswordWidget.h"
#include "RegistryManager.h"
#include "Student.h"

class ModifyPasswordWidget : public QWidget {
	Q_OBJECT

public:
	ModifyPasswordWidget(Student student, RegistryManager *rm, QWidget *parent = Q_NULLPTR);
	~ModifyPasswordWidget();

protected slots:
	//确定修改
	void confirm();

private:
	Ui::ModifyPasswordWidget ui;
	RegistryManager* rm;
	Student student;
};
