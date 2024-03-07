#include "mat_scalar_multi.h"
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <mat.h>

Mat_Scalar_Multi::Mat_Scalar_Multi(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("矩阵数乘");
    setFixedSize(400,200);

    QLineEdit *edt1=new QLineEdit;
    edt1->setParent(this);
    edt1->setPlaceholderText("数");

    QPlainTextEdit *edt2=new QPlainTextEdit;
    edt2->setParent(this);
    edt2->setPlaceholderText("矩阵");

    QLabel *lab=new QLabel;
    lab->setParent(this);
    lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    lab->setWordWrap(true);
    lab->setText("请输入数和矩阵");

    QHBoxLayout *layout=new QHBoxLayout;
    layout->setParent(this);
    layout->setDirection(QHBoxLayout::LeftToRight);
    layout->addWidget(edt1);
    layout->setStretchFactor(edt1,1);
    layout->addWidget(edt2);
    layout->setStretchFactor(edt2,2);
    layout->addWidget(lab);
    layout->setStretchFactor(lab,1);
    setLayout(layout);

    QObject::connect(edt1,&QLineEdit::textChanged,edt2,&QPlainTextEdit::textChanged);

    QObject::connect(edt2,&QPlainTextEdit::textChanged,[=]{
        if(edt1->text()==""&&edt2->toPlainText()=="")
            lab->setText("请输入数和矩阵");
        else if(edt1->text()=="")
            lab->setText("请输入数");
        else if(edt2->toPlainText()=="")
            lab->setText("请输入矩阵");
        else
        {
            Mat a(edt2->toPlainText());
            lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            QString b0=edt1->text();
            int *res=Mat::check(b0);
            if((res[0]!=1||res[1]!=1)&&a.is_empty()==true)
                lab->setText("数和矩阵输入错误");
            else if(res[0]!=1||res[1]!=1)
                lab->setText("数输入错误");
            else if(a.is_empty()==true)
                lab->setText("矩阵输入错误");
            else if(b0.size()>4)
                lab->setText("输入的数过大");
            else if(a.get_row_num()>10||a.get_colomn_num()>10)
                lab->setText("矩阵的阶数过大");
            else if(a.is_too_long()==true)
                lab->setText("矩阵中输入数字过长");
            else if(a.is_devided_by_zero()==true)
                lab->setText("矩阵中除数不能为0");
            else
            {
                int b=b0.toInt();
                a*=b;
                lab->setAlignment(Qt::AlignVCenter);
                QString n;
                for(int j=0;j<a.get_colomn_num()-1;++j)
                    n+=a[0][j].to_QString()+" ";
                n+=a[0][a.get_colomn_num()-1].to_QString();
                for(int i=1;i<a.get_row_num();++i)
                {
                    n+='\n';
                    for(int j=0;j<a.get_colomn_num()-1;++j)
                        n+=a[i][j].to_QString()+" ";
                    n+=a[i][a.get_colomn_num()-1].to_QString();
                }
                lab->setText(n);
            }
            delete [] res;
            res=nullptr;
        }
    });
}
