#include "ViewCourseWidget.h"
#include "ViewAssistantWidget.h"
#include <qfiledialog.h>
#include <qiodevice.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include "AddStudentWidget.h"

ViewCourseWidget::ViewCourseWidget(CourseManager *cm, int index, RegistryManager *rm, CourseWidget *father, QWidget *parent)
	: cm(cm), index(index), rm(rm), father(father), QWidget(parent) {
	ui.setupUi(this);
	syncTable();
}

ViewCourseWidget::~ViewCourseWidget() {
	childWidget.clear();
	rm = NULL;
	delete rm;
	cm = NULL;
	delete cm;
	father = NULL;
	delete father;
}

void ViewCourseWidget::inputScore() {
	QString path = QFileDialog::getOpenFileName(this, "", ".", "(*.csv)");
	QFile fp(path);
	if (!fp.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this, "Error", QString::fromLocal8Bit("导入失败！"));
	} else {
		QTextStream in(&fp);
		int success = 0, fail = 0;
		while (!in.atEnd()) {
			QStringList lineList = in.readLine().split(',');
			Student student = Student(lineList[0].toStdString());
			int score = lineList[1].toInt();
			if (course.containStudent(student) && 0 <= score && score <= 100) {
				cm->setScore(index, student, score);
				success++;
			} else {
				fail++;
			}
		}
		fp.close();
		QMessageBox::information(this, "Confirm", QString(QString::fromLocal8Bit("共导入%1个，成功%2个，失败%3个")).arg(success + fail).arg(success).arg(fail));
		syncTable();
	}
}

void ViewCourseWidget::addStudent() {
	AddStudentWidget* asw = new AddStudentWidget(cm, index, rm, this, father);
	childWidget.push_back(asw);
	asw->show();
}

void ViewCourseWidget::refresh() {
	syncTable();
}

void ViewCourseWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}

void ViewCourseWidget::syncTable() {
	course = cm->getCourse(index);
	setWindowTitle(QString::fromLocal8Bit("课程ID: ") + QString::number(course.id));
	ui.labelName->setText(QString::fromLocal8Bit(course.name.c_str()));
	ui.labelTeacher->setText(QString::fromLocal8Bit(course.teacher.c_str()));
	ui.labelCnt->setText(QString::number(course.getCnt()) + "/" + QString::number(course.cap));
	ui.tableStudent->clearContents();
	ui.tableStudent->setRowCount(course.getCnt());
	for (int i = 0; i < course.getCnt(); ++i) {
		Student student = course.getStudent(i);
		ui.tableStudent->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(student.id)));
		int score = course.getScore(student);
		ui.tableStudent->setItem(i, 1, new QTableWidgetItem(course.isExempt(student) ? QString::fromLocal8Bit("是") : QString::fromLocal8Bit("否")));
		ui.tableStudent->setItem(i, 2, new QTableWidgetItem(score == -1 ? QString::fromLocal8Bit("未录入") : QString::number(score)));
	}
	for (int i = 0; i < course.assistSize(); ++i) {
		ui.listAssistant->addItem(QString::fromStdString(course.getAssistant(i).id));
	}
}

void ViewCourseWidget::viewAssistant(QListWidgetItem *item) {
	ViewAssistantWidget* vaw = new ViewAssistantWidget(course, course.getAssistant(ui.listAssistant->currentRow()));
	childWidget.push_back(vaw);
	vaw->show();
}
