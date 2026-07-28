#include <iostream>
using namespace std;
//1.函数的默认参数
//注意事项:如果函数参数的某个位置出现了默认参数，那么该位置及其后面的所有参数都必须有默认值
//函数的默认参数可以在函数声明时指定，也可以在函数定义时指定，但不能同时在声明和定义中指定
int add(int a=5,int b=10,int c=15){
    return a+b+c;
}
//2.函数的占位参数
float add(float a,int){
    return (float)a+10;
}
//3.函数的重载
//函数的重载是指在同一个作用域中，允许存在一个以上的同名函数，只要它们的参数个数或者参数类型或者参数顺序不同即可
//函数的重载与函数的返回值类型无关
//例如上边两个函数，函数名相同，但是参数类型不同，所以是合法的函数重载
//引用作为函数参数时，引用的类型也会影响函数的重载
//例如int add(const int &a)和int add(int &a)是合法的函数重载，因为一个是常量引用，一个是非常量引用
int main() {
	/*int sum1=add();
    cout<<sum1<<endl;
    int sum2=add(1,2,20);
    cout<<sum2<<endl;
    int sum3=add(1,2,3);
    cout<<sum3<<endl;*/
float sum4=add(1.5f,2);
    cout<<sum4<<endl;
	system("pause");
	return 0;
}