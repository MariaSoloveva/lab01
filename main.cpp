#include <cstring>
#include <iostream>
#include "string.hpp"


int main()
{
    const char* data = {"awesome string___"};
    const char* data2 = {"Some String"};
    String stringFirst;
    String stringSecond(data);
    String stringCopy(stringSecond);
    String stringThird(data2);
    std::cout << "2   " << stringSecond << std::endl;
    std::cout << "3   " << stringThird << std::endl;
    std::cout << "Copy   " << stringCopy << std::endl;
    stringSecond = stringThird;
    std::cout << "2 after =   " << stringSecond << std::endl;
    stringSecond += stringCopy;
    std::cout << "2 after +=   " << stringSecond << std::endl;
    std::cout << "2 < 3 ? true : false   " << (stringCopy < stringThird)<< std::endl;
    std::cout << "2 > 3 ? true : false   " << (stringCopy > stringThird)<< std::endl;
    std::cout << "3   " << stringThird << std::endl;
    std::cout << "2 == 3  " << (stringThird == stringSecond) << std::endl;
    std::cout << "2 == 3  " << (stringSecond == stringSecond) << std::endl;
    std::cout << "2 != 3  " << (stringThird != stringSecond) << std::endl;
    stringSecond.Replace('s', 'S');
    std::cout << "2 replace 's' -> 'S' " << stringSecond << std::endl;
    std::cout << "find third string in second position"
              << stringSecond.Find(stringThird) << std::endl;
    stringSecond.Replace('S', 's');
    std::cout << "2 replace 'S' -> 's' " << stringSecond << std::endl;
    std::cout << "3   " << stringThird << std::endl;
    stringSecond.RTrim('_');
    stringSecond.LTrim('_');
    std::cout << "Delete '_' on left and right  " << stringSecond << std::endl;
    std::cout << "find third string in second " << stringSecond.Find(stringThird) << std::endl;
    std::cout << "2 size  " << stringSecond.Size() << std::endl;
    std::cout << "2 empty or not  " << stringSecond.Empty() << std::endl;
    return 0;
}
