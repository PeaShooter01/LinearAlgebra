#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QString>

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);
};

#endif // ABOUT_H
