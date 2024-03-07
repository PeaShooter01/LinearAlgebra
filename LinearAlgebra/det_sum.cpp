#include "det_sum.h"
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QLabel>
#include "mat.h"

Det_Sum::Det_Sum(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("行列式求值");
    setFixedSize(300,200);

    QPlainTextEdit *edt=new QPlainTextEdit;
    edt->setParent(this);

    QLabel *lab=new QLabel;
    lab->setParent(this);
    lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    lab->setWordWrap(true);
    lab->setText("请输入行列式");

    QHBoxLayout *layout=new QHBoxLayout;
    layout->setParent(this);
    layout->setDirection(QHBoxLayout::LeftToRight);
    layout->addWidget(edt);
    layout->setStretchFactor(edt,2);
    layout->addWidget(lab);
    layout->setStretchFactor(lab,1);
    setLayout(layout);

    QObject::connect(edt,&QPlainTextEdit::textChanged,[=]{
        Mat a(edt->toPlainText());
        lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        if(edt->toPlainText()=="")
            lab->setText("请输入行列式");
        else if(a.is_empty()==true)
            lab->setText("输入错误");
        else if(a.get_row_num()>10||a.get_colomn_num()>10)
            lab->setText("行列式的阶数过大");
        else if(a.is_too_long()==true)
            lab->setText("输入数字过长");
        else if(a.is_devided_by_zero()==true)
            lab->setText("除数不能为0");
        else
        {
            lab->setAlignment(Qt::AlignVCenter);
            try
            {
                lab->setText(a.get_det_sum().to_QString());
            }
            catch(const char* msg)
            {
                lab->setText(msg);
            }
        }
    });
}
