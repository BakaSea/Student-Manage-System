#include "ViewCourseWidget.h"

ViewCourseWidget::ViewCourseWidget(CourseWidget *father, int index, QWidget *parent)
	: father(father), index(index), QWidget(parent) {
	ui.setupUi(this);
}

ViewCourseWidget::~ViewCourseWidget() {

}
