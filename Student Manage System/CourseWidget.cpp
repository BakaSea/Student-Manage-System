#include "CourseWidget.h"
#include <stdio.h>
#include "AddCourseWidget.h"
#include "ModifyCourseWidget.h"
#include "ViewCourseWidget.h"
#include <qdir.h>
#include <qmessagebox.h>
#include <qfile.h>

CourseWidget::CourseWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	syncCourse();
}

CourseWidget::~CourseWidget() {

}

void CourseWidget::addCourse() {
	AddCourseWidget* acw = new AddCourseWidget(this);
	childWidget.push_back(acw);
	acw->show();
}

void CourseWidget::deleteCourse() {
	for (int i = 0, j = 0; j < vecCourse.size(); ++i, ++j) {
		if (ui.tableCourse->item(i, 6)->checkState() == Qt::Checked) {
			if (!vecCourse[j].getCnt()) {
				QFile::remove(QString::fromLocal8Bit(("./data/course/" + to_string(vecCourse[j].id)).c_str()));
				vecCourse.erase(vecCourse.begin()+j);
				j--;
			} else {

			}
		}
	}
	syncTable();
	updateCourse();
}

void CourseWidget::modifyCourse() {
	if (vecCourse.empty()) {
		QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("当前无课程！"));
	} else {
		ModifyCourseWidget* mcw = new ModifyCourseWidget(this, ui.tableCourse->currentRow());
		childWidget.push_back(mcw);
		mcw->show();
	}
}

void CourseWidget::viewCourse(int row, int col) {
	ViewCourseWidget* vcw = new ViewCourseWidget(this, row);
	childWidget.push_back(vcw);
	vcw->show();
}

void CourseWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}

void CourseWidget::syncCourse() {
	vecCourse.clear();
	FILE* fp = fopen("./data/course/currentcourse.txt", "r");
	if (fp != NULL) {
		int id, cap, cnt;
		char name[70], teacher[50], type[10];
		while (!feof(fp)) {
			int x = fscanf(fp, "%d\t%s\t%s\t%d\t%d\t%s", &id, name, teacher, &cap, &cnt, type);
			if (x == -1) break;
			Course course = Course(id, name, teacher, cap, cnt, Course::getTypebyName(type));
			course.sync();
			vecCourse.push_back(course);
		}
		fclose(fp);
	}
	syncTable();
}

void CourseWidget::syncTable() {
	ui.tableCourse->clearContents();
	ui.tableCourse->setRowCount(vecCourse.size());
	for (int i = 0; i < vecCourse.size(); ++i) {
		ui.tableCourse->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(vecCourse[i].id, 3, 10, QChar('0'))));
		ui.tableCourse->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].name.c_str())));
		ui.tableCourse->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].teacher.c_str())));
		ui.tableCourse->setItem(i, 3, new QTableWidgetItem(QString::number(vecCourse[i].cap)));
		ui.tableCourse->setItem(i, 4, new QTableWidgetItem(QString::number(vecCourse[i].getCnt())));
		ui.tableCourse->setItem(i, 5, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].getTypeName().c_str())));
		QTableWidgetItem* check = new QTableWidgetItem();
		check->setCheckState(Qt::Unchecked);
		ui.tableCourse->setItem(i, 6, check);
	}
}

void CourseWidget::updateCourse() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/course")) {
		dir.mkdir("./data/course");
	}
	FILE* fp = fopen("./data/course/currentcourse.txt", "w");
	if (fp == NULL) {
		return;
	}
	for (int i = 0; i < vecCourse.size(); ++i) {
		fprintf(fp, "%03d\t%s\t%s\t%d\t%d\t%s\n", vecCourse[i].id, vecCourse[i].name.c_str(), vecCourse[i].teacher.c_str(), vecCourse[i].cap, vecCourse[i].getCnt(), vecCourse[i].getTypeName().c_str());
	}
	fclose(fp);
}
