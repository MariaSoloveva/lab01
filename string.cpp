#pragma once
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>


template <class T>
class Polynomial
{
public:
    Polynomial()
    {
        Coefficients.push_back(0);
    }
    ~Polynomial()
    {
        Coefficients.clear();
    }
    Polynomial(size_t a)
    {
        for(size_t i = 0; i < a; ++i)
            Coefficients.push_back(0);
    }
    Polynomial(const Polynomial& a)
    {
        for(size_t i = 0; i < a.Coefficients.size(); ++i)
            Coefficients.push_back(a.Coefficients[i]);
    }
    Polynomial(const std::vector<T>& coef)
    {
        for (size_t i = 0; i < coef.size(); ++i)
            Coefficients.push_back(coef[i]);
    }

    T& operator[](size_t index)
    {
        return Coefficients[index];
    }
    T operator[](size_t index) const
    {
        return Coefficients[index];
    }

    size_t Degree() const
    {
        return Coefficients.size() - 1;
    }
    Polynomial& operator = (const Polynomial& a)
    {
        Coefficients.clear();
        for(size_t i = 0; i < a.Degree() + 1; ++i)
        {
            Coefficients.push_back(a[i]);
        }
        return *this;
    }
    Polynomial& operator += (const Polynomial& a)
    {
        if(Coefficients.size() > a.Coefficients.size())
        {
            for (size_t i = 1; i < a.Coefficients.size() + 1; ++i)
                Coefficients[Coefficients.size() - i] += a[a.Coefficients.size() - i];
            return *this;
        }
        else
        {
            Polynomial <T>pol(a);
            for (size_t i = 1; i < Coefficients.size() + 1; ++i)
                pol[a.Coefficients.size() - i] += Coefficients[Coefficients.size() - i];
            return pol;
        }
    }
    Polynomial& operator -= (const Polynomial& a)
    {
        Polynomial pol(a);
        if(Coefficients.size() >= a.Coefficients.size())
        {
            for (size_t i = 1; i < a.Coefficients.size() + 1; ++i)
                Coefficients[Coefficients.size() - i] -= a[a.Coefficients.size() - i];
            return *this;
        }
        else
        {
            for (size_t i = 1; i < Coefficients.size() + 1; ++i)
                pol[a.Coefficients.size() - i] -= Coefficients[Coefficients.size() - i];
            return pol;
        }
    }
    Polynomial& operator *= (const Polynomial& a)
    {
        std::vector<T> newVec(1);
        for(size_t i = 0; i < this->Degree() + a.Degree(); ++i)
            newVec.push_back(0);
        for(size_t i = 0; i < a.Coefficients.size(); ++i)
            for(size_t j = 0; j < Coefficients.size(); ++j)
                newVec[i + j] += a.Coefficients[i] * Coefficients[j];
        Polynomial pol(newVec);
        return pol;
    }
    Polynomial& operator *= (T c)
    {
        for(size_t i = 0; i < Coefficients.size(); ++i)
            Coefficients[i] *= c;
        return *this;
    }

    Polynomial& operator /= (const Polynomial& a)
    {
        Polynomial <T>copy(*this);
        int inner = copy.Degree() - a.Degree() + 1;
        std::vector<T> vec(inner);
        for(size_t i = 0; i < inner; ++i)
        {
            Polynomial pol(a);
            for(size_t j = 0; j < copy.Degree() - a.Degree(); ++j)
                pol.Coefficients.push_back(0);
            pol *= (copy.Coefficients[0] / a.Coefficients[0]);
            vec[i] = copy.Coefficients[0] / a.Coefficients[0];
            copy -= pol;
            for(size_t j = 0; j < copy.Degree() - a.Degree(); ++j)
                pol.Coefficients.erase(pol.Coefficients.begin());
            copy.Coefficients.erase(copy.Coefficients.begin());
        }
        Polynomial <T>pol(vec);
        return pol;
    }
    Polynomial& operator %= (const Polynomial& a)
    {
        Polynomial copy(*this);
        int inner = copy.Degree() - a.Degree() + 1;
        for(size_t i = 0; i < inner; ++i)
        {
            Polynomial pol(a);
            for(size_t j = 0; j < copy.Degree() - a.Degree(); ++j)
                pol.Coefficients.push_back(0);
            pol *= (copy.Coefficients[0] / a.Coefficients[0]);
            copy -= pol;
            for(size_t j = 0; j < copy.Degree() - a.Degree(); ++j)
                pol.Coefficients.erase(pol.Coefficients.begin());
            copy.Coefficients.erase(copy.Coefficients.begin());
        }
        return copy;
    }

    T operator()(const T& a) const
    {
        T number = 0;
        for(size_t i = 0 ; i < this->Degree(); ++i)
            number += Coefficients[i] * pow(a, this->Degree());
        return number;
    }

    /*auto begin() const -> decltype(Coefficients.begin())
    {
        return Coefficients.begin();
    }

    auto end() const -> decltype(Coefficients.end())
    {
        return Coefficients.end();
    }*/

private:
    std::vector<T> Coefficients;
};

template<class T>
bool operator==(const Polynomial<T>& a, const Polynomial<T>& b)
{
    /*if (std::distance(a.begin(), a.end()) == std::distance(b.begin(), b.end()))
    {
        for (size_t i = a.begin(); i < std::distance(a.begin(), a.end()); ++i)
            if (*(a.begin() + i) != *(b.begin() + i))
                return false;
        return true;
    }
    return false;*/
}

template<class T>
bool operator!=(const Polynomial<T>& a, const Polynomial<T>& b)
{
    return !(a == b);
}

template<class T>
Polynomial<T> operator+(const Polynomial<T>& a, const Polynomial<T>& b)
{
    Polynomial <T>c(a);
    c += b;
    return c;
}

template<class T>
Polynomial<T> operator-(const Polynomial<T>& a, const Polynomial<T>& b)
{
    Polynomial <T>c(a);
    c -= b;
    return c;
}

template<class T>
Polynomial<T> operator*(const Polynomial<T>& a, const Polynomial<T>& b)
{
    Polynomial <T>c(a);
    c *= b;
    return c;
}

template<class T>
Polynomial<T> operator/(const Polynomial<T>& a, const Polynomial<T>& b)
{
    Polynomial <T>c(a);
    c /= b;
    return c;
}

template<class T>
Polynomial<T> operator%(const Polynomial<T>& a, const Polynomial<T>& b)
{
    Polynomial <T>c(a);
    c %= b;
    return c;
}

template<class T>
Polynomial<T> operator*(const Polynomial<T>& a, T b)
{
    Polynomial <T>c(a);
    c *= b;
    return c;
}
template<class T>
Polynomial<T> operator*(T b, const Polynomial<T>& a)
{
    Polynomial <T>c(a);
    c *= b;
    return c;
}

int main()
{
    std::vector<double> vec ={1,2,1};
    std::vector<double> vec1 ={5,2,6,0,1};
    Polynomial <double>polyOfVec(vec);
    Polynomial <double>poly;
    Polynomial <double>polyOfVec1(vec1);
    polyOfVec1 /= polyOfVec;
    polyOfVec1 %= polyOfVec;
    polyOfVec1 *= polyOfVec;
    poly = polyOfVec1 % polyOfVec;
    poly = polyOfVec * 4.;
    poly = 7. * poly;
    polyOfVec += polyOfVec1;
    polyOfVec1 = polyOfVec + polyOfVec;
    polyOfVec1 *= polyOfVec;
    std::cout << (polyOfVec1 == polyOfVec) << std::endl;
    std::cout << (polyOfVec1 != polyOfVec) << std::endl;
    return 0;
}
