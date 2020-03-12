#include "LoginWidget.h"
#include <stdio.h>
#include <string.h>
#include "AdminMainWidget.h"
#include "StudentMainWidget.h"

LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	syncStudentList();
}

void LoginWidget::loginStudent() {
	map<string, string>::iterator iter = mapStu.find(ui.lineUsername->text().toStdString());
	if (iter == mapStu.end()) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("�û�������"));
	} else {
		if (ui.linePassword->text().toStdString() == iter->second) {
			ui.labelWarning->setStyleSheet("color:green");
			ui.labelWarning->setText(QString::fromLocal8Bit("��¼�ɹ���"));
		} else {
			ui.labelWarning->setStyleSheet("color:red");
			ui.labelWarning->setText(QString::fromLocal8Bit("�������"));
		}
	}
}

void LoginWidget::loginAdmin() {
	if (ui.lineUsername->text() == "Admin") {
		if (ui.linePassword->text() == "admin") {
			ui.labelWarning->setStyleSheet("color:green");
			ui.labelWarning->setText(QString::fromLocal8Bit("��¼�ɹ���"));
			this->close();
			AdminMainWidget* amw = new AdminMainWidget();
			amw->show();
		} else {
			ui.labelWarning->setStyleSheet("color:red");
			ui.labelWarning->setText(QString::fromLocal8Bit("�������"));
		}
	} else {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("�û�������"));
	}
}

void LoginWidget::registerStudent() {
	string id = ui.lineUsername->text().toStdString();
	if (checkUsername(id)) {
		map<string, string>::iterator iter = mapStu.find(id);
		if (iter == mapStu.end()) {
			mapStu[id] = ui.linePassword->text().toStdString();
			FILE* fp = fopen(id.c_str(), "w");
			if (fp == NULL) {
				ui.labelWarning->setStyleSheet("color:red");
				ui.labelWarning->setText(QString::fromLocal8Bit("ע��ʧ�ܣ�"));
			} else {
				fclose(fp);
				if (updateStudentList()) {
					ui.labelWarning->setStyleSheet("color:green");
					ui.labelWarning->setText(QString::fromLocal8Bit("ע��ɹ���"));
				} else {
					ui.labelWarning->setStyleSheet("color:red");
					ui.labelWarning->setText(QString::fromLocal8Bit("ע��ʧ�ܣ�"));
				}
			}
			
		} else {
			ui.labelWarning->setStyleSheet("color:red");
			ui.labelWarning->setText(QString::fromLocal8Bit("�û��Ѵ��ڣ�"));
		}
	} else {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("�û������Ϸ���9λѧ�ţ���"));
	}
}

void LoginWidget::syncStudentList() {
	mapStu.clear();
	FILE* fp = fopen("student.txt", "r");
	if (fp != NULL) {
		char str[50];
		string id, password;
		while (!feof(fp)) {
			int flag = 0;
			id.clear();
			password.clear();
			fscanf(fp, "%s", str);
			for (int i = 0; i < strlen(str); ++i) {
				if (!flag && str[i] == ',') {
					flag = 1;
				} else {
					if (!flag) {
						id.push_back(str[i]);
					} else {
						password.push_back(str[i]);
					}
				}
			}
			mapStu[id] = password;
		}
		fclose(fp);
	}
}

int LoginWidget::updateStudentList() {
	FILE* fp = fopen("student.txt", "w");
	if (fp == NULL) {
		return 0;
	}
	for (map<string, string>::iterator iter = mapStu.begin(); iter != mapStu.end(); ++iter) {
		fprintf(fp, "%s,%s\n", (iter->first).c_str(), (iter->second).c_str());
	}
	fclose(fp);
	return 1;
}

bool LoginWidget::checkUsername(string name) {
	if (name.size() != 9) return false;
	for (int i = 0; i < name.size(); ++i) {
		if (!isdigit(name[i])) return false;
	}
	return true;
}
