#ifndef MAT_H
#define MAT_H

#include "fraction.h"

class Mat
{
public:
    //构造函数
    Mat(QString n);
    Mat(int a,int b);
    Mat();

    //拷贝构造函数
    Mat(const Mat &obj);

    //析构函数
     ~Mat();

    //重载运算符
    Mat operator+(const Mat &b)const;
    Mat operator+=(const Mat &b);
    Mat operator-(const Mat &b)const;
    Mat operator-();
    Mat operator=(const Mat &b);
    Mat operator-=(const Mat &b);
    Mat operator*(const Fraction b)const;
    Mat operator*=(const Fraction b);
    Mat operator*(const Mat &b)const;
    Mat operator*=(const Mat &b);
    const Fraction* operator[](const int index)const;

    bool is_empty(void)const;
    Fraction get_det_sum(void);
    const Mat get_mat_adjoint(void);
    const Mat get_mat_inverse(void);
    const Mat get_mat_echelon(void);
    void mat_trans(void);
    int get_row_num(void)const;
    int get_colomn_num(void)const;
    bool is_devided_by_zero(void)const;
    bool is_too_long(void)const;

    //静态成员函数
    static int* check(QString &n);

private:
    void mat_adjoint(void);
    void det_sum(void);
    void mat_inverse(void);
    void mat_echelon(void);
    Fraction det_sum_eva(const int len,bool* row,bool* colomn)const;
    Fraction **value;
    int x;
    int y;
    Fraction *det_sum_value;
    Mat *mat_adjoint_value;
    Mat *mat_inverse_value;
    Mat *mat_echelon_value;
    bool devided_by_zero;
    bool too_long;
};

#endif // MAT_H
