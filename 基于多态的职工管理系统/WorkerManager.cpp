#include "WorkerManager.h"

WorkerManager::WorkerManager() {//构造函数
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//以只读的方式打开文件

	//1.文件不存在的情况下初始化
	if (!ifs.is_open()) {//if文件没打开
		//cout << "文件不存在 " << endl;
		this->m_empnum = 0;//开始0人在文件里
		this->m_empArray = NULL;//员工数组的指针指向空
		this->m_FileIsEmpty = true;//初始化文件为空
		ifs.close();
		return;
	}
	//2.文件存在但为空的情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空" << endl;
		this->m_empnum = 0;//开始0人在文件里
		this->m_empArray = NULL;//员工数组的指针指向空
		this->m_FileIsEmpty = true;//初始化文件为空
		ifs.close();
		return;
	}
	//3.文件存在且不为空的情况
	int num = this->get_num();
	//cout << "职工个数为：" << num << endl;
	//初始化职工数
	this->m_empnum = num;
	//根据职工数创建数组
	this->m_empArray = new worker * [this->m_empnum];
	//初始化职工
	init_Emp();

	//测试代码
	/*for (int i = 0; i < m_empnum; i++) {
		cout << "职工号：" << this->m_empArray[i]->m_Id 
			<< " 姓名：" << this->m_empArray[i]->m_Name 
			<< " 职位：" << this->m_empArray[i]->m_DeptId << endl;
	}*/
}

//初始化员工
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int Did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> Did) {
		worker* w1 = NULL;//父类指针
		if (Did == 1) {
			w1 = new employee(id, name, Did);
		}
		else if (Did == 2) {
			w1 = new manager(id, name, Did);
		}
		else {
			w1 = new boss(id, name, Did);
		}
		this->m_empArray[index] = w1;
		index++;
	}


}

void WorkerManager::show_menu() {
	
	cout << "*********************************" << endl;
	cout << "****** 欢迎使用职工管理系统 *****" << endl;
	cout << "******** 0.退出管理系统 *********" << endl;
	cout << "******** 1.增加职工信息 *********" << endl;
	cout << "******** 2.显示职工信息 *********" << endl;
	cout << "******** 3.删除离职职工 *********" << endl;
	cout << "******** 4.修改职工信息 *********" << endl;
	cout << "******** 5.查找职工信息 *********" << endl;
	cout << "******** 6.按照编号排序 *********" << endl;
	cout << "******** 7.清空所有文档 *********" << endl;
	cout << "*********************************" << endl;

}

//退出系统
void WorkerManager::exid_system() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);

}

//增加职工信息
void WorkerManager::addEmp() {
	cout << "请选择添加人数：" << endl;
	int addnum = 0;
	cin >> addnum;
	if (addnum > 0) {
		//计算职工数组新空间大小
		int newArrsize = this->m_empnum + addnum;
		//开辟新空间
		worker** newSpace = new worker * [newArrsize];//二级指针指向父类指针数组

		//在新空间放东西
		//1.将原空间下内容存在新空间下
		if (this->m_empArray != NULL) {
			for (int i = 0; i < this->m_empnum; i++) {
				newSpace[i] = this->m_empArray[i];
			}
		}

		//2.输入新数据
		for (int i = 0; i < addnum; i++) {
			int id;
			string name;
			int did;

			cout << "请输入第 " << i + 1 << " 个新职工的编号：" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << " 个新职工的姓名：" << endl;
			cin >> name;

			cout << "请输入该职工的岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> did;

			worker* w1 = NULL;//抽象父类指针，待会指向子类对象，形成多态
			switch (did) {
			case 1:
				w1 = new employee(id, name, 1);//普通职工
				break;
			case 2:
				w1 = new manager(id, name, 2);//经理
				break;
			case 3:
				w1 = new boss(id, name, 3);//老板
				break;
			default:
				break;
			}
			//新员工w1被录入到新空间内 创建的职工指针保存到职工指针数组中
			newSpace[this->m_empnum + i] = w1;

		}

		//释放原有空间
		delete[] this->m_empArray;

		//更新新空间的指向
		this->m_empArray = newSpace;

		//更新员工个数
		this->m_empnum = newArrsize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		cout << "成功添加 " << addnum<<" 名新员工" <<endl;
		this->save();
	
	}
	else {
		cout << "输入有误" << endl;
	}

	//按任意键后清屏返回上级目录
	system("pause");
	system("cls");

}

//显示员工
void WorkerManager::show_emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		for (int i = 0; i < m_empnum; i++) {
			m_empArray[i]->showInfo();//类的成员函数内部，编译器会自动在成员变量名前面“补上”隐含的 this->。
			//所以当你写 m_empnum 时，编译器其实把它看作 this->m_empnum。
			//只要没有同名的局部变量或参数遮蔽它，直接写变量名是最常见的做法，代码会更简洁

		}
	}
	system("pause");
	system("cls");

}

//判断员工是否存在
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < m_empnum; i++) {
		if (m_empArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

//删除员工
void WorkerManager::Del_emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		int id;
		cout << "请输入你要删除的员工编号：" << endl;
		cin >> id;
		int index = IsExist(id);
		if (index != -1) {//要删除的职工存在
			for (int i = index; i < m_empnum; i++) {
				m_empArray[i] = m_empArray[i + 1];//数据前移
			}
			m_empnum--;
			save();//数据同步到文件里
			cout << "删除成功！" << endl;
		}
		else {//要删除的职工不存在
			cout << "删除失败，未找到该员工！" << endl;
		}

	}
	//按任意键后清屏返回上级目录
	system("pause");
	system("cls");

}

//修改员工
void WorkerManager::Mod_emp() {
	if (m_FileIsEmpty) {//先查文件存不存在或有没有员工存在
		cout << "文件不存在或记录为空！" << endl;
	}
	else {//员工存在
		cout << "请输入要修改员工的id:" << endl;
		int id;
		cin >> id;
		int ret = IsExist(id);
		if (ret != -1) {
			//修改的员工存在
			delete m_empArray[ret];//删除员工
			int newid;
			string newname;
			int newdid;
			cout << "你要修改的" << id << "号的新信息为：" << endl;
			cout << "请输入新职工号:" << endl;
			cin >> newid;
			cout << "请输入新姓名:" << endl;
			cin >> newname; 
			cout << "请输入新职务:" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> newdid;

			worker* w1 = NULL;
			switch (newdid) {
			case 1:
				w1 = new employee(newid, newname, newdid);
				break;
			case 2:
				w1 = new manager(newid, newname, newdid);
				break;
			case 3:
				w1 = new boss(newid, newname, newdid);
				break;
			default:
				break;
			}
			m_empArray[ret] = w1;//更新数据到数组中
			save();//存到文档里


		}
		else {
			cout << "要删除的员工不存在!" << endl;
		}

	}
	//按任意键清屏
	system("pause");
	system("cls");

}
//void WorkerManager::Mod_emp() {
//	if (m_FileIsEmpty) {
//		cout << "文件不存在或记录为空！" << endl;
//	}
//	else {
//		cout << "请输入要修改员工的id:" << endl;
//		int id;
//		cin >> id;
//
//		int ret = IsExist(id);
//		if (ret != -1) {
//			 先获取新信息
//			int newid;
//			string newname;
//			int newdid;
//
//			cout << "请输入新职工号:" << endl;
//			cin >> newid;
//
//			 检查新ID是否已存在（除了自己）
//			if (newid != id && IsExist(newid) != -1) {
//				cout << "该职工号已存在！" << endl;
//				system("pause");
//				system("cls");
//				return;
//			}
//
//			cout << "请输入新姓名:" << endl;
//			cin >> newname;
//
//			cout << "请输入新职务:" << endl;
//			cout << "1.普通职工" << endl;
//			cout << "2.经理" << endl;
//			cout << "3.老板" << endl;
//			cin >> newdid;
//
//			 检查职务编号有效性
//			if (newdid < 1 || newdid > 3) {
//				cout << "职务编号无效！" << endl;
//				system("pause");
//				system("cls");
//				return;
//			}
//
//			 删除旧员工
//			delete m_empArray[ret];
//
//			 创建新员工
//			worker* w1 = NULL;
//			switch (newdid) {
//			case 1:
//				w1 = new employee(newid, newname, newdid);
//				break;
//			case 2:
//				w1 = new manager(newid, newname, newdid);
//				break;
//			case 3:
//				w1 = new boss(newid, newname, newdid);
//				break;
//			}
//
//			m_empArray[ret] = w1;
//			save();
//			cout << "修改成功！" << endl;
//		}
//		else {
//			cout << "要修改的员工不存在!" << endl;
//		}
//	}
//
//	system("pause");
//	system("cls");
//}

//查找员工
void WorkerManager::find_emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或内容为空！" << endl;
	}
	else {
		int select = 0;
		cout << "请选择查找方式：" << endl;
		cout << "1.按员工工号查找" << endl;
		cout << "2.按员工姓名查找" << endl;
		cin >> select;
		
		if (select == 1) {//按工号查找
			int id;
			cout << "请选择你要查找的员工工号：" << endl;
			cin >> id;
			int index = IsExist(id);//index为指针数组下标
			if (index != -1) {
				cout << "查找成功，该员工的信息如下：" << endl;
				this->m_empArray[index]->showInfo();
			}
			else {
				cout << "查找失败，该员工编号不存在！" << endl;
			}

		}
		else if (select == 2) {//按姓名查找
			string name;
			bool flag = false;//标志有没有这个名字的员工
			cout << "请选择你要寻找的员工姓名：" << endl;
			cin >> name;
			for (int i = 0; i < m_empnum; i++) {
				if (m_empArray[i]->m_Name == name) {
					cout << "查找成功，该员工的信息如下：" << endl;
					m_empArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "查找失败，没有这个名字的员工" << endl;
			}
		}
		else {
			cout << "输入选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//给员工排序
void WorkerManager::sort_emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或内容为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1.工号升序排序" << endl;
		cout << "2.工号降序排序" << endl;

		int ret = 0;
		cin >> ret;
		
		for (int i = 0; i < m_empnum; i++) {
			int maxOrMin = i;//设最大最小值为i
			for (int j = i + 1; j < m_empnum; j++) {
				if (ret == 1) {//按升序排序
					if (m_empArray[i]->m_Id > m_empArray[j]->m_Id) {
						maxOrMin = j;
					}
				}
				else if(ret == 2){//按降序排序
					if (m_empArray[i]->m_Id < m_empArray[j]->m_Id) {
						maxOrMin = j;
					}
				}
				else {
					cout << "没有这种排序方式！" << endl;
					system("pause");
					system("cls");
				}
			}
			if (maxOrMin != i) {//经过一次小排序后，最大最小值若不是i 把最大最小值换成i
				worker* w1 = m_empArray[i];
				m_empArray[i] = m_empArray[maxOrMin];
				m_empArray[maxOrMin] = w1;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		save();
		this->show_emp();
	}
}

//添加员工等操作后，保存文件
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//以只写方法打开文件，写入文件

	for (int i = 0; i < m_empnum; i++) {
		ofs << this->m_empArray[i]->m_Id << " "
			<< this->m_empArray[i]->m_Name << " "
			<< this->m_empArray[i]->m_DeptId << endl;
	}

	ofs.close();//写完关闭文件


}

//初始化文件存在且不为空时统计文件里人数
int WorkerManager::get_num() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;//用于读取文件里的信息
	string name;
	int Did;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> Did) { //三个信息都读到了，num++
		num++;
	
	}
	ifs.close();
	return num;

}

//清空文件
void WorkerManager::clean_file() {
	cout << "确定要清空吗？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//1.删除文件里内容
		ofstream ofs(FILENAME, ios::trunc);//以如果文件存在，删除文件并重新创建方式打开
		ofs.close();

		//2.删除职工数组
		if (this->m_empArray != NULL) {
			for (int i = 0; i < m_empnum; i++) {
				if (m_empArray[i] != NULL) {
					delete m_empArray[i];
				}
			}
			m_empnum = 0;

			//3.删除数组指针
			delete[] this->m_empArray;//释放堆区数据
			m_empArray = NULL;
			m_FileIsEmpty = true;
		}
		cout << "清除成功" << endl;
		system("pause");
		system("cls");

	}
	else if (select == 2) {
		//按任意键后清屏返回上级目录
		system("cls");
	}
	else {
		//按任意键后清屏返回上级目录
		cout << "输入错误，请重新输入！" << endl;
		system("pause");
		system("cls");
	}


}

WorkerManager::~WorkerManager() {
	if (this->m_empArray != NULL) {
		for (int i = 0; i < m_empnum; i++) {
			if (m_empArray[i] != NULL) {
				delete m_empArray[i];
			}
		}
		delete[] this->m_empArray;//释放堆区数据
		m_empArray = NULL;
	}

}