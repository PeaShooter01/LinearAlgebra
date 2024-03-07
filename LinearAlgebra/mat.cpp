/*
 * 当在堆区开辟内存时：1.在构造函数中赋初始值。2.在拷贝构造函数中实现深拷贝。3.在析构函数和重载=运算符函数中析构。
 */
#include "mat.h"

//构造函数
Mat::Mat(QString n)
{
    this->det_sum_value=nullptr;
    this->mat_adjoint_value=nullptr;
    this->mat_inverse_value=nullptr;
    this->mat_echelon_value=nullptr;
    this->devided_by_zero=false;
    this->too_long=false;

    int *a=Mat::check(n);
    this->x=a[0];
    this->y=a[1];
    delete [] a;
    a=nullptr;
    if(this->x==-1||this->y==-1)
    {
        this->value=nullptr;
        return;
    }
    int tag=0,row=0,colomn=0,div=-1;
    this->value=new Fraction*[this->x];
    for(int i=0;i<this->x;++i)
        this->value[i]=new Fraction[this->y];
    for(int i=0;i<n.size();++i)
    {
        if(n[i]=='/')
            div=i;
        if(n[i]==' '||n[i]=='\n')
        {
            if(div==-1)
            {
                    this->value[row][colomn]=n.mid(tag,i-tag).toInt();
                if(i-tag>4)
                    this->too_long=true;
            }
            else
            {
                this->value[row][colomn]=Fraction(n.mid(tag,div-tag).toInt(),n.mid(div+1,i-div-1).toInt());
                if(n.mid(div+1,i-div-1).toInt()==0)
                    this->devided_by_zero=true;
                if(div-tag>4||i-div-1>4)
                    this->too_long=true;
                div=-1;
            }
            ++colomn;
            tag=++i;
            if(colomn==this->y)
            {
                colomn=0;
                ++row;
            }
        }
    }
    if(div==-1)
    {
        this->value[row][colomn]=n.mid(tag,n.size()-tag).toInt();
        if(n.size()-tag>4)
            this->too_long=true;
    }
    else
    {
        this->value[row][colomn]=Fraction(n.mid(tag,div-tag).toInt(),n.mid(div+1,n.size()-div-1).toInt());
        if(n.mid(div+1,n.size()-div-1).toInt()==0)
            this->devided_by_zero=true;
        if(div-tag>4||n.size()-div-1>4)
            this->too_long=true;
    }
}
Mat::Mat()
{
    this->x=-1;
    this->y=-1;
    this->value=nullptr;
    this->det_sum_value=nullptr;
    this->mat_adjoint_value=nullptr;
    this->mat_inverse_value=nullptr;
    this->mat_echelon_value=nullptr;
    this->devided_by_zero=false;
    this->too_long=false;
}
Mat::Mat(int a,int b)
{
    this->x=a;
    this->y=b;
    this->value=new Fraction*[a];
    for(int i=0;i<a;++i)
        this->value[i]=new Fraction[b];
    this->det_sum_value=nullptr;
    this->mat_adjoint_value=nullptr;
    this->mat_inverse_value=nullptr;
    this->mat_echelon_value=nullptr;
    for(int i=0;i<a;++i)
        for(int j=0;j<b;++j)
            this->value[i][j]=0;
    this->devided_by_zero=false;
    this->too_long=false;
}

//拷贝构造函数
Mat::Mat(const Mat &obj)
{
    this->x=obj.x;
    this->y=obj.y;
    this->devided_by_zero=obj.devided_by_zero;
    this->too_long=obj.too_long;
    if(obj.value==nullptr)
        this->value=nullptr;
    else
    {
        this->value=new Fraction*[this->x];
        for(int i=0;i<this->x;++i)
            value[i]=new Fraction[this->y];
        for(int i=0;i<this->x;++i)
            for(int j=0;j<this->y;++j)
                this->value[i][j]=obj.value[i][j];
    }
    if(obj.det_sum_value==nullptr)
        this->det_sum_value=nullptr;
    else
    {
        if(this->det_sum_value==nullptr)
            this->det_sum_value=new Fraction;
        *this->det_sum_value=*obj.det_sum_value;
    }
    if(obj.mat_adjoint_value==nullptr)
        this->mat_adjoint_value=nullptr;
    else
    {
        if(this->mat_adjoint_value==nullptr)
            this->mat_adjoint_value=new Mat;
        *this->mat_adjoint_value=*obj.mat_adjoint_value;
    }
    if(obj.mat_inverse_value==nullptr)
        this->mat_inverse_value=nullptr;
    else
    {
        if(this->mat_inverse_value==nullptr)
            this->mat_inverse_value=new Mat;
        *this->mat_inverse_value=*obj.mat_inverse_value;
    }
    if(obj.mat_echelon_value==nullptr)
        this->mat_echelon_value=nullptr;
    else
    {
        if(this->mat_echelon_value==nullptr)
            this->mat_echelon_value=new Mat;
        *this->mat_echelon_value=*obj.mat_echelon_value;
    }
}

//析构函数
Mat::~Mat()
{
    if(this->value!=nullptr)
    {
        for(int i=0;i<this->x;++i)
            delete [] this->value[i];
        delete [] this->value;
        this->value=nullptr;
    }
    if(this->det_sum_value!=nullptr)
    {
        delete this->det_sum_value;
        this->det_sum_value=nullptr;
    }
    if(this->mat_adjoint_value!=nullptr)
    {
        delete this->mat_adjoint_value;
        this->mat_adjoint_value=nullptr;
    }
    if(this->mat_inverse_value!=nullptr)
    {
        delete this->mat_inverse_value;
        this->mat_inverse_value=nullptr;
    }
    if(this->mat_echelon_value!=nullptr)
    {
        delete this->mat_echelon_value;
        this->mat_echelon_value=nullptr;
    }
}

//重载运算符
Mat Mat::operator+(const Mat &b)const
{
    Mat mat=b;
    if(mat.is_empty()==true||this->is_empty()==true)
        return Mat();
    if(mat.x!=this->x||mat.y!=this->y)
        return Mat();
    for(int i=0;i<this->x;++i)
        for(int j=0;j<this->y;++j)
            mat.value[i][j]+=this->value[i][j];
    return mat;
}
Mat Mat::operator+=(const Mat &b)
{
    if(b.is_empty()==true||this->is_empty()==true)
    {
        *this=Mat();
        return *this;
    }
    if(b.x!=this->x||b.y!=this->y)
    {
        *this=Mat();
        return *this;
    }
    for(int i=0;i<this->x;++i)
        for(int j=0;j<this->y;++j)
            this->value[i][j]+=b.value[i][j];
    return *this;
}
Mat Mat::operator=(const Mat &b)
{
    if(this->value!=nullptr)
    {
        for(int i=0;i<this->x;++i)
            delete [] this->value[i];
        delete [] this->value;
        this->value=nullptr;
    }
    delete this->det_sum_value;
    if(b.det_sum_value==nullptr)
        this->det_sum_value=nullptr;
    else
    {
        if(this->det_sum_value==nullptr)
            this->det_sum_value=new Fraction;
        *this->det_sum_value=*b.det_sum_value;
    }
    if(b.mat_adjoint_value==nullptr)
        this->mat_adjoint_value=nullptr;
    else
    {
        if(this->mat_adjoint_value==nullptr)
            this->mat_adjoint_value=new Mat;
        *this->mat_adjoint_value=*b.mat_adjoint_value;
    }
    if(b.mat_inverse_value==nullptr)
        this->mat_inverse_value=nullptr;
    else
    {
        if(this->mat_inverse_value==nullptr)
            this->mat_inverse_value=new Mat;
        *this->mat_inverse_value=*b.mat_inverse_value;
    }
    this->x=b.x;
    this->y=b.y;
    this->devided_by_zero=b.devided_by_zero;
    this->too_long=b.too_long;
    if(this->x==-1||this->y==-1)
    {
        this->value=nullptr;
        return *this;
    }
    this->value=new Fraction*[this->x];
    for(int i=0;i<this->x;++i)
        this->value[i]=new Fraction[this->y];
    for(int i=0;i<this->x;++i)
        for(int j=0;j<this->y;++j)
            this->value[i][j]=b.value[i][j];
    return *this;
}
Mat Mat::operator-(const Mat &b)const
{
    if(b.is_empty()==true||this->is_empty()==true)
        return Mat();
    if(b.x!=this->x||b.y!=this->y)
        return Mat();
    Mat mat=*this;
    Mat mat2=b;
    -mat2;
    return mat+mat2;
}
Mat Mat::operator-=(const Mat &b)
{
    if(b.is_empty()==true||this->is_empty()==true)
        return Mat();
    if(b.x!=this->x||b.y!=this->y)
        return Mat();
    Mat mat2=b;
    -mat2;
    *this=*this+mat2;
    return *this;
}
Mat Mat::operator-()
{
    for(int i=0;i<this->x;++i)
        for(int j=0;j<this->y;++j)
            -this->value[i][j];
    return *this;
}
Mat Mat::operator*(const Fraction b)const
{
    Mat mat=*this;
    if(mat.is_empty()==true)
        return Mat();
    for(int i=0;i<this->x;++i)
        for(int j=0;j<this->y;++j)
            mat.value[i][j]=mat.value[i][j]*b;
    return mat;
}
Mat Mat::operator*=(const Fraction b)
{
    if(this->is_empty()==true)
        return Mat();
    for(int i=0;i<this->x;++i)
        for(int j=0;j<this->y;++j)
            this->value[i][j]=this->value[i][j]*b;
    return *this;
}
Mat Mat::operator*(const Mat &b)const
{
    if(this->x==-1||this->y==-1||b.x==-1||b.y==-1)
        return Mat();
    if(this->y==b.x)
    {
        Mat res(this->x,b.y);
        Fraction sum;
        int row=0,colomn=0;
                for(int i=0;i<this->x;i++)
                {
                    sum=0;
                    for(int k=0;k<this->y;k++)
                        sum+=this->value[i][k]*b.value[k][0];
                    res.value[row][colomn]=sum;
                    for(int j=1;j<b.y;j++)
                    {
                        sum=0;
                        for(int k=0;k<this->y;k++)
                            sum+=this->value[i][k]*b.value[k][j];
                        ++colomn;
                        res.value[row][colomn]=sum;
                    }
                    ++row;
                    colomn=0;
                }
        return res;
    }
    else
        return Mat();
}
Mat Mat::operator*=(const Mat &b)
{
    if(this->x==-1||this->y==-1||b.x==-1||b.y==-1)
    {
        *this=Mat();
        return *this;
    }
    if(this->y==b.x)
    {
        Mat res(this->x,b.y);
        Fraction sum;
        int row=0,colomn=0;
                for(int i=0;i<this->x;i++)
                {
                    sum=0;
                    for(int k=0;k<this->y;k++)
                        sum+=this->value[i][k]*b.value[k][0];
                    res.value[row][colomn]=sum;
                    for(int j=1;j<b.y;j++)
                    {
                        sum=0;
                        for(int k=0;k<this->y;k++)
                            sum+=this->value[i][k]*b.value[k][j];
                        ++colomn;
                        res.value[row][colomn]=sum;
                    }
                    ++row;
                    colomn=0;
                }
        *this=res;
        return *this;
    }
    else
    {
        *this=Mat();
        return *this;
    }
}
const Fraction* Mat::operator[](const int index) const
{
    return this->value[index];
}

//public:
bool Mat::is_empty(void)const
{
    if(this->x==-1||this->y==-1||this->value==nullptr)
        return true;
    else
        return false;
}
Fraction Mat::get_det_sum(void)
{
    if(this->x!=this->y)
        throw "行列式的行\n数与列数不\n相等";
    if(this->det_sum_value==nullptr)
        this->det_sum();
    return *this->det_sum_value;
}
const Mat Mat::get_mat_adjoint(void)
{
    if(this->x!=this->y)
        throw "输入的矩阵\n不是方阵";
    if(this->mat_adjoint_value==nullptr)
        this->mat_adjoint();
    return *this->mat_adjoint_value;
}
const Mat Mat::get_mat_inverse(void)
{
    if(this->x!=this->y)
        throw "输入的矩阵\n不是方阵";
    if(this->det_sum_value==nullptr)
        det_sum();
    if(this->mat_adjoint_value==nullptr)
        mat_adjoint();
    if(*this->det_sum_value==0)
        throw "该矩阵不可逆";
    if(this->mat_inverse_value==nullptr)
        mat_inverse();
    return *this->mat_inverse_value;
}
const Mat Mat::get_mat_echelon(void)
{
    if(this->mat_echelon_value==nullptr)
        mat_echelon();
    return *this->mat_echelon_value;
}
int Mat::get_row_num(void)const
{
    return this->x;
}
int Mat::get_colomn_num(void)const
{
    return this->y;
}
bool Mat::is_devided_by_zero(void)const
{
    return this->devided_by_zero;
}
bool Mat::is_too_long(void)const
{
    return this->too_long;
}
void Mat::mat_trans(void)
{
    Mat a(this->y,this->x);
    if(this->value!=nullptr)
        for(int i=0;i<this->x;++i)
            for(int j=0;j<this->y;++j)
                a.value[j][i]=this->value[i][j];
    *this=a;
}

//private:
void Mat::det_sum(void)
{
    if(this->x==1)
    {
        this->det_sum_value=new Fraction;
        *this->det_sum_value=this->value[0][0];
        return;
    }
    if(this->x==2)
    {
        this->det_sum_value=new Fraction;
        *this->det_sum_value=this->value[0][0]*this->value[1][1]-this->value[0][1]*this->value[1][0];
        return;
    }
    bool *row=new bool [this->x];
    bool *colomn=new bool [this->y];
    for(int i=0;i<this->x;i++)
        row[i]=false;
    for(int i=0;i<this->y;i++)
        colomn[i]=false;
    Fraction sum=0;
    row[0]=true;
    for(int i=0;i<this->x;i++)
    {
        colomn[i]=true;
        sum+=this->value[0][i]*this->det_sum_eva(this->x-1,row,colomn)*pow(-1,i);
        colomn[i]=false;
    }
    delete [] row;
    row=nullptr;
    delete [] colomn;
    colomn=nullptr;
    this->det_sum_value=new Fraction;
    *this->det_sum_value=sum;
}
void Mat::mat_adjoint(void)
{
    Mat tmp(this->x,this->y);
    if(this->x==1&&this->y==1)
        tmp.value[0][0]=1;
    if(this->x==2&&this->y==2)
    {
        tmp.value[0][0]=this->value[1][1];
        tmp.value[1][1]=this->value[0][0];
        tmp.value[0][1]=this->value[0][1];
        tmp.value[1][0]=this->value[1][0];
    }
    bool *row=new bool [this->x];
    bool *colomn=new bool [this->x];
    for(int i=0;i<this->x;i++)
    {
        row[i]=false;
        colomn[i]=false;
        for(int j=0;j<this->x;j++)
            tmp.value[i][j]=0;
    }
    for(int i=0;i<this->x;i++)
        for(int j=0;j<this->x;j++)
        {
            row[i]=true;
            colomn[j]=true;
            tmp.value[i][j]=det_sum_eva(this->x-1,row,colomn)*pow(-1,i+j);
            row[i]=false;
            colomn[j]=false;
        }
    delete [] row;
    delete [] colomn;
    this->mat_adjoint_value=new Mat(this->y,this->x);
    for(int i=0;i<this->x;i++)
        for(int j=0;j<this->x;j++)
            this->mat_adjoint_value->value[i][j]=tmp.value[j][i];
}
void Mat::mat_inverse(void)
{
    this->mat_inverse_value=new Mat(this->y,this->x);
    for(int i=0;i<this->y;i++)
        for(int j=0;j<this->x;j++)
            this->mat_inverse_value->value[i][j]=this->mat_adjoint_value->value[i][j]/(*this->det_sum_value);
}
void Mat::mat_echelon(void)
{
    Fraction tmp,div;
    this->mat_echelon_value=new Mat(this->x,this->y);
    for(int i=0;i<this->x;++i)
        for(int j=0;j<this->y;++j)
            this->mat_echelon_value->value[i][j]=this->value[i][j];
    for(int j=0;j<std::min(this->x,this->y);++j)
    {
        for(int i=j+1;i<this->x;++i)
            if(this->mat_echelon_value->value[j][j]==0&&this->mat_echelon_value->value[i][j]!=0)
            {
                for(int k=j;k<this->y;++k)
                {
                    tmp=this->mat_echelon_value->value[j][k];
                    this->mat_echelon_value->value[j][k]=this->mat_echelon_value->value[i][k];
                    this->mat_echelon_value->value[i][k]=tmp;
                }
                break;
            }
        for(int i=j+1;i<this->x;++i)
        {
            div=this->mat_echelon_value->value[i][j]/this->mat_echelon_value->value[j][j];
            for(int k=j;k<this->y;++k)
                this->mat_echelon_value->value[i][k]-=this->mat_echelon_value->value[j][k]*div;
        }
    }
}
Fraction Mat::det_sum_eva(const int len,bool* row,bool* colomn)const
{
    if(len==2)
    {
        Fraction sum;
        int i,r1,r2,c1,c2;
        for(i=0;i<this->x;i++)
        {
            if(row[i]==false)
            {
                r1=i;
                int j;
                for(j=0;j<this->x;j++)
                    if(colomn[j]==false)
                    {
                        c1=j;
                        break;
                    }
                for(j++;j<this->x;j++)
                    if(colomn[j]==false)
                    {
                        c2=j;
                        break;
                    }
                break;
            }
        }
        for(++i;;++i)
            if(row[i]==false)
            {
                r2=i;
                break;
            }
        sum=this->value[r1][c1]*this->value[r2][c2]-this->value[r1][c2]*this->value[r2][c1];
        return sum;
    }
    int tmp=0;
    Fraction sum=0;
    for(int i=0;i<this->x;i++)
    {
        if(row[i]==false)
        {
            sum=0;
            for(int j=0;j<this->x;j++)
            {
                if(colomn[j]==false)
                {
                    row[i]=true;
                    colomn[j]=true;
                    sum+=this->value[i][j]*this->det_sum_eva(len-1,row,colomn)*pow(-1,i+j-tmp);
                    row[i]=false;
                    colomn[j]=false;
                }
                else
                    tmp++;
            }
            break;
        }
        tmp++;
    }
    return sum;
}

//静态成员函数
int* Mat::check(QString &n)
{
    int row=1,colomn=1,colomn0=1;
    int *ret=new int[2];
    ret[0]=-1;
    ret[1]=-1;
    bool tag=false;
    if(n=="")
        return ret;
    if(!(n[0]>='0'&&n[0]<='9')&&n[0]!='-')
        return ret;
    if(!(n[n.size()-1]>='0'&&n[n.size()-1]<='9'))
        return ret;
    for(int i=1;i<n.size()-1;++i)
    {
        if(n[i]!='/'&&n[i]!=' '&&n[i]!='\n'&&n[i]!='-'&&!(n[i]>='0'&&n[i]<='9'))
            return ret;
        if((n[i]==' '||n[i]=='\n')&&(n[i-1]==' '||n[i-1]=='\n'))
            return ret;
        if(n[i]=='-'&&i<n.size()-1)
            if(!(n[i+1]>='0'&&n[i+1]<='9'))
                return ret;
        if(n[i]=='-'&&n[i-1]!=' '&&n[i-1]!='\n')
            return ret;
        if(n[i]=='/'&&!(n[i+1]>='0'&&n[i+1]<='9')&&!(n[i-1]>='0'&&n[i-1]<='9'))
            return ret;
    }
    for(int i=1;i<n.size();++i)
    {
        if(n[i]==' '&&tag==false)
            ++colomn;
        if(n[i]==' '&&tag==true)
            ++colomn0;
        if(n[i]=='\n'&&tag==false)
        {
            tag=true;
            ++row;
            continue;
        }
        if(n[i]=='\n'&&tag==true)
        {
            tag=true;
            ++row;
            if(colomn0!=colomn)
                return ret;
            colomn0=1;
        }
    }
    if(colomn0!=colomn&&row>1)
        return ret;
    ret[0]=row;
    ret[1]=colomn;
    return ret;
}
