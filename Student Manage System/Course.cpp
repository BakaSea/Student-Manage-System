#include "Course.h"
#include <qdebug.h>
#include <qdir.h>
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qiodevice.h>

Course::Course() : id(0), name(""), teacher(""), cap(0), type(SPEC) {
	init();
}

Course::Course(int id, string name, string teacher, int cap, int cnt, CourseType type) : 
	id(id), name(name), teacher(teacher), cap(cap), type(type) {
	init();
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
		QJsonObject objStu;
		objStu.insert("name", QJsonValue(QString::fromStdString(vecStu[i].id)));
		objStu.insert("exempt", QJsonValue(mapExempt[vecStu[i].id]));
		objStu.insert("score", QJsonValue(mapScore[vecStu[i].id]));
		arrayStu.append(objStu);
	}
	for (int i = 0; i < vecAssist.size(); ++i) {
		QJsonArray arrayAStu;
		for (int j = 0; j < vecAStu[i].size(); ++j) {
			arrayAStu.append(QJsonValue(QString::fromStdString(vecAStu[i][j].id)));
		}
		QJsonObject objAStu;
		objAStu.insert(QString::fromStdString(vecAssist[i].id), arrayAStu);
		arrayAssist.append(objAStu);
	}
	obj.insert("student", arrayStu);
	obj.insert("assistant", arrayAssist);
	QJsonDocument jdoc(obj);
	fp.write(jdoc.toJson());
	fp.close();
}

void Course::sync() {
	//从json中读入
	init();
	QFile fp(QString::fromStdString("./data/course/" + to_string(id) + ".json"));
	if (!fp.open(QIODevice::ReadOnly)) {
		qDebug() << "File open failed!";
		return;
	}
	QJsonDocument jdoc(QJsonDocument::fromJson(fp.readAll()));
	fp.close();
	QJsonObject obj = jdoc.object();
	QJsonArray arrayStu = obj.value("student").toArray(), arrayAssist = obj.value("assistant").toArray();
	for (int i = 0; i < arrayStu.size(); ++i) {
		QJsonObject objStu = arrayStu.at(i).toObject();
		Student student = Student(obj.value("name").toString().toStdString());
		vecStu.push_back(student);
		mapExempt[student.id] = objStu.value("exempt").toBool();
		mapScore[student.id] = objStu.value("score").toInt();
	}
	for (int i = 0; i < arrayAssist.size(); ++i) {
		QJsonObject objAStu = arrayAssist.at(i).toObject();
		Student assistant = Student(objAStu.keys()[0].toStdString());
		vecAssist.push_back(assistant);
		vecAStu.push_back(vector<Student>());
		QJsonArray arrayAStu = objAStu.value(objAStu.keys()[0]).toArray();
		for (int j = 0; j < arrayAStu.size(); ++j) {
			Student student = Student(arrayAStu[j].toString().toStdString());
			vecAStu[i].push_back(student);
		}
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
	update();
}

void Course::deleteStudent(Student student) {
	for (int i = 0; i < vecStu.size(); ++i) {
		if (vecStu[i] == student) {
			vecStu.erase(vecStu.begin() + i);
			break;
		}
	}
	update();
}

void Course::addAssistant(Student student) {
	vecAssist.push_back(student);
	vecAStu.push_back(vector<Student>());
	update();
}

void Course::deleteAssistant(Student student) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == student) {
			vecAssist.erase(vecAssist.begin() + i);
			vecAStu.erase(vecAStu.begin() + i);
			break;
		}
	}
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

bool Course::containAssistant(Student assistant) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			return true;
		}
	}
	return false;
}

void Course::addStudentToAssistant(Student assistant, Student student) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			vecAStu[i].push_back(student);
		}
	}
	update();
}

void Course::deleteStudentToAssistant(Student assistant, Student student) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			for (int j = 0; j < vecAStu[i].size(); ++i) {
				if (vecAStu[i][j] == student) {
					vecAStu[i].erase(vecAStu[i].begin() + j);
					break;
				}
			}
			break;
		}
	}
	update();
}

vector<Student> Course::getAStudent(Student assistant) {
	for (int i = 0; i < vecAssist.size(); ++i) {
		if (vecAssist[i] == assistant) {
			return vecAStu[i];
		}
	}
	return vector<Student>();
}

void Course::setExempt(Student student, bool exempt) {
	if (exempt) {
		mapExempt[student.id] = true;
	} else {
		mapExempt.erase(student.id);
	}
}

bool Course::isExempt(Student student) {
	return mapExempt.find(student.id) != mapExempt.end();
}

vector<Student> Course::getExemptStudent() {
	vector<Student> vecExempt;
	vecExempt.clear();
	for (unordered_map<string, bool>::iterator iter = mapExempt.begin(); iter != mapExempt.end(); ++iter) {
		vecExempt.push_back(Student(iter->first));
	}
	return vecExempt;
}

void Course::setScore(Student student, int score) {
	mapScore[student.id] = score;
}

int Course::getScore(Student student) {
	unordered_map<string, int>::iterator iter = mapScore.find(student.id);
	return iter == mapScore.end() ? 0 : iter->second;
}

void Course::init() {
	vecStu.clear();
	vecAssist.clear();
	vecAStu.clear();
	mapExempt.clear();
	mapScore.clear();
}
