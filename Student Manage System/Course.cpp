#include "Course.h"

string Course::getTypeName() {
	if (type == SPEC) {
		return "专业课";
	}
	if (type == NONSPEC) {
		return "非专业课";
	}
	return string();
}

Course::CourseType Course::getType(string type) {
	if (type == "专业课") {
		return SPEC;
	} else {
		return NONSPEC;
	}
}
