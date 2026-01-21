#include "boss.h"


boss::boss(int id, string name, int deptid) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}
void boss::showInfo() {//显示个人信息
	cout << "职工编号：" << this->m_Id
		<< "\t姓名：" << this->m_Name
		<< "\t职位：" << this->getDeptName()
		<< "\t职责：管理公司所有事物" << endl;


}
string boss::getDeptName() {//获取职位名称
	return string("老板");

}