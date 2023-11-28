#include <iostream>

class myClass {
public:
	int * arr;
	myClass() {
		arr = new int[3] {1, 2, 3};

	}
	~myClass() {
		delete[] arr;
	}
};

int main() {
	myClass x, y;
	
	std::cout << x.arr[0] << " " << y.arr[0];
}