#include "OwnCourseWidget.h"
#include <map>
#include "AssistantWidget.h"

OwnCourseWidget::OwnCourseWidget(Student *student, QWidget *parent)
	: student(student), QWidget(parent) {
	ui.setupUi(this);
	cm = new CourseManager();
	syncCourse();
}

OwnCourseWidget::~OwnCourseWidget() {
	childWidget.clear();
	delete cm;
	student = NULL;
	delete student;
}

void OwnCourseWidget::syncTable() {
	ui.tableCourse->clearContents();
	ui.tableCourse->setRowCount(vecCourse.size());
	for (int i = 0; i < vecCourse.size(); ++i) {
		Course course = cm->getCourseByID(vecCourse[i].first);
		ui.tableCourse->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(course.id, 3, 10, QChar('0'))));
		ui.tableCourse->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(course.name.c_str())));
		ui.tableCourse->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(course.teacher.c_str())));
		ui.tableCourse->setItem(i, 3, new QTableWidgetItem(QString::fromLocal8Bit(course.getTypeName().c_str())));
		if (vecCourse[i].second.id != "Null") {
			ui.tableCourse->setItem(i, 4, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].second.id.c_str())));
		}
		QTableWidgetItem* check = new QTableWidgetItem();
		check->setCheckState(Qt::Unchecked);
		ui.tableCourse->setItem(i, 5, check);
	}
}

void OwnCourseWidget::dropCourse() {
	for (int i = 0, j = 0; j < vecCourse.size(); ++i, ++j) {
		if (ui.tableCourse->item(i, 5)->checkState() == Qt::Checked) {
			student->deleteCourse(vecCourse[j].first);
			cm->deleteStudent(vecCourse[j].first, *student);
			vecCourse.erase(vecCourse.begin() + j);
			j--;
			//TODO
		}
	}
	syncTable();
}

void OwnCourseWidget::courseAssistant(int row, int col) {
	AssistantWidget* aw = new AssistantWidget(student, cm, vecCourse[row].first);
	childWidget.push_back(aw);
	aw->show();
}

void OwnCourseWidget::refresh() {
	syncCourse();
}

void OwnCourseWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}

void OwnCourseWidget::syncCourse() {
	cm->sync();
	student->sync();
	vecCourse.clear();
	vecCourse = student->getVector();
	syncTable();
}
