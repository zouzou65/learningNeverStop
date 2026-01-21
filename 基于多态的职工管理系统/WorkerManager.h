#pragma once
#include <iostream>
#include "worker.h"
#include "boss.h"
#include "manager.h"
#include "employee.h"
#include "fstream"
#define FILENAME "EmpFile.txt"

using namespace std;

class WorkerManager {
public:

	//成员属性
	int m_empnum;//记录文件中的人数个数

	worker** m_empArray;//员工数组的指针 二级指针 指向父类指针数组

	bool m_FileIsEmpty;//标志文件是否为空


	//成员行为
	WorkerManager();//构造函数

	void init_Emp();//初始化员工

	int get_num();//初始化时 文件存在且不为空时 统计文件里人数

	void show_menu();//显示菜单

	void addEmp();//添加员工

	void show_emp();//显示员工

	int IsExist(int id);//判断员工是否存在

	void Del_emp();//删除员工

	void Mod_emp();//修改员工

	void find_emp();//查找员工

	void sort_emp();//给员工排序

	void save();//添加员工等操作后，保存文件

	void exid_system();//退出系统

	void clean_file();//清空文件

	~WorkerManager();//析构函数
};
