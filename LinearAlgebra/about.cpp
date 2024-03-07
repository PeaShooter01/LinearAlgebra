#include "about.h"
#include <QLabel>
#include <QVBoxLayout>

About::About(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("关于");
    setFixedSize(300,200);

    QLabel *title=new QLabel;
    title->setParent(this);
    title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    title->setText("线代神器v2.0");

    QLabel *lab=new QLabel;
    lab->setParent(this);
    lab->setAlignment(Qt::AlignTop);
    lab->setWordWrap(true);
    lab->setText("用于考试，后果自负。");

    QVBoxLayout *layout=new QVBoxLayout;
    layout->setParent(this);
    layout->setDirection(QHBoxLayout::TopToBottom);
    layout->addWidget(title);
    layout->setStretchFactor(title,1);
    layout->addWidget(lab);
    layout->setStretchFactor(lab,9);
    setLayout(layout);
}
