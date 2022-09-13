//
//  ch1_function.cpp
//  test
//

#include <iostream> /* 입출력을 위한 헤더파일(iostream)을 포함시킴으로써 cin, cout, endl 등을 사용 가능하게 한다. stdio.h를 포함할 경우, scanf, printf 사용 가능.
*/
// using namespace std; // std라는 namespace를 생성을 통해 std::를 생략할 수 있지만, 충돌 위험이 있으므로 사용하지 않는다.

int main(){
    int x, y;
    std::cout << "x값을 입력하시오: ";
    std::cin >> x;
    std::cout << "y값을 입력하시오: ";
    std::cin >> y;
    
    if (x>y)
        std::cout << "x가 y보다 큽니다." << std::endl;
    else
        std::cout << "y가 x보다 큽니다." << std::endl;
    return 0;
}

