//
//  ch1_ex1.cpp
//  test
//
// 예제 1: 컵의 사이즈를 받아서 100ml미만은 small, 200ml미만은 medium, 200ml이상은 large로 출력

#include <iostream>

int main(){
    int size;
    std::cout << "컵의 용량(ml)을 입력하시오: ";
    std::cin >> size;
    if(size<100)
        std::cout << "small" << std::endl;
    else if(size >= 100 && size < 200)
        std::cout << "medium" << std::endl;
    else
        std::cout << "large" << std::endl;
    return 0;
}
