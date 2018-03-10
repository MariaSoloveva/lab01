#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <functional>
#include "cmake-build-debug/polynomial.h"

template <class T>
class Matrix
{
public:
    class Row
    {
        T* Rows;
        size_t M;
    public:
        Row()
        {
            M = 0;
            Rows = nullptr;
        }
        Row(size_t a)
        {
            Rows = new T[a];
            M = a;
            for (size_t i = 0; i < a; ++i)
            {
                Rows[i] = 0;
            }
        }
        ~Row()
        {
            delete [] Rows;
        }
        size_t Size()
        {
            return M;
        }
        T& operator[](size_t index)
        {
            return Rows[index];
        }
        T operator[](size_t index) const
        {
            return Rows[index];
        }
        Row& operator=(const Row& a)
        {
            delete[] Rows;
            Rows = new T[a.M];
            M = a.M;
            for (size_t i = 0; i < M; ++i)
                Rows[i] = a.Rows[i];
            return *this;
        }
    };
    Matrix(size_t n, size_t m)
    {
        N = n;
        MatrixNM = new Row[N];
        for (size_t i = 0; i < N; ++i)
            MatrixNM[i] = Row(m);
    }
    ~Matrix()
    {
        delete[] MatrixNM;
    }
    /// создает матрицу из одномерного массива
    /// {1, 2, 3, 4, 5, 6, 7, 8}, n = 4, m = 2
    /// Матрица будет иметь две строки и четыре столбца:
    /// 1 2 3 4
    /// 5 6 7 8
    Matrix(const std::vector<T>& vecIn, size_t n, size_t m)
    {
        N = n;
        MatrixNM = new Row[N];
        int x = 0;
        for (size_t i = 0; i < N; ++i)
        {
            MatrixNM[i] = Row(m);
            for (size_t j = 0; j < m; ++j)
            {
                MatrixNM[i][j] = vecIn[j + x];
            }
            x += m;
        }
    }
    Matrix(const Matrix<T>& m)
    {
        MatrixNM = new Row[m.NumRows()];
        N = m.NumRows();
        for (size_t i = 0; i < m.NumRows(); ++i)
        {
            MatrixNM[i] = Row(m.NumCols());
            MatrixNM[i] = m.MatrixNM[i];
        }
    }
    Matrix<T>& operator=(const Matrix<T>& m)
    {
        delete[] this->MatrixNM;
        N = m.N;
        MatrixNM = new Row[N];
        for (size_t i = 0; i < N; ++i)
            MatrixNM[i] = m.MatrixNM[i];
        return *this;
    }

    size_t NumRows() const
    {
        return N;
    }
    size_t NumCols() const
    {
        return MatrixNM[0].Size();
    }

    Matrix<T>& operator+=(const Matrix<T>& m)
    {
        if ((NumRows() == m.NumRows()) && (NumCols() == m.NumCols()))
        {
            for (int i = 0; i < m.NumRows(); ++i)
            {
                for (int j = 0; j < m.NumCols(); ++j)
                    MatrixNM[i][j] += m.MatrixNM[i][j];
            }
        }
        return *this;
    }
    Matrix<T>& operator-=(const Matrix<T>& m)
    {
        if ((NumRows() == m.NumRows()) && (NumCols() == m.NumCols()))
        {
            for (int i = 0; i < NumRows(); ++i)
            {
                for (int j = 0; j < NumCols(); ++j)
                    MatrixNM[i][j] -= m.MatrixNM[i][j];
            }
        }
        return *this;
    }
    Matrix<T>& operator*=(const Matrix<T>& b)
    {
        Matrix product(NumRows() , b.NumCols());
        if (NumCols() == b.NumRows())
        {
            for (size_t row = 0; row < NumRows(); row++)
            {
                for (size_t col = 0; col < b.NumCols(); col++)
                {
                    for (size_t inner = 0; inner < NumCols(); inner++)
                        product.MatrixNM[row][col] += MatrixNM[row][inner] * b.MatrixNM[inner][col];
                }
            }
        }
        *this = product;
        return *this;
    }
    Matrix<T>& operator*=(const std::vector<T>& vec)
    {
        Matrix product(NumRows() , 1);
        if (NumCols() == vec.size())
        {
            for (size_t row = 0; row < NumRows(); ++row)
            {
                for (size_t inner = 0; inner < NumCols(); ++inner)
                    product.MatrixNM[row][0] += MatrixNM[row][inner] * vec[inner];
            }
        }
        *this = product;
        return *this;
    }
    Matrix<T>& operator*=(T c)
    {
        for (size_t i = 0; i < NumRows(); ++i)
        {
            for (size_t j = 0; j < NumCols(); ++j)
                MatrixNM[i][j] *= c;
        }
        return *this;
    }
    Matrix<T> Transpose() const
    {
        Matrix<T> matrix2(NumCols(), NumRows());
        for (int i = 0; i < NumCols(); ++i)
        {
            for (int j = 0; j < NumRows(); ++j)
                matrix2.MatrixNM[i][j] = MatrixNM[j][i];
        }
        return matrix2;
    }
    void CreateNewMatrix(Matrix matrix, Matrix& tempMatr, size_t indRow, size_t indCol)
    {
        size_t inner = 0;
        for (size_t i = 0; i < matrix.NumRows(); i++)
        {
            if (i != indRow)
            {
                for (size_t j = 0, innerj = 0; j < matrix.NumRows(); j++)
                {
                    if (j != indCol)
                    {
                        tempMatr[inner][innerj] = matrix[i][j];
                        innerj++;
                    }
                }
                inner++;
            }
        }
    }
    T Determinant()
    {
        T det = 0;
        int k = 1;
        if (NumRows() < 1 || NumCols() != NumRows())
        {
            throw std::runtime_error("Can't name determinant");
        }
        if (NumRows() == 1)
            det = MatrixNM[0][0];
        else if (NumRows() == 2)
            det = MatrixNM[0][0] * MatrixNM[1][1] - MatrixNM[1][0] * MatrixNM[0][1];
        else
        {
            for (size_t i = 0; i < NumRows(); i++)
            {
                size_t m = NumRows() - 1;
                Matrix<T> tempMatrix(m, m);
                CreateNewMatrix(*this, tempMatrix, 0, i);
                det = det + k * MatrixNM[0][i] * tempMatrix.Determinant();
                k = -k;
            }
        }
        return det;
    }
    Matrix<T> Inverse()
    {
        int k = 1;
        Matrix obrMatrix(NumRows(), NumRows());
        T det = Determinant();
        if (det == 0 && NumRows() != NumCols())
            throw std::runtime_error("Can't name determinant");
        for (size_t i = 0; i < NumRows(); i++)
        {
            for (size_t j = 0; j < NumRows(); j++)
            {
                size_t m = NumRows() - 1;
                Matrix<T> tempMatr(m, m);
                CreateNewMatrix(*this, tempMatr, i, j);
                obrMatrix.MatrixNM[i][j] = k * tempMatr.Determinant() / det;
                k = -k;
            }
        }
        obrMatrix.Transpose();
        return obrMatrix;
    }
    const Row& operator[](size_t index) const
    {
        return MatrixNM[index];
    }
    Row& operator[](size_t index)
    {
        return MatrixNM[index];
    }
    Polynomial<T> CharacteristicEquation()
    {
        Matrix<T> Copy(*this);
        Polynomial<T> characteristicEq(NumRows() + 1);
        characteristicEq[0] = 1;
        characteristicEq[NumRows()] = Determinant();
        for (size_t k = 1 ; k < NumRows(); ++k)
        {
            for (size_t j = 0 ; j < NumRows(); ++j)
                characteristicEq[k] += (MatrixNM[j][j] / k);
            for (size_t j = 0 ; j < NumRows(); ++j)
                Copy[j][j] -= characteristicEq[k];
            *this *= Copy;
            Copy = *this;
        }
        return characteristicEq;
    }
private:
    Row* MatrixNM;
    size_t N;
};
template<class T>
bool operator!=(const Matrix<T>& a, const Matrix<T>& b)
{
    return !(a == b);
}

template<class T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    return a += b;
}

template<class T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
{
    return a -= b;
}

template<class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
{
    return a *= b;
}

template<class T>
Matrix<T> operator*(const Matrix<T>& a, T b)
{
    return a *= b;
}

template<class T>
Matrix<T> operator*(T b, const Matrix<T>& a)
{
    return a *= b;
}
template<class T>
Matrix<T> getBasis(const Matrix<T>& vectors)
{
    if (vectors.NumCols() > vectors.NumRows())
        return std::runtime_error("can't find basis");
    Matrix<T> copy(vectors.NumCols(), vectors.NumCols());
    for (size_t k = 0; k < vectors.NumRows() - vectors.NumCols() + 1; ++k)
    {
        for (size_t i = 0; i < vectors.NumCols(); i++)
        {
            for (size_t j = 0; j < vectors.NumCols(); j++)
                copy[i][j] = vectors[i + k][j];
        }
        if (copy.Determinant() == 0)
            return copy;
    }
    return std::runtime_error("can't find basis");
}
template<class T>
std::vector<T> getCoordinates(const Matrix<T>& basis, const std::vector<T>& vector)
{
    if (basis.NumCols() != vector.size())
        throw std::invalid_argument("check dim");
    Matrix<T> basisCopy(basis);
    basisCopy = basisCopy.Inverse();
    basisCopy *= vector;
    std::vector<T> coordinates(basisCopy.NumRows());
    for (size_t i = 0; i < basisCopy.NumRows(); ++i)
        coordinates[i] = basisCopy[i][0];
    return coordinates;
}
template<class T>
Matrix<T> getTransitionMatrix(const Matrix<T>& basisFrom, const Matrix<T>& basisTo)
{
    Matrix<T> basisToCopy(basisTo);
    basisToCopy.Inverse();
    if (basisFrom.NumCols() != basisTo.NumRows() &&
        basisFrom.NumRows() != basisFrom.NumCols() &&
        basisTo.NumRows() != basisTo.NumCols())
        throw std::invalid_argument("check dim");
    return basisFrom * basisToCopy;
}
template<class T>
bool operator==(const Matrix<T>& a, const Matrix<T>& b)
{
    if ((a.NumRows() == b.NumRows()) && (a.NumCols() == b.NumCols()))
    {
        for (int i = 0; i < a.NumCols(); ++i)
            for (int j = 0; j < a.NumRows(); ++j)
                if (a[i][j] != b[i][j])
                    return false;
        return true;
    }
    return false;
}


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
    //Matrix<int> m13(v1, 5, 2);
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
