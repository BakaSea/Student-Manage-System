#include "AdminMainWidget.h"
#include "CourseWidget.h"
#include "LoginWidget.h"
#include <qmessagebox.h>
#include "Course.h"
#include <qfile.h>
#include <qdir.h>
#include <qiodevice.h>
#include <qtextstream.h>
#include <qfiledialog.h>
#include <qtextcodec.h>

AdminMainWidget::AdminMainWidget(RegistryManager *rm, QWidget *parent)
	: rm(rm), QWidget(parent) {
	ui.setupUi(this);
	childWidget.clear();
	if (QFile::exists("./data/course/currentcourse.txt")) {
		ui.btnInputCourse->setEnabled(false);
	}
}

AdminMainWidget::~AdminMainWidget() {
	rm = NULL;
	delete rm;
}

void AdminMainWidget::inputCourse() {
	QString path = QFileDialog::getOpenFileName(this, "", ".", "(*.txt)");
	QFile fp1(path);
	if (!fp1.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this, "Error", QString::fromLocal8Bit("录入失败！"));
	} else {
		QDir dir;
		if (!dir.exists("./data")) {
			dir.mkdir("./data");
		}
		if (!dir.exists("./data/course")) {
			dir.mkdir("./data/course");
		}
		QFile fp2("./data/course/currentcourse.txt");
		if (!fp2.open(QIODevice::WriteOnly)) {
			QMessageBox::critical(this, "Error", QString::fromLocal8Bit("录入失败！"));
		} else {
			//文件编码转化
			QByteArray originText = fp1.readAll();
			QTextCodec::ConverterState state;
			QTextCodec* codec = QTextCodec::codecForName("UTF-8");
			QString newText = codec->toUnicode(originText.constData(), originText.size(), &state);
			if (state.invalidChars > 0) {
				newText = QTextCodec::codecForName("GBK")->toUnicode(originText);
			} else {
				newText = originText;
			}
			fp2.write(newText.toUtf8());
			fp2.close();
			QMessageBox::information(this, "Confirm", QString::fromLocal8Bit("录入成功！"));
			ui.btnInputCourse->setEnabled(false);
		}
		fp1.close();
	}
}

void AdminMainWidget::viewCourse() {
	CourseWidget* cw = new CourseWidget(CourseWidget::ADMIN, rm);
	childWidget.push_back(cw);
	cw->show();
}

void AdminMainWidget::inputStudent() {
	QString path = QFileDialog::getOpenFileName(this, "", ".", "(*.csv)");
	QFile fp(path);
	if (!fp.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this, "Error", QString::fromLocal8Bit("导入失败！"));
	} else {
		QTextStream in(&fp);
		int success = 0, fail = 0;
		while (!in.atEnd()) {
			string id = in.readLine().toStdString();
			if (rm->checkUsername(id)) {
				if (!rm->studentExist(id)) {
					rm->addStudent(id, "123456");
				}
				success++;
			} else {
				fail++;
			}
		}
		fp.close();
		QMessageBox::information(this, "Confirm", QString(QString::fromLocal8Bit("共导入%1个，成功%2个，失败%3个")).arg(success + fail).arg(success).arg(fail));
	}
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