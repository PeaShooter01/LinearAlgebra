#ifndef FRACTION_H
#define FRACTION_H

#include <QString>

class Fraction
{
public:
    //构造函数
    Fraction(int num,unsigned int deno);
    Fraction();

    //拷贝构造函数
    Fraction(const Fraction &b);
    Fraction(const int b);

    //重载算术运算符
    Fraction operator+(const Fraction &b)const;
    Fraction operator-(const Fraction &b)const;
    Fraction operator*(const Fraction &b)const;
    Fraction operator/(const Fraction &b)const;
    Fraction operator+=(const Fraction &b);
    Fraction operator-=(const Fraction &b);
    Fraction operator*=(const Fraction &b);
    Fraction operator/=(const Fraction &b);
    Fraction operator=(const Fraction &b);
    Fraction operator+(const int b)const;
    Fraction operator-(const int b)const;
    Fraction operator*(const int b)const;
    Fraction operator/(const int b)const;
    Fraction operator+=(const int b);
    Fraction operator-=(const int b);
    Fraction operator*=(const int b);
    Fraction operator/=(const int b);
    Fraction operator=(const int b);
    Fraction operator-();
    Fraction operator++();
    Fraction operator++(int);
    Fraction operator--();
    Fraction operator--(int);

    //重载关系运算符
    bool operator<(const Fraction &b);
    bool operator>(const Fraction &b);
    bool operator==(const Fraction &b);
    bool operator!=(const Fraction &b);
    bool operator<=(const Fraction &b);
    bool operator>=(const Fraction &b);
    bool operator<(const int b);
    bool operator>(const int b);
    bool operator==(const int b);
    bool operator!=(const int b);
    bool operator<=(const int b);
    bool operator>=(const int b);

    QString to_QString()const;

private:
    void reduct();
    int num;
    unsigned int deno;
};

unsigned int get_gcd(unsigned int x,unsigned int y);

#endif // FRACTION_H
