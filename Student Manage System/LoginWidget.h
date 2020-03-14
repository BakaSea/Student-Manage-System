#pragma once

#include <QWidget>
#include "ui_LoginWidget.h"
#include <map>
#include "Student.h"
using namespace std;

class LoginWidget : public QWidget {
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = Q_NULLPTR);

protected slots:
	//学生登录
	void loginStudent();
	//管理员登录
	void loginAdmin();
	//学生注册
	void registerStudent();

private:
	Ui::LoginWidgetClass ui;
	//存储学生id和密码
	map<string, string> mapStu;
	//从文件获取学生信息
	void syncStudentList();
	//将学生信息写入文件
	int updateStudentList();
	//判断学生id是否合法
	bool checkUsername(string name);
};
