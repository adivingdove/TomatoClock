#include "setting.h"
#include "ui_setting.h"
#include <QPainter>



setting::setting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::setting)
{
    ui->setupUi(this);
    QIcon exit(":/photos/cross.png");
    ui->exitButton->setIcon(exit);
    QIcon setPhoto(":/photos/minimize.png");
    ui->minimizeButton->setIcon(setPhoto);
    QIcon speaker(":/photos/speaker.png");
    ui->volumeButton->setIcon(speaker);
    QIcon rain(":/photos/rain.png");
    ui->rainButton->setIcon(rain);
    QIcon forest(":/photos/forest.png");
    ui->forestButton->setIcon(forest);
    QIcon file(":/photos/file.png");
    ui->selfButton->setIcon(file);

    music->stop();  //播放器默认为关闭


    //对slider的基础设置
    ui->volumeSlider->setTracking(true);
    ui->volumeSlider->setMinimum(0);  //设置slider最低值
    ui->volumeSlider->setMaximum(100);  //设置slider最高值
    ui->volumeSlider->setValue(0);  //设置slider初始值

    this->setWindowFlags(Qt::FramelessWindowHint);  //无边框设置，防止播放器重复播放


    //关联返回按钮点击事件与窗体关闭事件
    connect(ui->exitButton,&QPushButton::clicked,this,&setting::close);

}

setting::~setting()
{
    delete ui;
}

void setting::on_exitButton_clicked()
{

    emit signalBack();
    this->hide();
    music->stop();
}


void setting::on_rainButton_clicked()
{
    if(musicstate1==false){

        musicstate1=true;   //音乐状态为开启

        //开启按钮全部重置
        ui->forestButton->setText("开启");
        ui->selfButton->setText("开启");
        ui->volumeSlider->setValue(50);     //设定初始音量

        music->setSource(QUrl::fromLocalFile(":/music/rain.wav"));
        music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
        music->setVolume(ui->volumeSlider->value()*0.01f);  //设置音量,在0到1之间
        music->play();

        ui->rainButton->setText("暂停");
    }
    else
    {
        music->stop();    //暂停播放器
        ui->rainButton->setText("开启");    //重置文字
        musicstate1=false;    //重置音乐状态
    }
}


void setting::on_forestButton_clicked()
{
    if(musicstate2==false){

        musicstate2=true;   //重置音乐状态

        //开启按钮全部重置
        ui->rainButton->setText("开启");
        ui->selfButton->setText("开启");
        ui->volumeSlider->setValue(50);     //设定初始音量

        music->setSource(QUrl::fromLocalFile(":/music/forest.wav"));    //添加音乐资源
        music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
        music->setVolume(ui->volumeSlider->value()*0.01f);  //设置音量在0-1之间
        music->play();

        ui->forestButton->setText("暂停");
    }
    else
    {
        musicstate2=false;  //重置音乐状态

        music->stop();  //暂停播放器
        ui->forestButton->setText("开启");  //重置文字

    }
}

void setting::on_selfButton_clicked()
{
    if(musicstate3==false)
    {

        musicstate3=true;   //重置音乐状态

        //开启按钮全部重置
        ui->rainButton->setText("开启");
        ui->forestButton->setText("开启");
        ui->volumeSlider->setValue(50);     //设定初始音量

        music->setSource(QUrl::fromLocalFile(fileName));  //添加音乐资源
        music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
        // music->setVolume(ui->volumeSlider->value()*0.01f);  //设置音量在0-1之间
        music->play();
        if(!fileName.isEmpty())
        {
            ui->selfButton->setText("暂停");
        }
        else
        {
            QMessageBox::warning(this,"警告","请导入文件");
        }

    }
    else
    {
        musicstate3=false;  //重置音乐状态

        music->stop();  //暂停播放器
        ui->selfButton->setText("开启");  //重置文字

    }
}


void setting::on_minimizeButton_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}


void setting::on_volumeButton_clicked()
{
    //实现静音和不静音的切换
    if(mutestate==0){
        mutestate=1;
        music->setMuted(1);

        qDebug()<<mutestate;

        ui->volumeSlider->setValue(0);  //改变slider

        QIcon mute(":/photos/mute.png");    //图标改变
        ui->volumeButton->setIcon(mute);
    }
    else
    {
        mutestate=0;
        music->setMuted(0);

        qDebug()<<mutestate;

        QIcon speaker(":/photos/speaker.png");  //图标改变
        ui->volumeButton->setIcon(speaker);
    }
}





void setting::on_volumeSlider_valueChanged(int value)
{
    music->setVolume(value*0.01f);
    if(value==0){
        music->setMuted(1);     //播放器静音
        mutestate=1;    //设置静音状态

        QIcon mute(":/photos/mute.png");    //图标改变
        ui->volumeButton->setIcon(mute);
    }else{
        music->setMuted(0);     //播放器不静音
        mutestate=0;        //设置不静音状态

        QIcon speaker(":/photos/speaker.png");      //图标改变
        ui->volumeButton->setIcon(speaker);


    }
}



void setting::on_selfdefinedButton_clicked()
{
    //文件弹窗

    fileName=QFileDialog::getOpenFileName(this,"选择一个文件",
                                 QCoreApplication::applicationFilePath(),  //自动选择程序所在文件夹
                                                    "音频文件(*.wav);;wav文件(*.wav)");
    if(fileName.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一个文件");
    }
    else {
        //qDebug()<<fileName;

        ui->volumeSlider->setValue(50);     //设定初始音量

        //添加本地音乐资源并播放
        music->setSource(QUrl::fromLocalFile(fileName));
        music->setLoopCount(QSoundEffect::Infinite);
        music->setVolume(ui->volumeSlider->value()*0.01f);  //设置音量在0-1之间
        music->play();

        QFileInfo fileInfo(fileName);   //获取文件名
        QString filename_without_suffix = fileInfo.baseName(); //不包含后缀的文件名

        //改变开启图标，全部初始化
        ui->selfButton->setText("暂停");
        ui->rainButton->setText("开启");
        ui->forestButton->setText("开启");
        musicstate3=1;

        //提示
        QMessageBox::information(this,"提示","添加成功");
        ui->selfdefinedButton->setText(filename_without_suffix);       //改变按钮名称
    }



}


void setting::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QPixmap pixmap(":/photos/bg2.png");
    painter.drawPixmap(this->rect(),pixmap);
}

// void setting::changeEvent(QEvent *event)
// {
//     if(event->type() == QEvent::WindowStateChange)
// {
//         if(event->type()==Qt::WindowMinimized)
//         {
//             emit minimized(true);
//         }
// }
// }
