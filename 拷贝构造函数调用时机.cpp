#include <iostream>
using namespace std;
class Person {
private:
	int m_age;
public:
	Person() {
		cout << "默认构造函数" << endl;
		m_age = 0;
	}
	Person(int age) {
		m_age = age;
		cout << "有参构造函数" << endl;
	}
	Person(const Person& p) {
		m_age = p.m_age;
		cout << "拷贝构造函数" << endl;
	}
	~Person() {
		cout << "析构函数" << endl;
	}
	int showage() {
		return m_age;
	}
};
void test01() {
	Person p;
}
void test02() {
	Person p(10);
}
void test03() {
	Person p1;
	Person p2(p1);
}
Person dowork01() {
	Person p;
	return p;
}
void test04() {
    Person p(dowork01());
}
Person dowork02(Person p){
    return p;
}
void test05() {
    Person p1;
    dowork02(p1);
}
int main() {
	//test01();
	//test02();
	//test03();
	test04();
	//test05();
	system("pause");
	return 0;
}