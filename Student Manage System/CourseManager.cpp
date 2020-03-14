#include "CourseManager.h"
#include <qdir.h>

CourseManager::CourseManager() {
	vecCourse.clear();
	mapCourse.clear();
}

CourseManager::~CourseManager() {
	vecCourse.clear();
	mapCourse.clear();
}

Course CourseManager::getCourse(int index) {
	return vecCourse[index];
}

Course CourseManager::getCourseByID(int id) {
	return vecCourse[mapCourse[id]];
}

void CourseManager::addCourse(Course course) {
	vecCourse.push_back(course);
	mapCourse[course.id] = vecCourse.size() - 1;
	update();
}

void CourseManager::deleteCourse(int index) {
	mapCourse.erase(vecCourse[index].id);
	vecCourse.erase(vecCourse.begin() + index);
	update();
}

void CourseManager::modifyCourse(int index, string teacher, int cap) {
	vecCourse[index].teacher = teacher;
	vecCourse[index].cap = cap;
	update();
}

int CourseManager::size() {
	return vecCourse.size();
}

bool CourseManager::empty() {
	return !size();
}

void CourseManager::addStudent(int index, Student student) {
	vecCourse[index].addStudent(student);
	update();
}

void CourseManager::deleteStudent(int id, Student student) {
	vecCourse[mapCourse[id]].deleteStudent(student);
	update();
}

void CourseManager::addAssistant(int id, Student student) {
	vecCourse[mapCourse[id]].addAssistant(student);
	updateAssistant();
}

void CourseManager::deleteAssistant(int id, Student student) {
	vecCourse[mapCourse[id]].deleteAssistant(student);
	updateAssistant();
}

void CourseManager::update() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/course")) {
		dir.mkdir("./data/course");
	}
	FILE* fp = fopen("./data/course/currentcourse.txt", "w");
	if (fp == NULL) {
		return;
	}
	for (int i = 0; i < vecCourse.size(); ++i) {
		fprintf(fp, "%03d\t%s\t%s\t%d\t%d\t%s\n", vecCourse[i].id, vecCourse[i].name.c_str(), vecCourse[i].teacher.c_str(), vecCourse[i].cap, vecCourse[i].getCnt(), vecCourse[i].getTypeName().c_str());
	}
	fclose(fp);
}

void CourseManager::updateAssistant() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/course")) {
		dir.mkdir("./data/course");
	}
	FILE* fp = fopen("./data/course/assistant.txt", "w");
	if (fp == NULL) {
		return;
	}
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].assistSize()) {
			fprintf(fp, "%03d\t", vecCourse[i].id);
			for (int j = 0; j < vecCourse[i].assistSize(); ++j) {
				if (j == vecCourse[i].assistSize() - 1) {
					fprintf(fp, "%s\n", vecCourse[i].getAssistant(j).id.c_str());
				} else {
					fprintf(fp, "%s,", vecCourse[i].getAssistant(j).id.c_str());
				}
			}
		}
	}
	fclose(fp);
}

void CourseManager::sync() {
	vecCourse.clear();
	mapCourse.clear();
	FILE* fp = fopen("./data/course/currentcourse.txt", "r");
	if (fp != NULL) {
		int id, cap, cnt;
		char name[70], teacher[50], type[10];
		while (!feof(fp)) {
			int x = fscanf(fp, "%d\t%s\t%s\t%d\t%d\t%s", &id, name, teacher, &cap, &cnt, type);
			if (x == -1) break;
			Course course = Course(id, name, teacher, cap, cnt, Course::getTypebyName(type));
			course.sync();
			vecCourse.push_back(course);
			mapCourse[id] = vecCourse.size()-1;
		}
		fclose(fp);
	}
}
