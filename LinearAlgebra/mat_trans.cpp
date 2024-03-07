#include "mat_trans.h"
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include "mat.h"

Mat_Trans::Mat_Trans(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("矩阵转置");
    setFixedSize(300,200);

    QPlainTextEdit *edt=new QPlainTextEdit;
    edt->setParent(this);

    QLabel *lab=new QLabel;
    lab->setParent(this);
    lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    lab->setWordWrap(true);
    lab->setText("请输入矩阵");

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
            lab->setText("请输入矩阵");
        else if(a.is_empty()==true)
            lab->setText("输入错误");
        else if(a.get_row_num()>10||a.get_colomn_num()>10)
            lab->setText("矩阵的阶数过大");
        else if(a.is_too_long()==true)
            lab->setText("输入数字过长");
        else if(a.is_devided_by_zero()==true)
            lab->setText("除数不能为0");
        else
        {
            lab->setAlignment(Qt::AlignVCenter);
            a.mat_trans();
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
    });
}
