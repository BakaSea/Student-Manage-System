﻿#include "CourseWidget.h"
#include <stdio.h>
#include "AddCourseWidget.h"
#include "ModifyCourseWidget.h"
#include "ViewCourseWidget.h"
#include <qdir.h>
#include <qmessagebox.h>
#include <qfile.h>

CourseWidget::CourseWidget(UserType userType, QWidget *parent)
	: userType(userType), QWidget(parent) {
	ui.setupUi(this);
	cm = new CourseManager();
	syncCourse();
	ui.btnAddCourse->setVisible(true);
	ui.btnDeleteCourse->setVisible(true);
	ui.btnModifyCourse->setVisible(true);
	ui.btnSelectCourse->setVisible(false);
}

CourseWidget::CourseWidget(UserType userType, Student student, QWidget* parent)
	: userType(userType), student(student), QWidget(parent) {
	ui.setupUi(this);
	cm = new CourseManager();
	syncCourse();
	ui.btnSelectCourse->setVisible(true);
	ui.btnAddCourse->setVisible(false);
	ui.btnDeleteCourse->setVisible(false);
	ui.btnModifyCourse->setVisible(false);
}

CourseWidget::~CourseWidget() {

}

void CourseWidget::addCourse() {
	AddCourseWidget* acw = new AddCourseWidget(this);
	childWidget.push_back(acw);
	acw->show();
}

void CourseWidget::deleteCourse() {
	for (int i = 0, j = 0; j < cm->size(); ++i, ++j) {
		if (ui.tableCourse->item(i, 6)->checkState() == Qt::Checked) {
			if (!cm->getCourse(j).getCnt()) {
				QFile::remove(QString::fromLocal8Bit(("./data/course/" + to_string(cm->getCourse(j).id) + ".json").c_str()));
				cm->deleteCourse(j);
				j--;
			} else {
				//TODO
			}
		}
	}
	syncTable();
}

void CourseWidget::modifyCourse() {
	if (cm->empty()) {
		QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("当前无课程！"));
	} else {
		ModifyCourseWidget* mcw = new ModifyCourseWidget(this, ui.tableCourse->currentRow());
		childWidget.push_back(mcw);
		mcw->show();
	}
}

void CourseWidget::viewCourse(int row, int col) {
	if (userType == ADMIN) {
		ViewCourseWidget* vcw = new ViewCourseWidget(this, row);
		childWidget.push_back(vcw);
		vcw->show();
	}
}

void CourseWidget::selectCourse() {
	for (int i = 0; i < cm->size(); ++i) {
		if (!student.contain(cm->getCourse(i).id)) {
			if (ui.tableCourse->item(i, 6)->checkState() == Qt::Checked) {
				if (!cm->getCourse(i).full()) {
					student.addCourse(cm->getCourse(i).id);
					cm->addStudent(i, student);
				} else {
					//TODO
				}
			}
		}
	}
	syncTable();
}

void CourseWidget::refresh() {
	syncCourse();
}

void CourseWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}

void CourseWidget::syncCourse() {
	cm->sync();
	syncTable();
}

void CourseWidget::syncTable() {
	ui.tableCourse->clearContents();
	ui.tableCourse->setRowCount(cm->size());
	for (int i = 0; i < cm->size(); ++i) {
		ui.tableCourse->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(cm->getCourse(i).id, 3, 10, QChar('0'))));
		ui.tableCourse->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(cm->getCourse(i).name.c_str())));
		ui.tableCourse->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(cm->getCourse(i).teacher.c_str())));
		ui.tableCourse->setItem(i, 3, new QTableWidgetItem(QString::number(cm->getCourse(i).cap)));
		ui.tableCourse->setItem(i, 4, new QTableWidgetItem(QString::number(cm->getCourse(i).getCnt())));
		ui.tableCourse->setItem(i, 5, new QTableWidgetItem(QString::fromLocal8Bit(cm->getCourse(i).getTypeName().c_str())));
		if (userType == ADMIN) {
			QTableWidgetItem* check = new QTableWidgetItem();
			check->setCheckState(Qt::Unchecked);
			ui.tableCourse->setItem(i, 6, check);
		}
		if (userType == STUDENT) {
			if (!student.contain(cm->getCourse(i).id)) {
				QTableWidgetItem* check = new QTableWidgetItem();
				check->setCheckState(Qt::Unchecked);
				ui.tableCourse->setItem(i, 6, check);
			}
		}
	}
}