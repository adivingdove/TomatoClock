#include "tomatoclock.h"
#include"setting.h"
#include "./ui_tomatoclock.h"
#include <QSettings>

tomatoClock::tomatoClock(QWidget *parent ,int minute,int restminute)
    : QWidget(parent),work_minute(minute),rest_minute(restminute)
    , ui(new Ui::tomatoClock)
{
    ui->setupUi(this);
    Opacity = 1; // 透明度设置
    state = 1;   // 暂停，恢复暂停
    tomato_num = 0; //番茄钟计数

    this->setWindowFlags(Qt::FramelessWindowHint);      //设置为无边框窗口
    //    this->setMinimumSize(100,50);                        //设置最小尺寸
    //    this->setMaximumSize(200,100);                      //设置最大尺寸
    this->setWindowOpacity(Opacity);                    //设置不透明度

    QIcon setPhoto(":/photos/setting.png");
    ui->settingButton->setIcon(setPhoto);
    QIcon exitPhoto(":/photos/cross.png");
    ui->exitButton->setIcon(exitPhoto);
    QIcon resetPhoto(":/photos/reset.png");
    ui->resetButton->setIcon(resetPhoto);

    timer = new QTimer;

    ui->Timer->setDigitCount(5);                    //设置显示位数为8位



    initTime();                                      //令LCD初始化
    timer->setInterval(1000);                        //设置定时器间隔为1000=1s

    //连接槽函数，将timer的timeout行为，连接到updateTime函数中
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    timer->start();  //启用定时器

    state=0;//默认暂停
    timer->stop();


}



tomatoClock::~tomatoClock()
{
    delete ui;
}

 //实现退出按钮
void tomatoClock::on_exitButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "提醒", "确定要放弃本次番茄钟吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)//选择是则关闭
    {

        this->close();
    }
    else//选择否不进行操作
    {

    }
}

void tomatoClock::mousePressEvent(QMouseEvent *e)  //鼠标单击事件
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();

    this->setWindowOpacity(Opacity);
    if (state == 1)
    {
        //暂停
        state = 0;
        /*this->setStyleSheet("background:#B5B5B5"); */   //设置暂停背景颜色
        Opacity = 0.2;
        timer->stop();
        this->setWindowOpacity(Opacity);                    //设置不透明度
    }
    else
    {//恢复
        state = 1;
        timer->start();
        this->setStyleSheet( current_color);          //恢复背景颜色
        Opacity = 1;
    }
    this->setWindowOpacity(Opacity);                    //设置不透明度
}

void tomatoClock::mouseMoveEvent(QMouseEvent *e)  //鼠标移动事件
{
    if(e->buttons()&Qt::LeftButton)
        move(e->pos()+pos()-clickPos); //父窗口的左上角+当前鼠标指针移动-初始单击时候鼠标指针的方向
}


//开始时set时间并显示
void tomatoClock::initTime()
{

    if(tomato_state==1)
    {
        time.setHMS(0,work_minute,work_sec); //时间复位 25min
        ui->Timer->display(time.toString("mm:ss"));
    }
    else
    {
        time.setHMS(0,rest_minute,rest_sec);//休息时间复位
        ui->Timer->display(time.toString("mm:ss"));
    }
}

//每一秒更新一次时间
void tomatoClock::updateTime()
{
    //每次更新时间，time减1
    time = time.addSecs(-1);
    ui->Timer->display(time.toString("mm:ss"));
    if (time.minute() == 0 && time.second()==0 && tomato_state==0)
    {
        //进行了一个周期获得一个番茄
        tomato_num++;

        //休息完毕，进入番茄钟
        tomato_state = 1;
        initTime();
        current_color = ":/photos/bg3.jpeg";
        this->setStyleSheet(current_color);    //进入番茄色
    }
    else if(time.minute() == 0 && time.second()==0 && tomato_state==1)
    {


        //将番茄数量加一
        QSettings settings("MyCompany", "MyApp");
        if (!settings.contains("tomatonum")) {
            settings.setValue("tomatonum",int(0));
            // 处理值的逻辑
        } else {
            // 键不存在的处理逻辑
        }
        int tomatonum = settings.value("tomatonum").toInt();
        tomatonum++;
        settings.setValue("tomatonum",tomatonum);
        //qDebug()<<settings.value("tomatonum");


        //纪录总时长
        if (!settings.contains("work_time")) {
            settings.setValue("work_time",int(0));
            // 处理值的逻辑
        } else {
            // 键不存在的处理逻辑
        }
        int work_time = settings.value("work_time").toInt();
        work_time += work_minute;
        settings.setValue("work_time",work_time);
        //qDebug()<<settings.value("work_time");


        //番茄钟完毕，进入休息时间
        tomato_state = 0;
        initTime();
        current_color = ":/photos/star.jpeg";
        this->setStyleSheet(current_color);    //进入休息色
    }
}

//时间重置
void tomatoClock::on_resetButton_clicked()
{
    // 创建一个确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认重置", "您确定要重置计时器吗？",
                                  QMessageBox::Yes|QMessageBox::No);

    // 如果用户确认重置
    if (reply == QMessageBox::Yes) {
        if(tomato_state == 1)
        {
            time.setHMS(0, work_minute, work_sec);
            ui->Timer->display(time.toString("mm:ss"));
        }
        else
        {
            time.setHMS(0, rest_minute, rest_sec);
            ui->Timer->display(time.toString("mm:ss"));
        }
    }
    // 如果用户取消重置，可以选择不执行任何操作或者给出相应提示
}



void tomatoClock::on_settingButton_clicked()
{
    if(tomato_state==0)//休息时进入设置界面暂停
    {
         // 连接退出信号与显示槽函数
        state=0;
        timer->stop();
        this->hide();//当前窗体隐藏
        setting *sub = new setting();//新建子窗体
        connect(sub,&setting::subClose,this,&QWidget::show);//关联子窗体关闭信号与父窗体显示事件
        sub->setAttribute(Qt::WA_DeleteOnClose);//设置子窗体属性：关闭即销毁
        sub->show();//显示子窗体
         }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "提醒", "现在是工作时间，确定要暂停并进入设置吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)//选择是则进入设置
        {
            state=0;
            timer->stop();
            // 连接退出信号与显示槽函数
            state=0;
            timer->stop();
            this->hide();//当前窗体隐藏
            setting *sub = new setting();//新建子窗体
            connect(sub,&setting::subClose,this,&QWidget::show);//关联子窗体关闭信号与父窗体显示事件
            sub->setAttribute(Qt::WA_DeleteOnClose);//设置子窗体属性：关闭即销毁
            sub->show();//显示子窗体
        }
        else//选择否不进行操作
        {

        }
    }
}

void tomatoClock::paintEvent(QPaintEvent*)
{
    if(tomato_state==1)  //工作钟
    {
        QPainter painter(this);

        QPixmap pixmap(":/photos/bg3.jpeg");
        painter.drawPixmap(this->rect(),pixmap);

    }else
    {
        QPainter painter(this);
        QPixmap pixmap(":/photos/star.jpeg");
        painter.drawPixmap(this->rect(),pixmap);
    }
}

