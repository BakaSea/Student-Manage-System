#include "ModifyPasswordWidget.h"
#include <qmessagebox.h>

ModifyPasswordWidget::ModifyPasswordWidget(Student student, RegistryManager *rm, QWidget *parent)
	: student(student), rm(rm), QWidget(parent) {
	ui.setupUi(this);
}

ModifyPasswordWidget::~ModifyPasswordWidget() {
	rm = NULL;
	delete rm;
}

void ModifyPasswordWidget::confirm() {
	if (rm->loginSuccess(student.id, ui.lineOldPassword->text().toStdString())) {
		if (ui.lineNewPassword->text().isEmpty()) {
			QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("新密码不能为空！"));
		} else {
			rm->changePassword(student.id, ui.lineNewPassword->text().toStdString());
			QMessageBox::information(this, "Confirm", QString::fromLocal8Bit("修改成功！"));
			this->close();
		}
	} else {
		QMessageBox::warning(this, "Warning", QString::fromLocal8Bit("旧密码错误！"));
	}
}
