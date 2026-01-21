#include <iostream>
#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

//对多态代码正确性的测试
//void test() {
//	worker* w1 = NULL;
//	w1 = new employee(1, "zhangsan", 1);
//	w1->showInfo();
//	delete w1;
//
//	w1 = new manager(2, "lisi", 2);
//	w1->showInfo();
//	delete w1;
//
//	w1 = new boss(3, "wangwu", 3);
//	w1->showInfo();
//	delete w1;
//}


int main() {


	int choice = 0;
	WorkerManager wm;
	
	while (1) {
		wm.show_menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice) {
		case 0://退出系统
			wm.exid_system();
			break;
		case 1://添加职工
			wm.addEmp();
			break;
		case 2://显示职工
			wm.show_emp();
			break;
		case 3://删除职工
			wm.Del_emp();
			break;
		case 4://修改职工信息
			wm.Mod_emp();
			break;
		case 5://查找职工
			wm.find_emp();
			break;
		case 6://给职工排序
			wm.sort_emp();
			break;
		case 7://清空所有文档
			wm.clean_file();
			break;
		default:
			system("cls");
			break;
		}
		
	}
	
	

	return 0;
}