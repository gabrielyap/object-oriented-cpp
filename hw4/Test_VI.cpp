#include "hw4part2_VirtualInheritance.h"
#include <iostream>

int main(void)
{
    Work_Study Obj_WS;
    Work_Study *ptr = &Obj_WS;

    std::cout << &(ptr->E1) << std::endl;
    std::cout << &(ptr->S1) << std::endl;
    std::cout << &(ptr->A1) << std::endl;
    std::cout << &(ptr->W1) << std::endl;
    std::cout << "-----Divisor-----" << std::endl;
    std::cout << (Employee *) ptr << std::endl;
    std::cout << (Student *) ptr << std::endl;
    std::cout << (Account *) ptr << std::endl;
    std::cout << (Work_Study *) ptr << std::endl;

    return 0;
}