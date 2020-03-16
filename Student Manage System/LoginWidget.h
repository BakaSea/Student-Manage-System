#pragma once

#include <QWidget>
#include "ui_LoginWidget.h"
#include <map>
#include "Student.h"
#include "RegistryManager.h"
using namespace std;

class LoginWidget : public QWidget {
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = Q_NULLPTR);
	void clearWidget();

protected slots:
	//学生登录
	void loginStudent();
	//管理员登录
	void loginAdmin();
	//学生注册
	void registerStudent();

private:
	Ui::LoginWidgetClass ui;
	//管理学生信息
	RegistryManager* rm;
	//判断学生id是否合法
	bool checkUsername(string name);
};
