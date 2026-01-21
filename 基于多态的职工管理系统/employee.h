#pragma once
#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

class employee :public worker {
public:
	employee(int id, string name, int deptid);
	virtual void showInfo();//显示个人信息
	virtual string getDeptName();//获取职位名称
};
