#include "StudentMainWidget.h"

StudentMainWidget::StudentMainWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
}

StudentMainWidget::~StudentMainWidget() {

}

void StudentMainWidget::closeEvent(QCloseEvent* event) {
	for (int i = 0; i < childWidget.size(); ++i) {
		if (childWidget[i] != NULL) {
			childWidget[i]->close();
		}
	}
}
