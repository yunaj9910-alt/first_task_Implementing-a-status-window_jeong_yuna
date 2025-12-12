#include <iostream>
using namespace std;

//함수: 포인터를 사용한 값 변경
void modifyValue(int* ptr) {
	*ptr = 100; //포인터가 가리키는 변수의 값을 변경
}

int main() {
	int num = 50;
	modifyValue(&num);//num의 주소 전달

	cout << "포인터 전달 후 num: " << num << endl;
	//출력: 포인터 전달 후 num: 100
	return 0;
}