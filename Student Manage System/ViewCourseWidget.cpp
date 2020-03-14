#include "ViewCourseWidget.h"

ViewCourseWidget::ViewCourseWidget(CourseWidget *father, int index, QWidget *parent)
	: father(father), index(index), QWidget(parent) {
	ui.setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("课程ID: ") + QString::number(father->cm->getCourse(index).id));
	ui.labelName->setText(QString::fromLocal8Bit(father->cm->getCourse(index).name.c_str()));
	ui.labelTeacher->setText(QString::fromLocal8Bit(father->cm->getCourse(index).teacher.c_str()));
	ui.labelCnt->setText(QString::number(father->cm->getCourse(index).getCnt()) + "/" + QString::number(father->cm->getCourse(index).cap));
	for (int i = 0; i < father->cm->getCourse(index).getCnt(); ++i) {
		ui.listStudent->addItem(QString::fromStdString(father->cm->getCourse(index).getStudent(i).id));
	}
	for (int i = 0; i < father->cm->getCourse(index).assistSize(); ++i) {
		ui.listAssistant->addItem(QString::fromStdString(father->cm->getCourse(index).getAssistant(i).id));
	}
}

ViewCourseWidget::~ViewCourseWidget() {
	father = NULL;
	delete father;
}
