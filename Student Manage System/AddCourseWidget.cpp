#include "AddCourseWidget.h"
#include <stdio.h>
#include "Course.h"

AddCourseWidget::AddCourseWidget(CourseWidget *father, CourseManager *cm, QWidget *parent)
	: father(father), cm(cm), QWidget(parent) {
	ui.setupUi(this);
}

AddCourseWidget::~AddCourseWidget() {
	father = NULL;
	delete father;
	cm = NULL;
	delete cm;
}

void AddCourseWidget::confirm() {
	Course *newCourse = new Course();
	newCourse->id = cm->empty() ? 1 : cm->getCourse(cm->size()-1)->id+1;
	newCourse->name = ui.lineName->text().toLocal8Bit().toStdString();
	newCourse->teacher = ui.lineTeacher->text().toLocal8Bit().toStdString();
	newCourse->cap = ui.sbCap->value();
	newCourse->type = Course::getTypebyIndex(ui.cbType->currentIndex());
	if (newCourse->name.empty()) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("课程名称不能为空！"));
	} else if (newCourse->teacher.empty()) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("授课教师不能为空！"));
	} else if (!newCourse->cap) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("上限人数不能为0！"));
	} else {
		cm->addCourse(newCourse);
		father->syncTable();
		this->close();
	}
}