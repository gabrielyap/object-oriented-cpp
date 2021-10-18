#include "hw4part2_MultipleInheritance.h"
#include <iostream>

int main(void)
{
    Work_Study Obj_WS;
    Work_Study *ptr = &Obj_WS;

    std::cout << (Student *) ptr << std::endl;
    Student *stud_ptr = (Student *) ptr;
    std::cout << "Account Student" << (Account *) stud_ptr << std::endl;

    std::cout << (Employee *) ptr << std::endl;
    Employee *employee_ptr = (Employee *) ptr;
    std::cout << "Account Employee" << (Account*) employee_ptr << std::endl;

    std::cout << "Work_Study" << &Obj_WS << std::endl;

    std::cout << "Address of S1 is " << &(Obj_WS.S1) << std::endl;
    std::cout << "Address of E1 is " << &(Obj_WS.E1) << std::endl;
    std::cout << "Address of AE1 is " << &(((Employee&) Obj_WS).A1) << std::endl;
    std::cout << "Address of AS1 is " << &(((Student&) Obj_WS).A1) << std::endl;
    std::cout << "Address of W1 is " << &Obj_WS << std::endl;


    return 0;
}