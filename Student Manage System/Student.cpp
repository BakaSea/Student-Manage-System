#include "Student.h"
#include <qdir.h>
#include <qfile.h>
#include <qdebug.h>
#include <qtextstream.h>
#include <qiodevice.h>

Student::Student() {
	mapCA.clear();
	id = "Null";
}

Student::Student(string id) : id(id) {
	sync();
}

Student::Student(const Student& A) {
	id = A.id;
	mapCA.clear();
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

void Student::deleteAssistant(int id) {
	setAssistant(id, Student());
}

Student Student::getAssistant(int id) {
	return mapCA.find(id)->second;
}

void Student::sync() {
	if (id == "Null") return;
	mapCA.clear();
	QFile fp(QString::fromStdString("./data/student/" + id + ".txt"));
	if (!fp.open(QIODevice::ReadOnly)) {
		qDebug() << "File open failed!";
		return;
	}
	QTextStream in(&fp);
	in.setCodec("UTF-8");
	while (!in.atEnd()) {
		QStringList lineList = in.readLine().split('\t');
		int id = lineList[0].toInt();
		addCourse(id);
		setAssistant(id, Student(lineList[1].toStdString()));
	}
	fp.close();
}

void Student::update() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/student")) {
		dir.mkdir("./data/student");
	}
	QFile fp(QString::fromStdString("./data/student/" + id + ".txt"));
	if (!fp.open(QIODevice::WriteOnly)) {
		qDebug() << "File open failed!";
		return;
	}
	QTextStream out(&fp);
	out.setCodec("UTF-8");
	for (map<int, Student>::iterator iter = mapCA.begin(); iter != mapCA.end(); ++iter) {
		out << QString("%1").arg(iter->first, 3, 10, QChar('0')) << '\t' << QString::fromStdString(iter->second.id) << endl;
	}
	fp.close();
}
