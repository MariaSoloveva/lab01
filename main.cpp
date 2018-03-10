#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <functional>
#include"sort.hpp"

int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::vector<int> v1(9), v2(5), v3(10);
    std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
    std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    Matrix<int> m(5, 5);
    Matrix<int> m1(v1, 3, 3);
    Matrix<int> mVec(v2, 1, 5);
    Matrix<int> m2(m1);
    std::cout << std::endl;
    std::cout << m1.Determinant() << std::endl;
    m1.Transpose();
    m1.Inverse();
    std::cout << (m == m)<< std::endl;
    std::cout << (m == m1)<< std::endl;
    std::cout << (m != m)<< std::endl;
    std::cout << (m != m1)<< std::endl;
    m1 += m2;
    m1 -= m2;
    m1 *= 2;
    m1 *= m1;
    mVec *= v2;
    m1 = m;
    Matrix<int> m4(v2, 3, 3);
    m4[0][0] = 14;
    m4[0][1] = -4;
    m4[0][2] = 0;
    m4[1][0] = -4;
    m4[1][1] = 12;
    m4[1][2] = -4;
    m4[2][0] = 0;
    m4[2][1] = -4;
    m4[2][2] = 10;
    /*  Polynomial<int> vec = m4.CharacteristicEquation();
    for (size_t i = 0; i < vec.Degree() + 1; ++i)
        std::cout << vec[i] << " ";  */
    Matrix<int> m3(v2, 3, 2);
    m3[0][0] = 4;
    m3[0][1] = 4;
    m3[1][0] = 4;
    m3[1][1] = 4;
    m3[2][0] = 3;
    m3[2][1] = 4;
    //  Matrix<int> m13(v1, 5, 2);
    m = getBasis(m3);
    std::cout << std::endl;
    for (size_t i = 0; i < m.NumRows(); ++i) {
        for (size_t j = 0; j < m.NumRows(); ++j)
            std::cout << m[i][j] << " ";
        std::cout << std::endl;
    }
    Matrix<int> m5(v2, 3, 3);
    m5[0][0] = 1;
    m5[0][1] = 1;
    m5[0][2] = 1;
    m5[1][0] = 1;
    m5[1][1] = 1;
    m5[1][2] = 2;
    m5[2][0] = 1;
    m5[2][1] = 2;
    m5[2][2] = 3;
    std::vector<int> x ={6, 9, 14};
    std::vector<int> xNew = getCoordinates(m5, x);
    for (size_t i = 0; i < m5.NumRows(); ++i)
    {
        std::cout << xNew[i] << " ";
    }
    return 0;
}
