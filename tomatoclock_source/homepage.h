#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QProcess>
#include <QIcon>
#include <tomatoclock.h>
#include <settingpage.h>
#include <positivetiming.h>
//#include <sql.h>
#include <selfdefined.h>
#include<QString>
#include<QStringList>
#include<QTime>
#include<QTimer>
#include<QToolTip>
#include<QModelIndex>
#include<QPainter>
#include<QFontDatabase>
#include<QRandomGenerator>

namespace Ui {
class homePage;
}

class homePage : public QWidget
{
    Q_OBJECT

public:
    explicit homePage(QWidget *parent = nullptr);
    ~homePage();




private slots:
    void timeOut();

    void on_positiveTiming_clicked();

    void on_initialSettingPutton_2_clicked();

    void on_adding_clicked();

    void on_settingPutton_clicked();

    void paintEvent(QPaintEvent*);

    void changeWords();

private:
    Ui::homePage *ui;
    QTimer *timer;
};

#endif // HOMEPAGE_H
