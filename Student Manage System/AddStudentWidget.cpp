#include "AddStudentWidget.h"
#include <vector>
#include "Student.h"
#include <qmessagebox.h>
using namespace std;

AddStudentWidget::AddStudentWidget(CourseManager *cm, int index, RegistryManager *rm, ViewCourseWidget *father, CourseWidget *grandFather, QWidget *parent)
	: cm(cm), index(index), rm(rm), father(father), grandFather(grandFather), QWidget(parent) {
	ui.setupUi(this);
	syncTable();
}

AddStudentWidget::~AddStudentWidget() {
	cm = NULL;
	delete cm;
	rm = NULL;
	delete rm;
	father = NULL;
	delete father;
	grandFather = NULL;
	delete grandFather;
}

void AddStudentWidget::syncTable() {
	vector<Student> originStu = rm->getVector();
	vecStu.clear();
	for (int i = 0; i < originStu.size(); ++i) {
		if (!cm->getCourse(index).containStudent(originStu[i])) {
			vecStu.push_back(originStu[i]);
		}
	}
	ui.tableStudent->clearContents();
	ui.tableStudent->setRowCount(vecStu.size());
	for (int i = 0; i < vecStu.size(); ++i) {
		ui.tableStudent->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(vecStu[i].id)));
		QTableWidgetItem* check = new QTableWidgetItem();
		check->setCheckState(Qt::Unchecked);
		ui.tableStudent->setItem(i, 1, check);
	}
}


void AddStudentWidget::confirm() {
	int cnt = cm->getCourse(index).getCnt();
	for (int i = 0; i < ui.tableStudent->rowCount(); ++i) {
		if (ui.tableStudent->item(i, 1)->checkState() == Qt::Checked) {
			cnt++;
		}
	}
	for (int i = 0; i < ui.tableStudent->rowCount(); ++i) {
		if (ui.tableStudent->item(i, 1)->checkState() == Qt::Checked) {
			if (cnt > cm->getCourse(index).cap) {
				ui.tableStudent->item(i, 1)->setCheckState(Qt::Unchecked);
			} else {
				cm->addStudent(index, vecStu[i]);
				vecStu[i].sync();
				vecStu[i].addCourse(cm->getCourse(index).id);
				vecStu[i].update();
			}
		}
	}
	if (cnt > cm->getCourse(index).cap) {
		QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("选择的人数大于上限人数！"));
	} else {
		QMessageBox::information(this, "Confirm", QString::fromLocal8Bit("添加成功！"));
		syncTable();
		father->syncTable();
		grandFather->syncTable();
	}
}