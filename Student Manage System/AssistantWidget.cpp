#include "AssistantWidget.h"
#include "qmessagebox.h"

AssistantWidget::AssistantWidget(Student* student, CourseManager* cm, int id, OwnCourseWidget *father, QWidget *parent)
	: student(student), cm(cm), id(id), father(father), QWidget(parent) {
	ui.setupUi(this);
	syncList();
}

AssistantWidget::~AssistantWidget() {
	student = NULL;
	delete student;
	cm = NULL;
	delete cm;
	father = NULL;
	delete father;
}

void AssistantWidget::enrollAssistant() {
	if (course.containAssistant(*student)) {
		cm->deleteAssistant(id, *student);
	} else {
		cm->addAssistant(id, *student);
	}
	syncList();
}

void AssistantWidget::selectAssistant() {
	if (ui.listStudent->currentRow() == -1) {
		QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("未选择课程！"));
		return;
	}
	if (course.getAssistant(ui.listStudent->currentRow()) == *student) {
		QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("不能选择自己做助教！"));
	} else {
		Student assistant = course.getAssistant(ui.listStudent->currentRow());
		student->setAssistant(id, assistant);
		cm->addStudentToAssistant(id, assistant, *student);
	}
	syncList();
}

void AssistantWidget::changeExempt() {
	cm->setExempt(id, *student, cm->isExempt(id, *student) ^ 1);
	syncList();
	father->syncCourse();
}

void AssistantWidget::syncList() {
	ui.listStudent->clear();
	course = cm->getCourseByID(id);
	ui.labelCourse->setText(QString::fromLocal8Bit((course.name + " " + course.teacher).c_str()));
	string curAssist = student->getAssistant(id).id;
	ui.labelAssist->setText(QString::fromStdString(curAssist == "Null" ? "" : curAssist));
	ui.btnEnrollAssist->setText(QString::fromLocal8Bit(course.containAssistant(*student) ? UNENROLL_STR.c_str() : ENROLL_STR.c_str()));
	for (int i = 0; i < course.assistSize(); ++i) {
		ui.listStudent->addItem(QString::fromStdString(course.getAssistant(i).id));
	}
	ui.btnExempt->setText(course.isExempt(*student) ? QString::fromLocal8Bit("取消免修\n不免考") : QString::fromLocal8Bit("免修不免考"));
}
