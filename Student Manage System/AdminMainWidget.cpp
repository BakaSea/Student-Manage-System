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

AdminMainWidget::AdminMainWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	childWidget.clear();
	if (QFile::exists("./data/course/currentcourse.txt")) {
		ui.btnInputCourse->setEnabled(false);
	}
}

AdminMainWidget::~AdminMainWidget() {

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
	CourseWidget* cw = new CourseWidget(CourseWidget::ADMIN);
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