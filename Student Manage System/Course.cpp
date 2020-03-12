#include "Course.h"

string Course::getTypeName() {
	if (type == SPEC) {
		return "רҵ��";
	}
	if (type == NONSPEC) {
		return "��רҵ��";
	}
	return string();
}

Course::CourseType Course::getType(string type) {
	if (type == "רҵ��") {
		return SPEC;
	} else {
		return NONSPEC;
	}
}
