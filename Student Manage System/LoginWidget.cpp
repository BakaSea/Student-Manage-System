#include "LoginWidget.h"
#include <stdio.h>
#include <string.h>
#include "AdminMainWidget.h"
#include "StudentMainWidget.h"
#include <qdir.h>
#include <qcryptographichash.h>

LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	rm = new RegistryManager();
}

void LoginWidget::loginStudent() {
	if (!rm->studentExist(ui.lineUsername->text().toStdString())) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("用户名错误！"));
	} else {
		if (rm->loginSuccess(ui.lineUsername->text().toStdString(), ui.linePassword->text().toStdString())) {
			ui.labelWarning->setStyleSheet("color:green");
			ui.labelWarning->setText(QString::fromLocal8Bit("登录成功！"));
			this->hide();
			StudentMainWidget* smw = new StudentMainWidget(this, Student(ui.lineUsername->text().toStdString()), rm);
			smw->show();
		} else {
			ui.labelWarning->setStyleSheet("color:red");
			ui.labelWarning->setText(QString::fromLocal8Bit("密码错误！"));
		}
	}
}

void LoginWidget::clearWidget() {
	ui.lineUsername->setText("");
	ui.linePassword->setText("");
	ui.labelWarning->setText("");
}

void LoginWidget::loginAdmin() {
	if (ui.lineUsername->text() == "Admin") {
		if (ui.linePassword->text() == "admin") {
			ui.labelWarning->setStyleSheet("color:green");
			ui.labelWarning->setText(QString::fromLocal8Bit("登录成功！"));
			this->close();
			AdminMainWidget* amw = new AdminMainWidget(rm);
			amw->show();
		} else {
			ui.labelWarning->setStyleSheet("color:red");
			ui.labelWarning->setText(QString::fromLocal8Bit("密码错误！"));
		}
	} else {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("用户名错误！"));
	}
}

void LoginWidget::registerStudent() {
	string id = ui.lineUsername->text().toStdString();
	if (rm->checkUsername(id)) {
		if (ui.linePassword->text().isEmpty()) {
			ui.labelWarning->setStyleSheet("color:red");
			ui.labelWarning->setText(QString::fromLocal8Bit("密码不能为空！"));
		} else if (!rm->studentExist(id)) {
			Student student(id);
			if (rm->addStudent(id, ui.linePassword->text().toStdString())) {
				ui.labelWarning->setStyleSheet("color:green");
				ui.labelWarning->setText(QString::fromLocal8Bit("注册成功！"));
				this->hide();
				StudentMainWidget* smw = new StudentMainWidget(this, Student(id), rm);
				smw->show();
			} else {
				rm->deleteStudent(id);
				ui.labelWarning->setStyleSheet("color:red");
				ui.labelWarning->setText(QString::fromLocal8Bit("注册失败！"));
			}
		} else {
			ui.labelWarning->setStyleSheet("color:red");
			ui.labelWarning->setText(QString::fromLocal8Bit("用户已存在！"));
		}
	} else {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("用户名不合法（9位学号）！"));
	}
}
