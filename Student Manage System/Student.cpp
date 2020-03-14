#include "Student.h"
#include <stdio.h>
#include <qdir.h>

Student::Student() {
	mapCA.clear();
	id = "Null";
}

Student::Student(string id) : id(id) {
	mapCA.clear();
	sync();
}

bool Student::operator==(const Student& A) const {
	return id == A.id;
}

bool Student::operator<(const Student& A) const {
	return id < A.id;
}

int Student::size() {
	return mapCA.size();
}

bool Student::contain(int id) {
	return mapCA.find(id) != mapCA.end();
}

vector< pair<int, Student> > Student::getVector() {
	vector< pair<int, Student> > vec;
	vec.clear();
	for (map<int, Student>::iterator iter = mapCA.begin(); iter != mapCA.end(); ++iter) {
		vec.push_back(*iter);
	}
	return vec;
}

void Student::addCourse(int id) {
	mapCA[id] = Student();
	update();
}

void Student::deleteCourse(int id) {
	mapCA.erase(id);
	update();
}

void Student::setAssistant(int id, Student assistant) {
	mapCA[id] = assistant;
	update();
}

void Student::sync() {
	mapCA.clear();
	FILE* fp = fopen(("./data/student/" + id + ".txt").c_str(), "r");
	if (fp != NULL) {
		while (!feof(fp)) {
			int id;
			char name[20];
			int x = fscanf(fp, "%d\t%s", &id, name);
			if (x == -1) break;
			addCourse(id);
			setAssistant(id, Student(name));
		}
	}
}

void Student::update() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/student")) {
		dir.mkdir("./data/student");
	}
	FILE* fp = fopen(("./data/student/" + id + ".txt").c_str(), "w");
	if (fp == NULL) {
		return;
	}
	for (map<int, Student>::iterator iter = mapCA.begin(); iter != mapCA.end(); ++iter) {
		fprintf(fp, "%03d\t%s\n", iter->first, iter->second.id.c_str());
	}
	fclose(fp);
}
