#include "Course.h"
#include <qdebug.h>
#include <qdir.h>
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qiodevice.h>

Course::Course() {
	vecStu.clear();
	mapStu.clear();
}

Course::Course(int id, string name, string teacher, int cap, int cnt, CourseType type) : 
	id(id), name(name), teacher(teacher), cap(cap), type(type) {
	vecStu.clear();
	mapStu.clear();
}

string Course::getTypeName() {
	return type == SPEC ? "专业课" : "非专业课";
}

Course::CourseType Course::getTypebyName(string type) {
	return type == "专业课" ? SPEC : NONSPEC;
}

Course::CourseType Course::getTypebyIndex(int index) {
	return index ? NONSPEC : SPEC;
}

void Course::update() {
	//用json存储信息
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/course")) {
		dir.mkdir("./data/course");
	}
	QFile fp(QString::fromStdString("./data/course/" + to_string(id) + ".json"));
	if (!fp.open(QIODevice::WriteOnly)) {
		qDebug() << "File open failed!";
		return;
	}
	QJsonObject obj;
	QJsonArray arrayStu, arrayAssist;
	for (int i = 0; i < vecStu.size(); ++i) {
		arrayStu.append(QJsonValue(QString::fromStdString(vecStu[i].id)));
	}
	for (int i = 0; i < vecAssist.size(); ++i) {
		arrayAssist.append(QJsonValue(QString::fromStdString(vecAssist[i].id)));
	}
	obj.insert("student", arrayStu);
	obj.insert("assistant", arrayAssist);
	QJsonDocument jdoc(obj);
	fp.write(jdoc.toJson());
	fp.close();
}

void Course::sync() {
	//从json中读入
	vecStu.clear();
	vecAssist.clear();
	QFile fp(QString::fromStdString("./data/course/" + to_string(id) + ".json"));
	if (!fp.open(QIODevice::ReadOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QJsonDocument jdoc(QJsonDocument::fromJson(fp.readAll()));
	fp.close();
	QJsonObject obj = jdoc.object();
	QJsonArray arrayStu = obj.value("student").toArray(), arrayAssist = obj.value("assistant").toArray();
	for (int i = 0; i < arrayStu.size(); ++i) {
		vecStu.push_back(Student(arrayStu.at(i).toString().toStdString()));
	}
	for (int i = 0; i < arrayAssist.size(); ++i) {
		vecAssist.push_back(Student(arrayAssist.at(i).toString().toStdString()));
	}
}

int Course::getCnt() {
	return vecStu.size();
}

bool Course::full() {
	return vecStu.size() >= cap;
}

void Course::addStudent(Student student) {
	vecStu.push_back(student);
	mapStu[student] = vecStu.size() - 1;
	update();
}

void Course::deleteStudent(Student student) {
	vecStu.erase(vecStu.begin() + mapStu[student]);
	mapStu.erase(student);
	update();
}

void Course::addAssistant(Student student) {
	vecAssist.push_back(student);
	mapAssist[student] = vecAssist.size() - 1;
	update();
}

void Course::deleteAssistant(Student student) {
	vecAssist.erase(vecAssist.begin() + mapAssist[student]);
	mapAssist.erase(student);
	update();
}

Student Course::getStudent(int index) {
	return vecStu[index];
}

int Course::assistSize() {
	return vecAssist.size();
}

Student Course::getAssistant(int index) {
	return vecAssist[index];
}
