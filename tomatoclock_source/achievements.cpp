#include "ui_achievements.h"
#include "achievements.h"
#include <QLabel>
#include <QMessageBox>
#include <QSettings>
#include <QPainter>
#include <QPaintEvent>


achievements::achievements(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::achievements)
{
    //为传参暂时放一个变量
    int tomato_num = 0;
    QSettings settings("MyCompany", "MyApp");
    if (!settings.contains("tomatonum")) {
        settings.setValue("tomatonum",int(0));
        // 处理值的逻辑
    } else {
        // 键不存在的处理逻辑
    }
    tomato_num = settings.value("tomatonum").toInt();

    ui->setupUi(this);
    //可以拖动滚动条
    ui->scrollArea->setWidgetResizable(false);
    //横竖滚动条都可以实现
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //设置主界面
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setGeometry(0, 60, 451, 1000); //实际界面参数
    ui->scrollArea->setStyleSheet("background:transparent");


    first = false;
    second = false;
    third = false;
    forth = false;
    fifth = false;
    getAchievements(tomato_num);

}

achievements::~achievements()
{
    delete ui;
}

//判断番茄数
void achievements::getAchievements(int tomato_num)
{
    QSettings settings("MyCompany", "MyApp");
    if (tomato_num >= 1 && tomato_num <= 10) {
        first = true;
        ui->firstButton->setStyleSheet("QPushButton{border-image:url(:/photos/01.png)}");
        settings.setValue("medal_num",1);
    } else if (tomato_num > 10 && tomato_num <= 25) {
        first = true;
        second = true;
        ui->firstButton->setStyleSheet("QPushButton{border-image:url(:/photos/01.png)}");
        ui->secondButton->setStyleSheet("QPushButton{border-image:url(:/photos/02.png)}");
        settings.setValue("medal_num",2);
    } else if (tomato_num > 25 && tomato_num <= 50) {
        first = true;
        second = true;
        third = true;
        ui->firstButton->setStyleSheet("QPushButton{border-image:url(:/photos/01.png)}");
        ui->secondButton->setStyleSheet("QPushButton{border-image:url(:/photos/02.png)}");
        ui->thirdButton->setStyleSheet("QPushButton{border-image:url(:/photos/03.png)}");
        settings.setValue("medal_num",3);
    } else if (tomato_num > 50 & tomato_num <= 75) {
        first = true;
        second = true;
        third = true;
        forth = true;
        ui->firstButton->setStyleSheet("QPushButton{border-image:url(:/photos/01.png)}");
        ui->secondButton->setStyleSheet("QPushButton{border-image:url(:/photos/02.png)}");
        ui->thirdButton->setStyleSheet("QPushButton{border-image:url(:/photos/03.png)}");
        ui->forthButton->setStyleSheet("QPushButton{border-image:url(:/photos/04.png)}");
        settings.setValue("medal_num",4);
    } else if (tomato_num > 75) {
        first = true;
        second = true;
        third = true;
        forth = true;
        fifth = true;
        ui->firstButton->setStyleSheet("QPushButton{border-image:url(:/photos/01.png)}");
        ui->secondButton->setStyleSheet("QPushButton{border-image:url(:/photos/02.png)}");
        ui->thirdButton->setStyleSheet("QPushButton{border-image:url(:/photos/03.png)}");
        ui->forthButton->setStyleSheet("QPushButton{border-image:url(:/photos/04.png)}");
        ui->fifthButton->setStyleSheet("QPushButton{border-image:url(:/photos/05.png)}");
        settings.setValue("medal_num",5);
    } else {
        first = false;
        second = false;
        third = false;
        forth = false;
        fifth = false;
    }
}

void achievements::on_firstButton_clicked()
{
    if (first == true) {
        QMessageBox msg;
        msg.setWindowTitle("初出茅庐");
        msg.setText(
            "恭喜您完成了您的第一个番茄钟！这是您成就之旅的第一步，前方还有更多的挑战等待着您！");
        msg.exec();
    } else {
        QMessageBox msg;
        msg.setWindowTitle("初出茅庐");
        msg.setText("您尚未获得该成就，请继续努力！");
        msg.exec();
    }
}

void achievements::on_secondButton_clicked()
{
    if (second) {
        QMessageBox msg;
        msg.setWindowTitle("坚持不懈");
        msg.setText("您已经获得了坚持不懈的成就！每一次专注工作都让您离目标更近一步，坚持下去，成功"
                    "就在眼前！");
        msg.exec();
    } else {
        QMessageBox msg;
        msg.setWindowTitle("坚持不懈");
        msg.setText("您尚未获得该成就，请继续努力！");
        msg.exec();
    }
}

void achievements::on_thirdButton_clicked()
{
    if (third) {
        QMessageBox msg;
        msg.setWindowTitle("专注大师");
        msg.setText("作为专注大师，您展现了出色的工作效率和专注力！您的每一个番茄钟都是对自己的认可"
                    "，继续保持，向更高峰迈进！");
        msg.exec();
    } else {
        QMessageBox msg;
        msg.setWindowTitle("专注大师");
        msg.setText("您尚未获得该成就，请继续努力！");
        msg.exec();
    }
}

void achievements::on_forthButton_clicked()
{
    if (forth) {
        QMessageBox msg;
        msg.setWindowTitle("高效能手");
        msg.setText("您已经成为高效能手！您的时间管理和工作效率令人钦佩。继续保持稳健的步伐，您将收"
                    "获更多成就！");
        msg.exec();
    } else {
        QMessageBox msg;
        msg.setWindowTitle("高效能手");
        msg.setText("您尚未获得该成就，请继续努力！");
        msg.exec();
    }
}

void achievements::on_fifthButton_clicked()
{
    if (fifth) {
        QMessageBox msg;
        msg.setWindowTitle("番茄之王");
        msg.setText("恭喜您成为番茄之王！您的专注力和工作效率超越了常人，让成就之光照亮您前行的道路"
                    "，创造更辉煌的明天！");
        msg.exec();
    } else {
        QMessageBox msg;
        msg.setWindowTitle("番茄之王");
        msg.setText("您尚未获得该成就，请继续努力！");
        msg.exec();
    }
}

void achievements::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pixmap(":/photos/backgreen.jpeg");
    painter.drawPixmap(this->rect(),pixmap);
}
