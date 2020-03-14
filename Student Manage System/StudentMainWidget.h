#pragma once

#include <QWidget>
#include "ui_StudentMainWidget.h"
#include <vector>
#include "LoginWidget.h"
#include "Student.h"
using namespace std;

class StudentMainWidget : public QWidget {
	Q_OBJECT

public:
	StudentMainWidget(LoginWidget *father, Student student, QWidget *parent = Q_NULLPTR);
	~StudentMainWidget();

protected slots:
	//注销登录
	void logout();
	//查看课程信息
	void viewCourse();
	//查看个人课表
	void viewOwnCourse();
	//修改密码
	void modifyPassword();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::StudentMainWidget ui;
	vector<QWidget*> childWidget;
	LoginWidget* father;
	//当前操作的学生
	Student* student;
};
