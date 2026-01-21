#include "employee.h"


employee::employee(int id, string name, int deptid) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptid;
}
void employee::showInfo() {//显示个人信息
	cout << "职工编号：" << this->m_Id
		<< "\t姓名：" << this->m_Name
		<< "\t职位：" << this->getDeptName()
		<< "\t职责：完成经理交付的任务" << endl;


}
string employee::getDeptName() {//获取职位名称
	return string("员工");

}