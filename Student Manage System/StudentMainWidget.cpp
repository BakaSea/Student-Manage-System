#include "StudentMainWidget.h"
#include "CourseWidget.h"
#include "OwnCourseWidget.h"
#include "ModifyPasswordWidget.h"

StudentMainWidget::StudentMainWidget(LoginWidget *father, Student student, RegistryManager *rm, QWidget *parent)
	: father(father), rm(rm), QWidget(parent) {
	ui.setupUi(this);
	this->student = new Student(student.id);
}

StudentMainWidget::~StudentMainWidget() {
	father = NULL;
	delete father;
	delete student;
}

void StudentMainWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}

void StudentMainWidget::logout() {
	father->show();
	this->close();
}

void StudentMainWidget::viewCourse() {
	CourseWidget* cw = new CourseWidget(CourseWidget::STUDENT, student);
	childWidget.push_back(cw);
	cw->show();
}

void StudentMainWidget::viewOwnCourse() {
	OwnCourseWidget* ocw = new OwnCourseWidget(student);
	childWidget.push_back(ocw);
	ocw->show();
}

void StudentMainWidget::modifyPassword() {
	ModifyPasswordWidget* mpw = new ModifyPasswordWidget(*student, rm);
	childWidget.push_back(mpw);
	mpw->show();
}
