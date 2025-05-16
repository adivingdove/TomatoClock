#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include<QSoundEffect>
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>
#include<QFile>
#include<QFileInfo>
#include<QDebug>

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();


signals:
    void signalBack();

    void minimized(bool minimized);

private slots:
    void on_exitButton_clicked();

    void on_rainButton_clicked();

    void on_forestButton_clicked();

    void on_minimizeButton_clicked();

    void on_volumeButton_clicked();

    void on_volumeSlider_valueChanged(int value);

    void on_selfdefinedButton_clicked();

    void on_selfButton_clicked();

    void paintEvent(QPaintEvent*);

    // void changeEvent(QEvent *event);

private:
    Ui::setting *ui;
    QSoundEffect *music=new QSoundEffect;  //设置音乐播放器

    bool musicstate1=0;   //默认状态下雨声音乐未播放
    bool musicstate2=0;   //默认状态下森林音乐未播放
    bool musicstate3=0;   //默认状态下自定义音乐未播放
    bool mutestate=0;   //默认状态下不静音

    QString fileName;

    //退出后返回父窗口
signals:
    void subClose();

private:
    void closeEvent(QCloseEvent *){//重写关闭按钮事件
        emit subClose();//发出关闭信号，父窗体接收信号后显示窗体
    }
};

#endif // SETTING_H
