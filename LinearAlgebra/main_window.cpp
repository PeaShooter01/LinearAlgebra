#include "main_window.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "det_sum.h"
#include "mat_trans.h"
#include "mat_add.h"
#include "mat_scalar_multi.h"
#include "mat_multi.h"
#include "mat_adjoint.h"
#include "mat_inverse.h"
#include "mat_simp.h"
#include "about.h"

Main_Window::Main_Window(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("线代神器v2.0");
    setFixedSize(200,405);//每个元素高45

    QLabel *lab=new QLabel;
    lab->setParent(this);
    lab->setText("欢迎使用线代神器！");
    lab->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QPushButton *but1=new QPushButton;
    but1->setParent(this);
    but1->setText("行列式求值");

    QPushButton *but2=new QPushButton;
    but2->setParent(this);
    but2->setText("矩阵转置");

    QPushButton *but3=new QPushButton;
    but3->setParent(this);
    but3->setText("矩阵加减法");

    QPushButton *but4=new QPushButton;
    but4->setParent(this);
    but4->setText("矩阵数乘");

    QPushButton *but5=new QPushButton;
    but5->setParent(this);
    but5->setText("矩阵乘法");

    QPushButton *but6=new QPushButton;
    but6->setParent(this);
    but6->setText("求伴随矩阵");

    QPushButton *but7=new QPushButton;
    but7->setParent(this);
    but7->setText("求逆矩阵");

    QPushButton *but8=new QPushButton;
    but8->setParent(this);
    but8->setText("化阶梯形矩阵");

    QPushButton *but9=new QPushButton;
    but9->setParent(this);
    but9->setText("关于");

    QVBoxLayout *layout=new QVBoxLayout;
    layout->setParent(this);
    layout->setDirection(QVBoxLayout::TopToBottom);
    layout->addWidget(lab);
    layout->addWidget(but1);
    layout->addWidget(but2);
    layout->addWidget(but3);
    layout->addWidget(but4);
    layout->addWidget(but5);
    layout->addWidget(but6);
    layout->addWidget(but7);
    layout->addWidget(but8);
    layout->addWidget(but9);
    layout->setStretchFactor(lab,1);
    layout->setStretchFactor(but1,1);
    layout->setStretchFactor(but2,1);
    layout->setStretchFactor(but3,1);
    layout->setStretchFactor(but4,1);
    layout->setStretchFactor(but5,1);
    layout->setStretchFactor(but6,1);
    layout->setStretchFactor(but7,1);
    layout->setStretchFactor(but8,1);
    layout->setStretchFactor(but9,1);
    setLayout(layout);

    QObject::connect(but1,&QPushButton::clicked,[=]{
        Det_Sum *det_sum=new Det_Sum;
        det_sum->setAttribute(Qt::WA_DeleteOnClose);
        det_sum->show();
    });

    QObject::connect(but2,&QPushButton::clicked,[=]{
        Mat_Trans *mat_trans=new Mat_Trans;
        mat_trans->setAttribute(Qt::WA_DeleteOnClose);
        mat_trans->show();
    });

    QObject::connect(but3,&QPushButton::clicked,[=]{
        Mat_Add *mat_add=new Mat_Add;
        mat_add->setAttribute(Qt::WA_DeleteOnClose);
        mat_add->show();
    });

    QObject::connect(but4,&QPushButton::clicked,[=]{
        Mat_Scalar_Multi *mat_scalar_multi=new Mat_Scalar_Multi;
        mat_scalar_multi->setAttribute(Qt::WA_DeleteOnClose);
        mat_scalar_multi->show();
    });

    QObject::connect(but5,&QPushButton::clicked,[=]{
        Mat_Multi *mat_multi=new Mat_Multi;
        mat_multi->setAttribute(Qt::WA_DeleteOnClose);
        mat_multi->show();
    });

    QObject::connect(but6,&QPushButton::clicked,[=]{
        Mat_Adjoint *mat_adjoint=new Mat_Adjoint;
        mat_adjoint->setAttribute(Qt::WA_DeleteOnClose);
        mat_adjoint->show();
    });

    QObject::connect(but7,&QPushButton::clicked,[=]{
        Mat_Inverse *mat_inverse=new Mat_Inverse;
        mat_inverse->setAttribute(Qt::WA_DeleteOnClose);
        mat_inverse->show();
    });

    QObject::connect(but8,&QPushButton::clicked,[=]{
        Mat_Simp *mat_simp=new Mat_Simp;
        mat_simp->setAttribute(Qt::WA_DeleteOnClose);
        mat_simp->show();
    });

    QObject::connect(but9,&QPushButton::clicked,[=]{
        About about(this);
        about.exec();
    });
}
