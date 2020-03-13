#include "AdminMainWidget.h"
#include "CourseWidget.h"
#include "LoginWidget.h"
#include <stdio.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "Course.h"

AdminMainWidget::AdminMainWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	childWidget.clear();
	FILE* fp = fopen("./data/course/currentcourse.txt", "r");
	if (fp != NULL) {
		ui.btnInputCourse->setEnabled(false);
		fclose(fp);
	}
}

AdminMainWidget::~AdminMainWidget() {

}

void AdminMainWidget::inputCourse() {
	string path = QFileDialog::getOpenFileName(this, "", ".", "(*.txt)").toLocal8Bit().toStdString();
	FILE* fp1 = fopen(path.c_str(), "r");
	if (fp1 == NULL) {
		QMessageBox::critical(this, "Error", QString::fromLocal8Bit("录入失败！"));
	} else {
		QDir dir;
		if (!dir.exists("./data")) {
			dir.mkdir("./data");
		}
		if (!dir.exists("./data/course")) {
			dir.mkdir("./data/course");
		}
		FILE* fp2 = fopen("./data/course/currentcourse.txt", "w");
		if (fp2 == NULL) {
			QMessageBox::critical(this, "Error", QString::fromLocal8Bit("录入失败！"));
		} else {
			int cap, cnt, id;
			char name[70], teacher[50], type[10];
			while (!feof(fp1)) {
				int x = fscanf(fp1, "%d\t%s\t%s\t%d\t%d\t%s", &id, name, teacher, &cap, &cnt, type);
				if (x == -1) break;
				fprintf(fp2, "%03d\t%s\t%s\t%d\t%d\t%s\n", id, name, teacher, cap, cnt, type);
				Course course = Course(id, name, teacher, cap, cnt, Course::getTypebyName(type));
				course.update();
			}
			fclose(fp2);
			QMessageBox::information(this, "Confirm", QString::fromLocal8Bit("录入成功！"));
			ui.btnInputCourse->setEnabled(false);
		}
		fclose(fp1);
	}
}

void AdminMainWidget::viewCourse() {
	CourseWidget* cw = new CourseWidget();
	childWidget.push_back(cw);
	cw->show();
}

void AdminMainWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}

void AdminMainWidget::logout() {
	this->close();
	LoginWidget* lw = new LoginWidget();
	lw->show();
}