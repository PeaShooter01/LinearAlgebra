#include "mat_add.h"
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include "mat.h"

Mat_Add::Mat_Add(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("矩阵加减法");
    setFixedSize(600,200);

    QPlainTextEdit *edt1=new QPlainTextEdit;
    edt1->setParent(this);
    edt1->setPlaceholderText("矩阵1");

    QPlainTextEdit *edt2=new QPlainTextEdit;
    edt2->setParent(this);
    edt2->setPlaceholderText("矩阵2");

    QLabel *lab=new QLabel;
    lab->setParent(this);
    lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    lab->setWordWrap(true);
    lab->setText("请输入矩阵1和2");

    QWidget *func=new QWidget;
    func->setParent(this);

    QRadioButton *add=new QRadioButton;
    add->setParent(func);
    add->setText("加法");
    add->setChecked(true);

    QRadioButton *sub=new QRadioButton;
    sub->setParent(func);
    sub->setText("减法");

    QVBoxLayout *func_layout=new QVBoxLayout;
    func_layout->setParent(func);
    func_layout->setDirection(QHBoxLayout::TopToBottom);
    func_layout->addWidget(add);
    func_layout->addWidget(sub);
    func->setLayout(func_layout);

    QHBoxLayout *layout=new QHBoxLayout;
    layout->setParent(this);
    layout->setDirection(QHBoxLayout::LeftToRight);
    layout->addWidget(func);
    layout->setStretchFactor(func,1);
    layout->addWidget(edt1);
    layout->setStretchFactor(edt1,2);
    layout->addWidget(edt2);
    layout->setStretchFactor(edt2,2);
    layout->addWidget(lab);
    layout->setStretchFactor(lab,1);
    setLayout(layout);

    QObject::connect(add,&QRadioButton::toggled,edt2,&QPlainTextEdit::textChanged);
    QObject::connect(sub,&QRadioButton::toggled,edt2,&QPlainTextEdit::textChanged);
    QObject::connect(edt1,&QPlainTextEdit::textChanged,edt2,&QPlainTextEdit::textChanged);

    QObject::connect(edt2,&QPlainTextEdit::textChanged,[=]{
        Mat a(edt1->toPlainText());
        Mat b(edt2->toPlainText());
        lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        if(edt1->toPlainText()==""&&edt2->toPlainText()=="")
            lab->setText("请输入矩阵1和2");
        else if(edt1->toPlainText()=="")
            lab->setText("请输入矩阵1");
        else if(edt2->toPlainText()=="")
            lab->setText("请输入矩阵2");
        else if(a.is_empty()==true&&b.is_empty()==true)
            lab->setText("矩阵1和2输入错误");
        else if(a.is_empty()==true)
            lab->setText("矩阵1输入错误");
        else if(b.is_empty()==true)
            lab->setText("矩阵2输入错误");
        else if((a.get_row_num()>10||a.get_colomn_num()>10)&&(b.get_row_num()>10||b.get_colomn_num()>10))
            lab->setText("矩阵1和2的阶数过大");
        else if(a.get_row_num()>10||a.get_colomn_num()>10)
            lab->setText("矩阵1的阶数过大");
        else if(b.get_row_num()>10||b.get_colomn_num()>10)
            lab->setText("矩阵2的阶数过大");
        else if(a.is_too_long()==true&&b.is_too_long()==true)
            lab->setText("矩阵1和2中输入数字过长");
        else if(a.is_too_long()==true)
            lab->setText("矩阵1中输入数字过长");
        else if(b.is_too_long()==true)
            lab->setText("矩阵2中输入数字过长");
        else if(a.is_devided_by_zero()==true&&b.is_devided_by_zero()==true)
            lab->setText("矩阵1和2中除数不能为0");
        else if(a.is_devided_by_zero()==true)
            lab->setText("矩阵1中除数不能为0");
        else if(b.is_devided_by_zero()==true)
            lab->setText("矩阵2中除数不能为0");
        else
        {
            Mat sum;
            if(add->isChecked())
                sum=a+b;
            else
                sum=a-b;
            if(sum.is_empty()==true)
                lab->setText("两个矩阵无法相加");
            else
            {
                lab->setAlignment(Qt::AlignVCenter);
                QString n;
                for(int j=0;j<sum.get_colomn_num()-1;++j)
                    n+=sum[0][j].to_QString()+" ";
                n+=sum[0][sum.get_colomn_num()-1].to_QString();
                for(int i=1;i<sum.get_row_num();++i)
                {
                    n+='\n';
                    for(int j=0;j<sum.get_colomn_num()-1;++j)
                        n+=sum[i][j].to_QString()+" ";
                    n+=sum[i][sum.get_colomn_num()-1].to_QString();
                }
                lab->setText(n);
            }
        }
    });
}
