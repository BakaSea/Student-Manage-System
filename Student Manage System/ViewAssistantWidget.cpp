#include "ViewAssistantWidget.h"

ViewAssistantWidget::ViewAssistantWidget(Course *course, Student assistant, QWidget *parent)
	: course(course), assistant(assistant), QWidget(parent) {
	ui.setupUi(this);
	ui.labelName->setText(QString::fromLocal8Bit((assistant.id + "的学生名单").c_str()));
	vecAStudent = course->getAStudent(assistant);
	for (int i = 0; i < vecAStudent.size(); ++i) {
		ui.listStudent->addItem(new QListWidgetItem(QString::fromStdString(vecAStudent[i].id)));
	}
}

ViewAssistantWidget::~ViewAssistantWidget() {

}
