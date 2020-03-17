#pragma once

#include <QWidget>
#include "ui_AdminMainWidget.h"
#include <vector>
#include "RegistryManager.h"
using namespace std;

class AdminMainWidget : public QWidget {
	Q_OBJECT

public:
	AdminMainWidget(RegistryManager *rm, QWidget* parent = Q_NULLPTR);
	~AdminMainWidget();

protected slots:
	//注销登录
	void logout();
	//录入课程
	void inputCourse();
	//查看课程信息
	void viewCourse();
	//导入学生名单
	void inputStudent();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Ui::AdminMainWidget ui;
	vector<QWidget*> childWidget;
	RegistryManager* rm;
};
