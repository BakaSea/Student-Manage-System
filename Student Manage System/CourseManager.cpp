#include "CourseManager.h"
#include <qdir.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qtextstream.h>
#include <qdebug.h>

CourseManager::CourseManager() {
	vecCourse.clear();
}

CourseManager::~CourseManager() {
	vecCourse.clear();
}

Course CourseManager::getCourse(int index) {
	return vecCourse[index];
}

Course CourseManager::getCourseByID(int id) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			return vecCourse[i];
		}
	}
	return Course();
}

void CourseManager::addCourse(Course course) {
	vecCourse.push_back(course);
	update();
}

void CourseManager::deleteCourse(int index) {
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
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			if (vecCourse[i].containAssistant(student)) {
				vecCourse[i].deleteAssistant(student);
				updateAssistant();
			}
			vecCourse[i].deleteStudent(student);
			break;
		}
	}
	update();
}

void CourseManager::addAssistant(int id, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			vecCourse[i].addAssistant(student);
			break;
		}
	}
	updateAssistant();
}

void CourseManager::deleteAssistant(int id, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			vecCourse[i].deleteAssistant(student);
			break;
		}
	}
	updateAssistant();
}

void CourseManager::addStudentToAssistant(int id, Student assistant, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			vecCourse[i].addStudentToAssistant(assistant, student);
			break;
		}
	}
}

void CourseManager::deleteStudentToAssistant(int id, Student assistant, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			vecCourse[i].deleteStudentToAssistant(assistant, student);
			break;
		}
	}
}

void CourseManager::setExempt(int id, Student student, bool exempt) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			vecCourse[i].setExempt(student, exempt);
			break;
		}
	}
}

bool CourseManager::isExempt(int id, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			return vecCourse[i].isExempt(student);
		}
	}
	return false;
}

void CourseManager::setScore(int id, Student student, int score) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			vecCourse[i].setScore(student, score);
			break;
		}
	}
}

int CourseManager::getScore(int id, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].id == id) {
			return vecCourse[i].getScore(student);
		}
	}
	return 0;
}

void CourseManager::update() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/course")) {
		dir.mkdir("./data/course");
	}
	QFile fp("./data/course/currentcourse.txt");
	if (!fp.open(QIODevice::WriteOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QTextStream out(&fp);
	out.setCodec("UTF-8");
	for (int i = 0; i < vecCourse.size(); ++i) {
		out << QString("%1").arg(vecCourse[i].id, 3, 10, QChar('0')) << "\t" << QString::fromLocal8Bit(vecCourse[i].name.c_str()) << "\t"
			<< QString::fromLocal8Bit(vecCourse[i].teacher.c_str()) << "\t" << QString::number(vecCourse[i].cap) << "\t"
			<< QString::number(vecCourse[i].getCnt()) << "\t" << QString::fromLocal8Bit(vecCourse[i].getTypeName().c_str()) << endl;
	}
	fp.close();
}

void CourseManager::updateAssistant() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/course")) {
		dir.mkdir("./data/course");
	}
	QFile fp("./data/course/assistant.txt");
	if (!fp.open(QIODevice::WriteOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QTextStream out(&fp);
	out.setCodec("UTF-8");
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i].assistSize()) {
			out << QString("%1").arg(vecCourse[i].id, 3, 10, QChar('0')) << "\t";
			for (int j = 0; j < vecCourse[i].assistSize(); ++j) {
				out << QString::fromStdString(vecCourse[i].getAssistant(j).id);
				if (j == vecCourse[i].assistSize() - 1) {
					 out << endl;
				} else {
					out << ",";
				}
			}
		}
	}
	fp.close();
}

void CourseManager::sync() {
	vecCourse.clear();
	QFile fp("./data/course/currentcourse.txt");
	if (!fp.open(QIODevice::ReadOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QTextStream in(&fp);
	in.setCodec("UTF-8");
	while (!in.atEnd()) {
		int id, cap, cnt;
		string name, teacher, type;
		QStringList lineList = in.readLine().split('\t');
		id = lineList[0].toInt();
		name = lineList[1].toLocal8Bit().toStdString();
		teacher = lineList[2].toLocal8Bit().toStdString();
		cap = lineList[3].toInt();
		cnt = lineList[4].toInt();
		type = lineList[5].toLocal8Bit().toStdString();
		Course course = Course(id, name, teacher, cap, cnt, Course::getTypebyName(type));
		course.sync();
		vecCourse.push_back(course);
	}
	fp.close();
}
