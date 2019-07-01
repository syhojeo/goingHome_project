#include "eventhandler.h"

void gobase()
{
    printf("go to base: WORK IN PROGRESS\n");
}

void set_destination(std::string &dest, std::string &name)
{
    std::cout << "go to " << dest << " and find " << name << '\n';
    // 여기에 서비스/메시지 관련 내용 추가
    return;
}

void destination_menu()
{
    // Go to dest, and find name
    std::string dest, name;
    printf("select destination: ");
    std::cin >> dest;

    printf("find who: ");
    std::cin >> name;
    
    set_destination(dest, name);

    return;
}
