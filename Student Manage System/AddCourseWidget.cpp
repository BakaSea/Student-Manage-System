#include "AddCourseWidget.h"
#include <stdio.h>
#include "Course.h"

AddCourseWidget::AddCourseWidget(CourseWidget *father, QWidget *parent)
	: father(father), QWidget(parent) {
	ui.setupUi(this);
}

AddCourseWidget::~AddCourseWidget() {
	father = NULL;
	delete father;
}

void AddCourseWidget::confirm() {
	Course newCourse;
	newCourse.id = father->cm->empty() ? 1 : father->cm->getCourse(father->cm->size()-1).id+1;
	newCourse.name = ui.lineName->text().toLocal8Bit().toStdString();
	newCourse.teacher = ui.lineTeacher->text().toLocal8Bit().toStdString();
	newCourse.cap = ui.sbCap->value();
	newCourse.setCnt(0);
	newCourse.type = Course::getTypebyIndex(ui.cbType->currentIndex());
	if (!newCourse.name.size()) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("课程名称不能为空！"));
	} else if (!newCourse.teacher.size()) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("授课教师不能为空！"));
	} else if (!newCourse.cap) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("上限人数不能为0！"));
	} else {
		newCourse.update();
		father->cm->addCourse(newCourse);
		father->syncTable();
		this->close();
	}
}