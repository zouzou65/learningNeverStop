#pragma once
#include <iostream>
#include <string>
//基类（父类）不需要包含子类的头文件，但子类必须包含基类的头文件。
using namespace std;

//抽象职工基类
class worker {
public:
	virtual void showInfo() = 0;//显示个人信息
	virtual string getDeptName() = 0;//获取职位名称

	int m_Id;//职工编号
	string m_Name;//职工姓名
	int m_DeptId;//部门编号


};
