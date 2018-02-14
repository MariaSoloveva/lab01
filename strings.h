#include <iostream>

class String
{
    char * Data;
 public:
    ~String();
    String();
    String(const String& rhs);
    String(const char* data);
    String& operator=(const String& rhs);
    String& operator+=(const String& rhs);
    bool operator==(const String& rhs) const;
    bool operator<(const String& rhs) const;
    size_t Find(const String& substr) const;
    void Replace(char oldSymbol, char newSymbol);
    size_t Size() const;
    bool Empty() const;
    char operator[](size_t index) const;
    char& operator[](size_t index);
    void RTrim(char symbol);
    void LTrim(char symbol);
    friend std::ostream& operator<<(std::ostream&, const String&);
};
    String operator+(const String& a, const String& b);
    bool operator!=(const String& a, const String& b);
    bool operator>(const String& a, const String& b);
