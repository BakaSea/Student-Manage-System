#include "RegistryManager.h"
#include <qdir.h>
#include <qcryptographichash.h>
#include <stdio.h>
#include <string.h>

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
	return update();
}

void RegistryManager::deleteStudent(string username) {
	mapStu.erase(username);
}

bool RegistryManager::studentExist(string username) {
	map<string, string>::iterator iter = mapStu.find(username);
	return iter != mapStu.end();
}

bool RegistryManager::loginSuccess(string username, string password) {
	map<string, string>::iterator iter = mapStu.find(username);
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

void RegistryManager::sync() {
	mapStu.clear();
	FILE* fp = fopen("./data/student/student.txt", "r");
	if (fp != NULL) {
		char str[50];
		string id, password;
		while (!feof(fp)) {
			int flag = 0;
			id.clear();
			password.clear();
			int x = fscanf(fp, "%s", str);
			if (x == -1) break;
			for (int i = 0; i < strlen(str); ++i) {
				if (!flag && str[i] == ',') {
					flag = 1;
				} else {
					if (!flag) {
						id.push_back(str[i]);
					} else {
						password.push_back(str[i]);
					}
				}
			}
			mapStu[id] = password;
		}
		fclose(fp);
	}
}

bool RegistryManager::update() {
	QDir dir;
	if (!dir.exists("./data")) {
		dir.mkdir("./data");
	}
	if (!dir.exists("./data/student")) {
		dir.mkdir("./data/student");
	}
	FILE* fp = fopen("./data/student/student.txt", "w");
	if (fp == NULL) {
		return false;
	}
	for (map<string, string>::iterator iter = mapStu.begin(); iter != mapStu.end(); ++iter) {
		fprintf(fp, "%s,%s\n", (iter->first).c_str(), (iter->second).c_str());
	}
	fclose(fp);
	return true;
}
