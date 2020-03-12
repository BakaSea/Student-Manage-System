#include "CourseWidget.h"
#include <stdio.h>

CourseWidget::CourseWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	syncCourse();
}

CourseWidget::~CourseWidget() {

}

void CourseWidget::syncCourse() {
	vecCourse.clear();
	FILE* fp = fopen("currentcourse.txt", "r");
	if (fp != NULL) {
		int id, cap, cnt;
		char name[70], teacher[50], type[10];
		while (!feof(fp)) {
			fscanf(fp, "%d\t%s\t%s\t%d\t%d\t%s\n", &id, name, teacher, &cap, &cnt, type);
			vecCourse.push_back(Course(id, name, teacher, cap, cnt, Course::getType(type)));
		}
		fclose(fp);
	}
	ui.tableCourse->setRowCount(vecCourse.size());
	for (int i = 0; i < vecCourse.size(); ++i) {
		ui.tableCourse->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(vecCourse[i].id, 3, 10, QChar('0'))));
		ui.tableCourse->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].name.c_str())));
		ui.tableCourse->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].teacher.c_str())));
		ui.tableCourse->setItem(i, 3, new QTableWidgetItem(QString::number(vecCourse[i].cap)));
		ui.tableCourse->setItem(i, 4, new QTableWidgetItem(QString::number(vecCourse[i].cnt)));
		ui.tableCourse->setItem(i, 5, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].getTypeName().c_str())));
	}
}

void CourseWidget::updateCourse() {

}
