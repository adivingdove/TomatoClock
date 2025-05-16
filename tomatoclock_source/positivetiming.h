#ifndef POSITIVETIMING_H
#define POSITIVETIMING_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include"setting.h"
#include <QMessageBox>

namespace Ui {
class positiveTiming;
}

class positiveTiming : public QWidget
{
    Q_OBJECT

public:
    explicit positiveTiming(QWidget *parent = nullptr);
    ~positiveTiming();

protected:
    //     声明一些函数
    void mousePressEvent(QMouseEvent *e); //鼠标单击事件
    void mouseMoveEvent(QMouseEvent *e); // 鼠标单击拖动窗口

private slots:
    void initTime(); //初始化时间
    void updateTime(); //更新时间
    void on_resetButton_clicked();
    void on_settingButton_2_clicked();
    void on_exitButton_2_clicked();
    void paintEvent(QPaintEvent*);
    // void handleMinimizedEvent(bool minimized);

private:
    float Opacity; //透明度控制

    int state; //用于暂停和恢复暂停
    int tomato_state=1; //番茄钟计数,用于表示休息与工作两种状态,初始为1（工作）
    int tomato_num;//番茄数，用户每完成一次工作则番茄数加1

    QString current_color;
    QPoint clickPos;
    Ui::positiveTiming *ui;

    QTimer *timer;//时间显示器
    QTime time;//时间



};

#endif // POSITIVETIMING_H
