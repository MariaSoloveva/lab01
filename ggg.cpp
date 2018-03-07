#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
template <class It, class Out, class BinatyOp>
Out wise_addition(It first1, It last1, It first2, Out out, BinatyOp plus)
{
    It it2 = first2;
    for (It it1 = first1; it1 != last1; ++it1)
    {
        *out = plus(*it1, *it2);
        ++it2;
        ++out;
    }
    return out;
};
template <class T>
struct MaxAbs
{
    T operator()(T a, T b) const
    {
        return (abs(a) > abs(b)) ? a : b;
    }
};
template <class T>
class DimVector
{
    T* startOfVec;
    T* endOfVec;
    T N;
public:
    ~DimVector()
    {
        delete[] startOfVec;
        delete[] endOfVec;
    }
    // создает вектор размерности n
    // начало и конец вектора в точке начала координат
    DimVector(size_t n)
        : startOfVec(new T[n])
        , endOfVec(new T[n])
        , N(n)
    {
        memset(startOfVec, 0, n * sizeof(startOfVec[0]));
        memset(endOfVec, 0, n * sizeof(endOfVec[0]));
    }

    // создает вектор размерности n
    // начало в точке с координатами beg
    // конец вектора в точке с координатами end
    DimVector(T* beg, T* end, size_t n)
        : startOfVec(new T[n])
        , endOfVec(new T[n])
        , N(n)
    {
        //  memset(startOfVec, beg, n * sizeof(startOfVec[0]));
        //  memset(endOfVec, end, n * sizeof(endOfVec[0]));
    }

    // конструктор копирования
    DimVector(const DimVector& point)
        : startOfVec(new T[point.N])
        , endOfVec(new T[point.N])
    {
        memcpy(startOfVec, point.startOfVec, N * sizeof(startOfVec[0]));
        memcpy(endOfVec, point.endOfVec, N * sizeof(endOfVec[0]));
    }
    // оператор присваивания
    DimVector& operator =(const DimVector& oth)
    {
        if (this != &oth)
        {
            delete[] startOfVec;
            delete[] endOfVec;
            N = oth.N;
            startOfVec = new T[N];
            endOfVec = new T[N];
            memcpy(startOfVec, oth.startOfVec, N * sizeof(startOfVec[0]));
            memcpy(endOfVec, oth.endOfVec, N * sizeof(endOfVec[0]));
        }
        return *this;
    }
    // сложение двух векторов
    // если размерность векторов не совпадают,
    // генерируйте исключение std::runtime_error("error");
    DimVector& operator+=(const DimVector& oth)
    {
        if (oth.Dimension() != Dimension())
        {
            throw std::runtime_error("error");
        }
        for (size_t i = 0; i < Dimension(); ++i)
        {
            startOfVec[i] += oth.startOfVec[i];
            endOfVec[i] += oth.endOfVec[i];
        }
        return *this;
    }

    size_t Dimension() const
    {
        return N;
    }

    // длина вектора
    T Length() const
    {
        T lenghtOfVec = 0;
        for (size_t i = 0; i < Dimension(); ++i)
        {
            T x = (endOfVec[i] - startOfVec[i]);
            lenghtOfVec += x * x;
        }
        return sqrt(lenghtOfVec);
    }
    // равны ли вектора
    bool operator== (const DimVector& vec) const
    {
        if (vec.Dimension() != Dimension())
        {
            throw std::runtime_error("error");
        }
        for (size_t i = 0; i < Dimension(); ++i)
        {
            if (endOfVec[i] == vec.endOfVec[i] && startOfVec[i] == vec.startOfVec[i])
                return false;
        }
        return true;
    }
};
template<class T>
DimVector<T> operator+(const DimVector<T>& a, const DimVector<T>& b)
{
    DimVector<T> c(a);
    c += b;
    return c;
}
template<class T>
std::ostream& operator<<(std::ostream& out, const DimVector<T>& a)
{
    for (int i = 0; i < a.Dimension(); ++i)
    {
        out << a.startOfVec[i] << " ";
    }
    for (int i = 0; i < a.Dimension(); ++i)
    {
        out << a.endOfVec[i] << " ";
    }
    return out;
}
template<class T>
bool operator!= (const DimVector<T>& a, const DimVector<T>& b) const
{
    return !(a == b);
}
int main()
{
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {-1, -2, -3};
    std::vector<int> v3(3);

    auto it = wise_addition(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<int>{});
    std::cout << std::boolalpha << (it == (v3.begin() + std::distance(v1.begin(),
                                                                      v1.end())));  // true
    std::cout << v3[0] << v3[1] << v3[2];  // 000

    MaxAbs<int> op;
    int v = op(-100, 10);
    std::cout << v;  // -100

    int arr1[] = {1, 2, 3, 2};
    int arr2[] = {1, 4, 6, 4};
    int arr0[] = {0, 0, 0, 0};
    // DimVector(size_t n)
    DimVector<int> b(4);
    // DimVector(T* beg, T* end, size_t n)
    DimVector<int> c1(arr1, arr2, 4);
    DimVector<int> c2(arr0, arr2, 4);
    // DimVector(const DimVector& point);
    DimVector<int> cCopy(c1);
    // DimVector& operator=(const DimVector& oth)
    std:: cout << (b = c2) << std::endl;
    // DimVector& operator+=(const DimVector& oth)
    std:: cout << (b += c2) << std::endl;
    // size_t Dimension() const
    std:: cout << b.Dimension() << std::endl;
    // T Length() const
    std:: cout << cCopy.Length() << std::endl;
    // bool operator== (const DimVector&) const
    std:: cout << (b == c2) << std::endl;
    std:: cout << (b == b) << std::endl;
    // DimVector<T> operator+(const DimVector<T>& a, const DimVector<T>& b)
    std:: cout << (c1 + c1) << std::endl;
    // bool operator!= (const DimVector<T>&, const DimVector<T>&) const
    std:: cout << (b != c2) << std::endl;
    std:: cout << (b != b) << std::endl;
    return 0;
}
