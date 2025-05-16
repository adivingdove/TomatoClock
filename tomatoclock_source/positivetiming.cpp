#include "positivetiming.h"
#include "ui_positivetiming.h"
#include<QPainter>

positiveTiming::positiveTiming(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::positiveTiming)
{
    ui->setupUi(this);
    Opacity = 1; // 透明度设置
    state = 1;   // 暂停，恢复暂停
    /*current_color = "background:#CD9B9B"; //当前背景色设置
    this->setStyleSheet(current_color);*/                 //设置背景颜色
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置为无边框窗口
    //    this->setMinimumSize(100,50);                        //设置最小尺寸
    //    this->setMaximumSize(200,100);                      //设置最大尺寸
    this->setWindowOpacity(Opacity);                    //设置不透明度



    timer = new QTimer;

    ui->Timer->setDigitCount(5);                    //设置显示位数为8位



    initTime();                                      //令LCD初始化
    timer->setInterval(1000);                        //设置定时器间隔为1000=1s

    //连接槽函数，将timer的timeout行为，连接到updateTime函数中
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    timer->start();  //启用定时器

    state=0;//默认暂停
    timer->stop();

    QIcon con(":/photos/setting.png");
    ui->settingButton_2->setIcon(con);

    QIcon con2(":/photos/reset.png");
    ui->resetButton->setIcon(con2);

    QIcon con3(":/photos/cross.png");
    ui->exitButton_2->setIcon(con3);



}

positiveTiming::~positiveTiming()
{
    delete ui;
}


void positiveTiming::mousePressEvent(QMouseEvent *e)  //鼠标单击事件
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();

    this->setWindowOpacity(Opacity);
    if (state == 1)
    {
        //暂停
        state = 0;
        this->setStyleSheet("background:#B5B5B5");    //设置暂停背景颜色
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

void positiveTiming::mouseMoveEvent(QMouseEvent *e)  //鼠标移动事件
{
    if(e->buttons()&Qt::LeftButton)
        move(e->pos()+pos()-clickPos); //父窗口的左上角+当前鼠标指针移动-初始单击时候鼠标指针的方向
}


//开始时set时间并显示
void positiveTiming::initTime()
{


        time.setHMS(0,0,0); //时间复位
        ui->Timer->display(time.toString("mm:ss"));

}

//每一秒更新一次时间
void positiveTiming::updateTime()
{
    //每次更新时间，time减1
    time = time.addSecs(1);
    ui->Timer->display(time.toString("mm:ss"));

}

//时间重置
void positiveTiming::on_resetButton_clicked()
{

    // 创建一个确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认重置", "您确定要重置计时器吗？",
                                  QMessageBox::Yes|QMessageBox::No);

    // 如果用户确认重置
    if (reply == QMessageBox::Yes) {

            time.setHMS(0, 0, 0);
            ui->Timer->display(time.toString("mm:ss"));
        }


    // 如果用户取消重置，可以选择不执行任何操作或者给出相应提示


}



void positiveTiming::on_settingButton_2_clicked()
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


void positiveTiming::on_exitButton_2_clicked()
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

void positiveTiming::paintEvent(QPaintEvent*){
    QPainter painter(this);

    QPixmap pixmap(":/photos/bg3.jpeg");
    painter.drawPixmap(this->rect(),pixmap);
}

// //槽函数
// void positiveTiming::handleMinimizedEvent(bool minimized)
// {
//     if(minimized)
//     {
//         this->show();
//         qDebug()<<minimized;
//     }
// }
