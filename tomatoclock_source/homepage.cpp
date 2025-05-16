#include "homepage.h"
#include "ui_homepage.h"
#include<QFontDatabase>

homePage::homePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::homePage)
{
    ui->setupUi(this);

    //adding上放图片
    QIcon con1(":/photos/list.png");
    ui->adding->setIcon(con1);

    //putton上放图片
    QIcon con2(":/photos/setting.png");
    ui->settingPutton->setIcon(con2);

    //initialputton上放图片
    QIcon con3(":/photos/tomato.png");
    ui->initialSettingPutton_2->setIcon(con3);

    //positivetiming上放图片
    QIcon con4(":/photos/positivetiming.png");
    ui->positiveTiming->setIcon(con4);

    //设定LCDnumber
    ui->currentTime->setDigitCount(8);
    ui->currentTime->setMode(QLCDNumber::Dec);
    ui->currentTime->setSegmentStyle(QLCDNumber::Flat);
    ui->currentTime->setStyleSheet("color:white");

    //设定当前时间
    timer=new QTimer(this);
    timer->setInterval(1000);   //定时刷新
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    timer->start();
    ui->currentTime->setSegmentStyle(QLCDNumber::Filled);

    //鼠标悬停标签
    ui->positiveTiming->setToolTip("正计时");
    ui->positiveTiming->setStyleSheet("background: transparent;QToolTip{border:1px solid rgb(118,118,118);background-color:#ffffff;color:#484848;font-size:12px}");
    ui->initialSettingPutton_2->setToolTip("开始");
    ui->initialSettingPutton_2->setStyleSheet("background: transparent;QToolTip{border:1px solid rgb(118,118,118);background-color:#ffffff;color:#484848;font-size:12px}background: transparent;QToolTip{border:1px solid rgb(118,118,118);background-color:#ffffff;color:#484848;font-size:12px}");
    ui->settingPutton->setToolTip("设置");
    ui->settingPutton->setStyleSheet("background: transparent;QToolTip{border:1px solid rgb(118,118,118);background-color:#ffffff;color:#484848;font-size:12px}");
    ui->adding->setToolTip("自定义");
    ui->adding->setStyleSheet("background: transparent;QToolTip{border:1px solid rgb(118,118,118);background-color:#ffffff;color:#484848;font-size:12px}");

    //文案随机生成
    // QTimer *timer=new QTimer(this);
    // timer->start(1*1000);
    // timer->start();
    // connect(timer,SIGNAL(timeout),this,SLOT(changeWords()));
    changeWords();

}



homePage::~homePage()
{
    delete ui;
}


void homePage::on_positiveTiming_clicked()
{
    positiveTiming *p = new positiveTiming;
    //this->hide();
    p->show();
}


void homePage::on_initialSettingPutton_2_clicked()
{
    tomatoClock *c = new tomatoClock;
    //this->hide();
    c->show();
}




void homePage::on_adding_clicked()
{
    selfdefined *s = new selfdefined;
    //this->hide();
    s->show();
}


void homePage::on_settingPutton_clicked()
{
    settingPage *s = new settingPage;
    //this->hide();
    s->show();
}

void homePage::timeOut(){
    QTime currentTime=QTime::currentTime();

    ui->currentTime->display(currentTime.toString("HH:mm:ss"));
}


//添加背景图片
void homePage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QPixmap pixmap(":/photos/background.jpeg");
    painter.drawPixmap(this->rect(),pixmap);
}

//文案切换
void homePage::changeWords()
{
    //标签生成不同文案,用随机数实现
    switch(QRandomGenerator::global()->bounded(10)){
    case 0:
        break;
    case 1:
        ui->label_2->setText("“以春为饵，去垂钓新生”");
        break;
    case 2:
        ui->label_2->setText("“万物与我都是自由诗”");
        break;
    case 3:
        ui->label_2->setText("“人生岁月不哀戚，还有梦境和黎明”");
        break;
    case 4:
        ui->label_2->setText("“靡不有初，鲜克有终”");
        break;
    case 5:
        ui->label_2->setText("“纵有疾风起，人生不言弃”");
        break;
    case 6:
        ui->label_2->setText("“我非生而知之者，好古，敏以求之者也”");
        break;
    case 7:
        ui->label_2->setText("“追逐影子的人，自己就是影子”");
        break;
    case 8:
        ui->label_2->setText("“在隆冬，我终于知道，我身上有个不可战胜的夏天”");
        break;
    case 9:
        ui->label_2->setText("“只要想起一生中后悔的事，梅花便落满了南山”");
        break;
    case 10:
        ui->label_2->setText("“你当像鸟飞往你的山”");
        break;
    }
}

