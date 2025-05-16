#ifndef TOMATOCLOCK_H
#define TOMATOCLOCK_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include<QPainter>
#include<QRect>
#include<QPen>

QT_BEGIN_NAMESPACE
namespace Ui { class tomatoClock; }
QT_END_NAMESPACE

class tomatoClock : public QWidget
{
    Q_OBJECT

public:
    //tomatoClock(QWidget *parent = nullptr);
    tomatoClock(QWidget *parent = nullptr,int minute=25,int restminute=5);
    ~tomatoClock();

protected:
    //     声明一些函数
    void mousePressEvent(QMouseEvent *e); //鼠标单击事件
    void mouseMoveEvent(QMouseEvent *e); // 鼠标单击拖动窗口

private slots:


    void initTime(); //初始化时间
    void updateTime(); //更新时间

    void on_exitButton_clicked();

    void on_resetButton_clicked();

    void on_settingButton_clicked();

    void paintEvent(QPaintEvent*);

private:
    float Opacity; //透明度控制

    int state; //用于暂停和恢复暂停
    int tomato_state=1; //番茄钟计数,用于表示休息与工作两种状态,初始为1（工作）
    int tomato_num;//番茄数，用户每完成一次工作则番茄数加1

    QString current_color;
    QPoint clickPos;
    Ui::tomatoClock *ui;

    QTimer *timer;//时间显示器
    QTime time;//时间

    //自定义时间
    int work_minute=25;
    int work_sec=0;
    int rest_minute=5;
    int rest_sec=0;
};
#endif // TOMATOCLOCK_H
