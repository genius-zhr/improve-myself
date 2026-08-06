#include <iostream>
#include <vector>
using namespace std;
class Vectorlist {
private:
	vector<int>v;
	int size;
	int capacity;
public:
	Vectorlist() {
		size = 0;
		capacity = 0;
	}
	void show_size() {
		cout << "当前大小为:" << v.size() << endl;
	}
	void show_capacity() {
		cout << "当前容量为:" << v.capacity() << endl;
	}
	void push_back(int data) {
		v.push_back(data);
	}
	void print() {
		for (auto x : v) {
			cout << x << " ";
		}
		cout << endl;
	}
	void erase(int x) {
		for (auto it = v.begin();it != v.end();it++) {
			if (*it == x) {
				v.erase(it);
				return;
			}
		}
		cout << "未找到该数据" << endl;
		return;
	}
	bool find(int x) {
		for (auto e : v) {
			if (e == x) {
				return true;
			}
		}
		return false;
	}
	int getidx(int x) {
		bool t = this->find(x);
		int idx = 0;
		if (t) {
			for (auto it = v.begin();it != v.end();it++) {
				if (*it == x) {
					break;
				}
				idx++;
			}
		}
		return idx;
	}
	void modify(int x, int data) {
		int idx=this->getidx(x);
		v[idx] = data;
	}
	void insert(int x,int data) {
		int idx = this->getidx(x);
		auto it = v.begin() + idx;
		v.insert(it, data);
	}
};
int main() {
	Vectorlist V;
	V.push_back(10);
	V.push_back(20);
	V.push_back(30);
	V.print();
	V.modify(20, 50);
	V.print();
	V.insert(50, 666);
	V.print();
	system("pause");
	return 0;
}