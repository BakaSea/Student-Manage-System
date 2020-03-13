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
}

Course::Course(int id, string name, string teacher, int cap, int cnt, CourseType type) : 
	id(id), name(name), teacher(teacher), cap(cap), cnt(cnt), type(type) {
	vecStu.clear();
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

void Course::setCnt(int x) {
	cnt = x;
}

void Course::addCnt() {
	cnt++;
}
