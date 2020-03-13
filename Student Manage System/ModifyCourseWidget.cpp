#include "ModifyCourseWidget.h"

ModifyCourseWidget::ModifyCourseWidget(CourseWidget *father, int index, QWidget *parent)
	: father(father), index(index), QWidget(parent) {
	ui.setupUi(this);
	ui.labelName->setText(QString::fromLocal8Bit(father->vecCourse[index].name.c_str()));
	ui.labelCnt->setText(QString::number(father->vecCourse[index].cnt));
	ui.lineTeacher->setText(QString::fromLocal8Bit(father->vecCourse[index].teacher.c_str()));
	ui.sbCap->setValue(father->vecCourse[index].cap);
}

ModifyCourseWidget::~ModifyCourseWidget() {
	father = NULL;
	delete father;
}

void ModifyCourseWidget::confirm() {
	if (!ui.lineTeacher->text().size()) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("授课教师不能为空！"));
	} else if (!ui.sbCap->value()) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("上限人数不能为0！"));
	} else if (ui.sbCap->value() < father->vecCourse[index].cnt) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString::fromLocal8Bit("上限人数小于已选人数！"));
	} else {
		father->vecCourse[index].teacher = ui.lineTeacher->text().toLocal8Bit().toStdString();
		father->vecCourse[index].cap = ui.sbCap->value();
		father->updateCourse();
		father->syncTable();
		this->close();
	}
}