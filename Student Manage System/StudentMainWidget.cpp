#include "StudentMainWidget.h"
#include "CourseWidget.h"

StudentMainWidget::StudentMainWidget(LoginWidget *father, Student student, QWidget *parent)
	: father(father), student(student), QWidget(parent) {
	ui.setupUi(this);
}

StudentMainWidget::~StudentMainWidget() {
	father = NULL;
	delete father;
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

}

void StudentMainWidget::modifyPassword() {

}
