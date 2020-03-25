#include "CourseManager.h"
#include <qdir.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qtextstream.h>
#include <qdebug.h>

CourseManager::CourseManager(RegistryManager *rm) : rm(rm) {
	vecCourse.clear();
}

CourseManager::~CourseManager() {
	vecCourse.clear();
	rm = NULL;
	delete rm;
}

Course* CourseManager::getCourse(int index) {
	return vecCourse[index];
}

Course* CourseManager::getCourseByID(int id) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i]->id == id) {
			return vecCourse[i];
		}
	}
	return new Course();
}

void CourseManager::addCourse(Course* course) {
	vecCourse.push_back(course);
	update();
}

void CourseManager::deleteCourse(int index) {
	vecCourse.erase(vecCourse.begin() + index);
	update();
}

void CourseManager::modifyCourse(int index, string teacher, int cap) {
	vecCourse[index]->teacher = teacher;
	vecCourse[index]->cap = cap;
	update();
}

int CourseManager::size() {
	return vecCourse.size();
}

bool CourseManager::empty() {
	return !size();
}

void CourseManager::addStudent(int index, Student student) {
	vecCourse[index]->addStudent(student);
	update();
}

void CourseManager::deleteStudent(int id, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i]->id == id) {
			if (vecCourse[i]->containAssistant(student)) {
				vecCourse[i]->deleteAssistant(student);
				updateAssistant();
			}
			vecCourse[i]->deleteStudent(student);
			break;
		}
	}
	update();
}

void CourseManager::addAssistant(int id, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i]->id == id) {
			vecCourse[i]->addAssistant(student);
			break;
		}
	}
	updateAssistant();
}

void CourseManager::deleteAssistant(int id, Student student) {
	for (int i = 0; i < vecCourse.size(); ++i) {
		if (vecCourse[i]->id == id) {
			vecCourse[i]->deleteAssistant(student);
			break;
		}
	}
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
	QFile fp("./data/course/currentcourse.txt");
	if (!fp.open(QIODevice::WriteOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QTextStream out(&fp);
	out.setCodec("UTF-8");
	for (int i = 0; i < vecCourse.size(); ++i) {
		out << QString("%1").arg(vecCourse[i]->id, 3, 10, QChar('0')) << "\t" << QString::fromLocal8Bit(vecCourse[i]->name.c_str()) << "\t"
			<< QString::fromLocal8Bit(vecCourse[i]->teacher.c_str()) << "\t" << QString::number(vecCourse[i]->cap) << "\t"
			<< QString::number(vecCourse[i]->getCnt()) << "\t" << QString::fromLocal8Bit(vecCourse[i]->getTypeName().c_str()) << endl;
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
		if (vecCourse[i]->assistSize()) {
			out << QString("%1").arg(vecCourse[i]->id, 3, 10, QChar('0')) << "\t";
			for (int j = 0; j < vecCourse[i]->assistSize(); ++j) {
				out << QString::fromStdString(vecCourse[i]->getAssistant(j).id);
				if (j == vecCourse[i]->assistSize() - 1) {
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
	vecOrder.clear();
	//添加课程
	QFile fpCourse("./data/course/currentcourse.txt");
	if (!fpCourse.open(QIODevice::ReadOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QTextStream inCourse(&fpCourse);
	inCourse.setCodec("UTF-8");
	while (!inCourse.atEnd()) {
		int id, cap, cnt;
		string name, teacher, type;
		QStringList lineList = inCourse.readLine().split('\t');
		if (lineList.size() < 6) {
			break;
		}
		id = lineList[0].toInt();
		name = lineList[1].toLocal8Bit().toStdString();
		teacher = lineList[2].toLocal8Bit().toStdString();
		cap = lineList[3].toInt();
		cnt = lineList[4].toInt();
		type = lineList[5].toLocal8Bit().toStdString();
		Course *course = new Course(id, name, teacher, cap, cnt, Course::getTypebyName(type));
		vecCourse.push_back(course);
	}
	fpCourse.close();
	vecOrder = vector<int>(vecCourse[vecCourse.size() - 1]->id + 1);
	for (int i = 0; i < vecCourse.size(); ++i) {
		vecOrder[vecCourse[i]->id] = i;
	}
	//添加助教
	QFile fpAssist("./data/course/assistant.txt");
	if (!fpAssist.open(QIODevice::ReadOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QTextStream inAssist(&fpAssist);
	inAssist.setCodec("UTF-8");
	while (!inAssist.atEnd()) {
		QStringList lineList = inAssist.readLine().split('\t');
		if (lineList.size() < 2) {
			break;
		}
		Course* course = getCourseByID(lineList[0].toInt());
		QStringList assistList = lineList[1].split(',');
		for (int i = 0; i < assistList.size(); ++i) {
			course->addAssistant(Student(assistList[i].toStdString()));
		}
		course = NULL;
		delete course;
	}
	fpAssist.close();
	//添加学生
	vector<Student> vecStudent = rm->getVector();
	for (int i = 0; i < vecStudent.size(); ++i) {
		QFile fpStudent(QString::fromStdString("./data/student/" + vecStudent[i].id + ".txt"));
		if (!fpStudent.open(QIODevice::ReadOnly)) {
			qDebug() << "File open failed";
			return;
		}
		Student student = Student(vecStudent[i].id);
		QTextStream inStudent(&fpStudent);
		inStudent.setCodec("UTF-8");
		while (!inStudent.atEnd()) {
			QStringList lineList = inStudent.readLine().split('\t');
			if (lineList.size() < 4) {
				break;
			}
			Course* course = vecCourse[vecOrder[lineList[0].toInt()]];
			string assistant = lineList[1].toStdString();
			bool exempt = lineList[2].toInt();
			int score = lineList[3].toInt();
			course->addStudent(student);
			if (assistant != "Null") {
				course->addStudentToAssistant(Student(assistant), student);
			}
			course->setExempt(student, exempt);
			if (score != -1) {
				course->setScore(student, score);
			}
			course = NULL;
			delete course;
		}
		fpStudent.close();
	}
}
