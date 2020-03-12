#pragma once

#include <QtWidgets/QWidget>
#include "ui_LoginWidget.h"
#include <map>
#include "Student.h"
using namespace std;

class LoginWidget : public QWidget {
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = Q_NULLPTR);

protected slots:
	void loginStudent();
	void loginAdmin();
	void registerStudent();

private:
	Ui::LoginWidgetClass ui;
	map<string, string> mapStu;
	void syncStudentList();
	int updateStudentList();
	bool checkUsername(string name);
};
