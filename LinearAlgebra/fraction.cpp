#include "fraction.h"

unsigned int get_gcd(unsigned int x,unsigned int y)
{
    unsigned int z=y;
    while(x%y!=0)
    {
        z=x%y;
        x=y;
        y=z;
    }
    return z;
}

//构造函数
Fraction::Fraction(int num,unsigned int deno=1)
{
    this->num=num;
    this->deno=deno;
    this->reduct();
}
Fraction::Fraction()
{
    this->num=0;
    this->deno=1;
}

//拷贝构造函数
Fraction::Fraction(const Fraction &b)
{
    this->num=b.num;
    this->deno=b.deno;
}
Fraction::Fraction(const int b)
{
    this->num=b;
    this->deno=1;
}
//重载算术运算符
Fraction Fraction::operator+(const Fraction &b)const
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    Fraction m(this->num*multi1+b.num*multi2,lcm);
    if(m.num!=0)
        m.reduct();
    return m;
}
Fraction Fraction::operator-(const Fraction &b)const
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    Fraction m(this->num*multi1-b.num*multi2,lcm);
    if(m.num!=0)
        m.reduct();
    return m;
}
Fraction Fraction::operator*(const Fraction &b)const
{
    Fraction m(this->num*b.num,this->deno*b.deno);
    if(m.num!=0)
        m.reduct();
    return m;
}
Fraction Fraction::operator/(const Fraction &b)const
{
    Fraction rec;
    if(b.num<0)
    {
        rec.num=0-b.deno;
        rec.deno=0-b.num;
    }
    else
    {
        rec.num=b.deno;
        rec.deno=b.num;
    }
    Fraction m(this->num*rec.num,this->deno*rec.deno);
    if(m.num!=0)
        m.reduct();
    return m;
}
Fraction Fraction::operator+=(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    this->num=this->num*multi1+b.num*multi2;
    this->deno=lcm;
    this->reduct();
    return *this;
}
Fraction Fraction::operator-=(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    this->num=this->num*multi1-b.num*multi2;
    this->deno=lcm;
    this->reduct();
    return *this;
}
Fraction Fraction::operator*=(const Fraction &b)
{
    this->num*=b.num;
    this->deno*=b.deno;
    this->reduct();
    return *this;
}
Fraction Fraction::operator/=(const Fraction &b)
{
    Fraction rec;
    if(b.num<0)
    {
        rec.num=0-b.deno;
        rec.deno=0-b.num;
    }
    else
    {
        rec.num=b.deno;
        rec.deno=b.num;
    }
    this->num*=rec.num;
    this->deno*=rec.deno;
    this->reduct();
    return *this;
}
Fraction Fraction::operator=(const Fraction &b)
{
    this->num=b.num;
    this->deno=b.deno;
    return *this;
}
Fraction Fraction::operator+(const int b)const
{
    Fraction m(b,1);
    m+=*this;
    return m;
}
Fraction Fraction::operator-(const int b)const
{
    Fraction tmp(b,1);
    Fraction m=*this;
    m-=tmp;
    return m;
}
Fraction Fraction::operator*(const int b)const
{
    Fraction m(b,1);
    m*=*this;
    return m;
}
Fraction Fraction::operator/(const int b)const
{
    Fraction tmp(b,1);
    Fraction m=*this;
    m/=tmp;
    return m;
}
Fraction Fraction::operator+=(const int b)
{
    Fraction m(b,1);
    *this+=m;
    return *this;
}
Fraction Fraction::operator-=(const int b)
{
    Fraction m(b,1);
    *this-=m;
    return *this;
}
Fraction Fraction::operator*=(const int b)
{
    Fraction m(b,1);
    *this*=m;
    return *this;
}
Fraction Fraction::operator/=(const int b)
{
    Fraction m(b,1);
    *this/=m;
    return *this;
}
Fraction Fraction::operator=(const int b)
{
    this->num=b;
    this->deno=1;
    return *this;
}
Fraction Fraction::operator-()
{
    this->num=0-this->num;
    return *this;
}
Fraction Fraction::operator++()
{
    *this+=1;
    return *this;
}
Fraction Fraction::operator++(int)
{
    Fraction tmp=*this;
    *this+=1;
    return tmp;
}
Fraction Fraction::operator--()
{
    *this-=1;
    return *this;
}
Fraction Fraction::operator--(int)
{
    Fraction tmp=*this;
    *this-=1;
    return tmp;
}

//重载关系运算符
bool Fraction::operator<(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    return this->num*multi1<b.num*multi2;
}
bool Fraction::operator>(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    return this->num*multi1>b.num*multi2;
}
bool Fraction::operator==(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    return this->num*multi1==b.num*multi2;
}
bool Fraction::operator!=(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    return this->num*multi1!=b.num*multi2;
}
bool Fraction::operator<=(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    return this->num*multi1<=b.num*multi2;
}
bool Fraction::operator>=(const Fraction &b)
{
    unsigned int gcd=get_gcd(this->deno,b.deno);
    unsigned int lcm=this->deno*b.deno/gcd;
    unsigned int multi1=lcm/this->deno;
    unsigned int multi2=lcm/b.deno;
    return this->num*multi1>=b.num*multi2;
}
bool Fraction::operator<(const int b)
{
    int tmp=b;
    tmp*=this->deno;
    return this->num<tmp;
}
bool Fraction::operator>(const int b)
{
    int tmp=b;
    tmp*=this->deno;
    return this->num>tmp;
}
bool Fraction::operator==(const int b)
{
    int tmp=b;
    tmp*=this->deno;
    return this->num==tmp;
}
bool Fraction::operator!=(const int b)
{
    int tmp=b;
    tmp*=this->deno;
    return this->num!=tmp;
}
bool Fraction::operator<=(const int b)
{
    int tmp=b;
    tmp*=this->deno;
    return this->num<=tmp;
}
bool Fraction::operator>=(const int b)
{
    int tmp=b;
    tmp*=this->deno;
    return this->num>=tmp;
}
QString Fraction::to_QString()const
{
    if(this->num==0)
        return "0";
    QString n;
    n+=QString::number(this->num);
    if(this->deno!=1)
    {
        n+='/';
        n+=QString::number(this->deno);
    }
    return n;
}

//private:
void Fraction::reduct()
{
    if(this->num==0)
        return;
    bool minus=false;
    if(this->num<0)
    {
        minus=true;
        this->num=0-this->num;
    }
    unsigned int gcd=get_gcd(this->num,this->deno);
    this->num/=gcd;
    this->deno/=gcd;
    if(minus==true)
        this->num=0-this->num;
}
