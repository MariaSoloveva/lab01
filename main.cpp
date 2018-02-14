#include <iostream>
#include "strings.h"

int StrLen(const char* strIn)
{
    int size = 0;
    for (; strIn[size] != 0; size++)
        continue;
    return size;
}
void StrCopy(char* strOut, const char* strIn)
{
    for (int i = 0; i < StrLen(strIn); i++)
        strOut[i] = strIn[i];
}

String::~String()
{
    delete[] Data;
}
String::String() : Data(nullptr) {}
String::String(const String& rhs)
{
    Data = new char[StrLen(rhs.Data)+1];
    StrCopy(Data, rhs.Data);
}
String::String(const char* data)
{
    Data = new char[StrLen(data)+1];
    StrCopy(Data, data);
}
String& String::operator=(const String& rhs)
{
    if (this != &rhs)
    {
        Data = nullptr;
        delete[] this->Data;
        this->Data = new char[StrLen(rhs.Data)+1];
        StrCopy(this->Data, rhs.Data);
    }
    return *this;
}
String& String::operator+=(const String& rhs)
{
    int size = StrLen(this->Data) + StrLen(rhs.Data);
    char* newString = new char[size + 1];
    for (int i = 0; i < StrLen(this->Data); i++)
        newString[i] = this->Data[i];
    for (int k = StrLen(this->Data), j = 0; k <= size; k++, j++)
        newString[k] = rhs.Data[j];
    delete[] this->Data;
    this->Data = newString;
    return *this;
}
bool String::operator<(const String& rhs) const
{
    return (StrLen(Data) < StrLen(rhs.Data)) ? true : false;
}
bool String::operator==(const String& rhs) const
{
    int i = 0;
    for (; (rhs.Data[i] == this->Data[i]) && (i < StrLen(rhs.Data)); ++i)
        continue;
    return (i == StrLen(rhs.Data)) ? true : false;
}
size_t String::Find(const String& substr) const
{
    size_t lenSub = StrLen(substr.Data);
    if ((StrLen(this->Data) - lenSub) > 0)
    {
        for (size_t i = 0; i < (StrLen(this->Data) - lenSub); ++i)
        {
            int j = 0;
            bool flag = true;
            for (int k = i; k < lenSub; ++k)
            {
                if (this->Data[k] != substr.Data[j])
                    flag = false;
                ++j;
            }
            if (flag)
                return i;
        }
    }
    else
        return -1;
}
void String::Replace(char oldSymbol, char newSymbol)
{
    for (int i = 0; this->Data[i] != 0; ++i)
        if (this->Data[i] == oldSymbol)
            this->Data[i] = newSymbol;
}
size_t String::Size() const
{
    size_t sizeOfData = 0;
    for (; Data[sizeOfData] != 0; ++sizeOfData)
        continue;
    return sizeOfData;
}
bool String::Empty() const
{
    return (Data == nullptr) ? true : false;
}
char String::operator[](size_t index) const
{
    return (index >= 0 && index < StrLen(this->Data)) ? this->Data[index] : 0;
}
char& String::operator[](size_t index)
{
    static char emptyChar = 0;
    return (index >= 0 && index < StrLen(this->Data)) ? this->Data[index] : emptyChar;
}
void String::RTrim(char symbol)
{
    size_t sizeOfData = StrLen(this->Data);
    for (; sizeOfData != -1; sizeOfData--)
        if (this->Data[sizeOfData - 1] != symbol)
            break;
    char* newData = new char[sizeOfData + 1];
    for (int i = 0; i < sizeOfData; ++i)
        newData[i] = this->Data[i];
    this->Data = nullptr;
    delete[] this->Data;
    this->Data = newData;
}
void String::LTrim(char symbol)
{
    size_t sizeOfData = 0;
    for (; this->Data[sizeOfData] != 0; ++sizeOfData)
        if (Data[sizeOfData] != symbol)
            break;
    char* newData = new char[StrLen(this->Data) - sizeOfData + 1];
    for (int i = 0; this->Data[sizeOfData] != 0; ++sizeOfData, ++i)
        newData[i] = this->Data[sizeOfData];
    Data = nullptr;
    delete[] this->Data;
    this->Data = newData;
}

String operator+(const String& a, const String& b)
{
    String c = a;
    return c += b;
}

bool operator!=(const String& a, const String& b)
{
    return !(a == b);
}

bool operator>(const String& a, const String& b)
{
    return (b < a) ? true : false;
}
std::ostream& operator<<(std::ostream& out, const String& str)
{
    return out << str.Data;
}

int main()
{
    const char* data = {"__some string__"};
    const char* data2 = {"Some String"};
    String stringFirst;
    String stringSecond(data);
    String stringCopy(stringSecond);
    String stringThird(data2);
    std::cout << stringFirst << std::endl;
    std::cout << "2   " << stringSecond << std::endl;
    std::cout << "3   " << stringThird << std::endl;
    std::cout << "Copy   " << stringCopy << std::endl;
    stringSecond = stringThird;
    std::cout << "2 after =   " << stringSecond << std::endl;
    stringSecond += stringCopy;
    std::cout << "2 after +=   " << stringSecond << std::endl;
    std::cout << "2 < 3 ? true : false   " << (stringSecond < stringThird)<< std::endl;
    std::cout << "2 > 3 ? true : false   " << (stringSecond > stringThird)<< std::endl;
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
    stringSecond.LTrim('s');
    std::cout << "Delete '_' on left and right  " << stringSecond << std::endl;
    std::cout << "find third string in second " << stringSecond.Find(stringThird) << std::endl;
    std::cout << "2 size  " << stringSecond.Size() << std::endl;
    std::cout << "2 empty or not  " << stringSecond.Empty() << std::endl;
    return 0;
}
