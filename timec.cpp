#include <QtWidgets>
#include "timec.h"
TimeC::TimeC(QWidget *p):QWidget(p)
{
    QFont f("Times",10,QFont::Bold);

    state=new QLabel("Введите время остановки таймера (в формате чч.мм.сс)");
    limi=new QLineEdit;
    limi->hide();
    state->hide();

    t=new QTimer;

    chb=new QCheckBox;
    chb->setCheckable(true);
    chb->setChecked(false);

    pc=new ProgressCircle;
    pc->setInnerRadius(0.8);
    pc->setOuterRadius(1);
    pc->setMinimumSize(100,100);
    pc->setMaximum(10000);

    QLabel *tim=new QLabel("Время");
    tim->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    tim->setLineWidth(1);
    tim->setFont(f);

    QLabel *summa=new QLabel("Стоимость услуги");
    summa->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    summa->setLineWidth(1);
    summa->setFont(f);

    QLabel *pay=new QLabel("Введите стоимость (1 ч.)");
    pay->setFont(f);

    QLabel *limit=new QLabel("Устновить ограничение по времени");
    limit->setFont(f);

    QPushButton *b1=new QPushButton("Start");
    QPushButton *b2=new QPushButton("End");
    QPushButton *b3=new QPushButton("Reset");

    QLineEdit *line=new QLineEdit;
    QRegExp rx("-?\\d+");
    QValidator *validator = new QRegExpValidator(rx);
    line->setValidator(validator);

    l=new QLabel("00:00:00");
    l->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    l->setLineWidth(1);

    l2=new QLabel("0 руб");
    l2->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    l2->setLineWidth(1);

    connect(b1,QPushButton::clicked,[this](){t->start(1000);});
    connect(t,SIGNAL(timeout()),this,SLOT(tm()));
    connect(this,TimeC::Clocking,[this](){Displ(sec);});
    connect(b2,SIGNAL(clicked()),t,SLOT(stop()));
    connect(b3,SIGNAL(clicked()),this,SLOT(Treset()));
    connect(this,TimeC::Clocking,[this](){Money(sec);});
    connect(line,SIGNAL(textChanged(QString)),this,SLOT(setPrice(QString)));
    connect(this,SIGNAL(Clocking(int)),pc,SLOT(setValue(int)));
    connect(this,TimeC::Clocking,[this](){pc->setSt(l->text()+"\n\n"+l2->text());});
    connect(limi,&QLineEdit::textChanged,[this](QString s){timelimit=s;});
    connect(t,&QTimer::timeout,[this](){if(timelimit==l->text())t->stop();});
    connect(chb,&QCheckBox::stateChanged,[this](int x){if(x==2)showH();});
    connect(chb,&QCheckBox::stateChanged,[this](int x){if(x==0)hideH();});
    connect(t,SIGNAL(timeout()),this,SLOT(messag()));


    QVBoxLayout *v1=new QVBoxLayout;
    v1->setSpacing(0);
    v1->addWidget(tim);
    v1->addWidget(l);
    v1->addWidget(summa);
    v1->addWidget(l2);

    QVBoxLayout *v2=new QVBoxLayout;
    v2->setSpacing(10);
    v2->addWidget(b1);
    v2->addWidget(b2);
    v2->addWidget(b3);

    v2->addWidget(pay);
    v2->setAlignment(pay,Qt::AlignCenter);
    v2->setStretch(3,200);
    v2->addWidget(line);

    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(pc);

    QHBoxLayout *h=new QHBoxLayout;
    h->addLayout(v1);
    h->addLayout(v3);
    h->addLayout(v2);

    QHBoxLayout *li=new QHBoxLayout;
    li->addWidget(limit);
    li->addWidget(chb);

    QVBoxLayout *vv=new QVBoxLayout;
    vv->addLayout(h);
    vv->setAlignment(h,Qt::AlignCenter);
    vv->addLayout(li);
    vv->setAlignment(li,Qt::AlignCenter);


    QHBoxLayout *spesh=new QHBoxLayout;
    spesh->addWidget(state);
    spesh->addWidget(limi);
    vv->addLayout(spesh);


    setLayout(vv);


    /*   setMaximumHeight(150);
    setMaximumWidth(500);*/
}
void TimeC::Displ(int x){
    QTime t=toHMS(x);
    l->setText(t.toString());
}
void TimeC::Money(int x){
    money=x*(price/3600.0);
    l2->setText(QString::number(money)+" руб");
}
QTime TimeC::toHMS(int s){
    int hour = s / 3600;
    int min = (s - hour * 3600) / 60;
    int  sec = s - hour * 3600 - min * 60;
    QTime tt(hour,min,sec);
    return tt;
}
void TimeC::tm(){
    ++sec;
    emit Clocking(sec);
}
void TimeC::setPrice(QString s){
    price=s.toDouble();
}
void TimeC::Treset(){
    pc->setValue(0);
    sec=0;
    money=0;
    t->stop();
    l->setText("00:00:00");
    l2->setText("0 руб.");
    pc->setSt("00:00:00\n\n0 руб");
}
void TimeC::showH(){
    limi->show();
    state->show();
}
void TimeC::hideH(){
    limi->hide();
    state->hide();
    limi->setText("");
}
void TimeC::messag(){
    if(!t->isActive() && chb->isChecked()){
        QMessageBox::information(0,"Info","Время истекло");
    }
}

