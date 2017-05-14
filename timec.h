#pragma once
#include <QtWidgets>
#include <ProgressCircle.h>
class TimeC: public QWidget{
    Q_OBJECT
public:
    explicit TimeC(QWidget *p=0);
    TimeC(const TimeC &t)=delete;
    TimeC& operator=(const TimeC &t)=delete;

    virtual ~TimeC(){}

    void Displ(int x);

    virtual void Money(int x);

    QTime toHMS(int s);

signals:
    void Clocking(int);
public slots:
    void tm();
    void setPrice(QString s);
    void Treset();
    void showH();
    void hideH();
    void messag();

private:
    QCheckBox *chb;
    ProgressCircle *pc;
    QTimer *t;
    QLabel *l,*l2;
    QLabel *state;
    QLineEdit *limi;
    int sec=0;
    double price=0.0;
    double money=0.0;
    QString timelimit;

};

