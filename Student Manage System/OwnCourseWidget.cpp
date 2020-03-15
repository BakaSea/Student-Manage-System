#include "OwnCourseWidget.h"
#include <map>
#include "AssistantWidget.h"
#include "qmessagebox.h"

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
	int spec = 0, nonspec = 0;
	for (int i = 0; i < vecCourse.size(); ++i) {
		Course course = cm->getCourseByID(vecCourse[i].first);
		ui.tableCourse->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(course.id, 3, 10, QChar('0'))));
		ui.tableCourse->setItem(i, 1, new QTableWidgetItem(QString::fromLocal8Bit(course.name.c_str())));
		ui.tableCourse->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit(course.teacher.c_str())));
		ui.tableCourse->setItem(i, 3, new QTableWidgetItem(QString::fromLocal8Bit(course.getTypeName().c_str())));
		if (course.type == Course::SPEC) {
			spec++;
		} else {
			nonspec++;
		}
		if (vecCourse[i].second.id != "Null") {
			if (course.containAssistant(vecCourse[i].second)) {
				ui.tableCourse->setItem(i, 4, new QTableWidgetItem(QString::fromLocal8Bit(vecCourse[i].second.id.c_str())));
			} else {
				QMessageBox::warning(this, "Warning", QString::fromLocal8Bit((course.name + "的助教" + vecCourse[i].second.id + "已退课！").c_str()));
				student->deleteAssistant(vecCourse[i].first);
			}
		}
		QTableWidgetItem* check = new QTableWidgetItem();
		check->setCheckState(Qt::Unchecked);
		ui.tableCourse->setItem(i, 5, check);
	}
	if (spec < 4 || nonspec < 2) {
		ui.labelWarning->setStyleSheet("color:red");
		ui.labelWarning->setText(QString("%1%2%3%4%5").arg(QString::fromLocal8Bit("根据学院要求：目前课程不达标！仍差")).arg(spec > 4 ? 0 : 4 - spec)
			.arg(QString::fromLocal8Bit("门专业课，以及")).arg(nonspec > 2 ? 0 : 2 - nonspec).arg(QString::fromLocal8Bit("门非专业课！请及时选课！")));
	}
}

void OwnCourseWidget::dropCourse() {
	for (int i = 0, j = 0; j < vecCourse.size(); ++i, ++j) {
		if (ui.tableCourse->item(i, 5)->checkState() == Qt::Checked) {
			student->deleteCourse(vecCourse[j].first);
			cm->deleteStudent(vecCourse[j].first, *student);
			vecCourse.erase(vecCourse.begin() + j);
			j--;
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
