#include "RegistryManager.h"
#include <qdir.h>
#include <qcryptographichash.h>
#include <string.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qdebug.h>
#include <qtextstream.h>
#include "Student.h"

RegistryManager::RegistryManager() {
	sync();
}

RegistryManager::~RegistryManager() {
	mapStu.clear();
}

bool RegistryManager::addStudent(string username, string password) {
	QString pw;
	pw.append(QCryptographicHash::hash(password.c_str(), QCryptographicHash::Md5).toHex());
	mapStu[username] = pw.toStdString();
	Student student(username);
	student.update();
	return update();
}

void RegistryManager::deleteStudent(string username) {
	mapStu.erase(username);
}

bool RegistryManager::studentExist(string username) {
	unordered_map<string, string>::iterator iter = mapStu.find(username);
	return iter != mapStu.end();
}

bool RegistryManager::loginSuccess(string username, string password) {
	unordered_map<string, string>::iterator iter = mapStu.find(username);
	if (iter == mapStu.end()) {
		return false;
	}
	QString pw;
	pw.append(QCryptographicHash::hash(password.c_str(), QCryptographicHash::Md5).toHex());
	if (iter->second == pw.toStdString()) {
		return true;
	} else {
		return false;
	}
}

bool RegistryManager::changePassword(string username, string password) {
	return addStudent(username, password);
}

bool RegistryManager::checkUsername(string username) {
	if (username.size() != 9) return false;
	for (int i = 0; i < username.size(); ++i) {
		if (!isdigit(username[i])) return false;
	}
	return true;
}

void RegistryManager::sync() {
	mapStu.clear();
	QFile fp("./data/student/student.txt");
	if (!fp.open(QIODevice::ReadOnly)) {
		qDebug() << "File open failed";
		return;
	}
	QTextStream in(&fp);
	in.setCodec("UTF-8");
	while (!in.atEnd()) {
		QStringList lineList = in.readLine().split(',');
		mapStu[lineList[0].toStdString()] = lineList[1].toStdString();
	}
	fp.close();
}

bool RegistryManager::update() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/student")) {
		dir.mkdir("./data/student");
	}
	QFile fp("./data/student/student.txt");
	if (!fp.open(QIODevice::WriteOnly)) {
		qDebug() << "File open failed";
		return false;
	}
	QTextStream out(&fp);
	out.setCodec("UTF-8");
	for (unordered_map<string, string>::iterator iter = mapStu.begin(); iter != mapStu.end(); ++iter) {
		out << QString::fromStdString(iter->first) << ',' << QString::fromStdString(iter->second) << endl;
	}
	fp.close();
	return true;
}
