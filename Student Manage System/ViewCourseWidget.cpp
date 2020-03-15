#include "ViewCourseWidget.h"
#include "ViewAssistantWidget.h"

ViewCourseWidget::ViewCourseWidget(Course course, QWidget *parent)
	: course(course), QWidget(parent) {
	ui.setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("课程ID: ") + QString::number(course.id));
	ui.labelName->setText(QString::fromLocal8Bit(course.name.c_str()));
	ui.labelTeacher->setText(QString::fromLocal8Bit(course.teacher.c_str()));
	ui.labelCnt->setText(QString::number(course.getCnt()) + "/" + QString::number(course.cap));
	for (int i = 0; i < course.getCnt(); ++i) {
		ui.listStudent->addItem(QString::fromStdString(course.getStudent(i).id));
	}
	for (int i = 0; i < course.assistSize(); ++i) {
		ui.listAssistant->addItem(QString::fromStdString(course.getAssistant(i).id));
	}
}

ViewCourseWidget::~ViewCourseWidget() {
	childWidget.clear();
}

void ViewCourseWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}

void ViewCourseWidget::viewAssistant(QListWidgetItem* item) {
	ViewAssistantWidget* vaw = new ViewAssistantWidget(course, course.getAssistant(ui.listAssistant->currentRow()));
	childWidget.push_back(vaw);
	vaw->show();
}
