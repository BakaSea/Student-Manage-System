#include "ViewCourseWidget.h"

ViewCourseWidget::ViewCourseWidget(CourseWidget *father, int index, QWidget *parent)
	: father(father), index(index), QWidget(parent) {
	ui.setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("课程ID: ") + QString::number(father->vecCourse[index].id));
	ui.labelName->setText(QString::fromLocal8Bit(father->vecCourse[index].name.c_str()));
	ui.labelTeacher->setText(QString::fromLocal8Bit(father->vecCourse[index].teacher.c_str()));
	ui.labelCnt->setText(QString::number(father->vecCourse[index].getCnt()) + "/" + QString::number(father->vecCourse[index].cap));
	for (int i = 0; i < father->vecCourse[index].vecStu.size(); ++i) {
		ui.listStudent->addItem(QString::fromStdString(father->vecCourse[index].vecStu[i].id));
	}
	for (int i = 0; i < father->vecCourse[index].vecAssist.size(); ++i) {
		ui.listAssistant->addItem(QString::fromStdString(father->vecCourse[index].vecAssist[i].id));
	}
}

ViewCourseWidget::~ViewCourseWidget() {
	father = NULL;
	delete father;
}
