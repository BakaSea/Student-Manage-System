#pragma once
#include <unordered_map>
#include <string>
using namespace std;

class RegistryManager {
public:
	RegistryManager();
	~RegistryManager();
	//学生注册
	bool addStudent(string username, string password);
	//删除学生
	void deleteStudent(string username);
	//判断学生是否存在
	bool studentExist(string username);
	//判断登录是否成功
	bool loginSuccess(string username, string password);
	//更改密码
	bool changePassword(string username, string password);
	//判断学生id是否合法
	bool checkUsername(string username);

private:
	//存储学生id和密码
	unordered_map<string, string> mapStu;
	//从文件中同步学生信息
	void sync();
	//将学生信息写入到文件中
	bool update();
};
