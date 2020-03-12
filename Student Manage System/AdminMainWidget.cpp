#include "AdminMainWidget.h"
#include "CourseWidget.h"
#include "LoginWidget.h"
#include <stdio.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

AdminMainWidget::AdminMainWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	FILE* fp = fopen("currentcourse.txt", "r");
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
		QMessageBox::critical(NULL, "Error", QString::fromLocal8Bit("录入失败！"));
	} else {
		FILE* fp2 = fopen("currentcourse.txt", "w");
		if (fp2 == NULL) {
			QMessageBox::critical(NULL, "Error", QString::fromLocal8Bit("录入失败！"));
		} else {
			int cap, cnt;
			char id[10], name[70], teacher[50], type[10];
			while (!feof(fp1)) {
				fscanf(fp1, "%s\t%s\t%s\t%d\t%d\t%s", id, name, teacher, &cap, &cnt, type);
				fprintf(fp2, "%s\t%s\t%s\t%d\t%d\t%s\n", id, name, teacher, cap, cnt, type);
			}
			fclose(fp2);
			QMessageBox::information(NULL, "Confirm", QString::fromLocal8Bit("录入成功！"));
			ui.btnInputCourse->setEnabled(false);
		}
		fclose(fp1);
	}
}

void AdminMainWidget::viewCourse() {
	CourseWidget* cw = new CourseWidget();
	cw->show();
}

void AdminMainWidget::logout() {
	this->close();
	LoginWidget* lw = new LoginWidget();
	lw->show();
}