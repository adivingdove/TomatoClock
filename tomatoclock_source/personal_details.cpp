#include "personal_details.h"
#include "ui_personal_details.h"
#include <QLabel>
#include <QSettings>


personal_details::personal_details(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::personal_details)
{
    ui->setupUi(this);
    //this->setWindowTitle("tomato");

    // 设置背景图片并调整大小以适应QLabel
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/photos/OIP-C2.jpg").scaled(this->size(), Qt::KeepAspectRatio));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    backgroundLabel->setAlignment(Qt::AlignCenter);
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower();   //显示在最下层

    QSettings settings("MyCompany", "MyApp");
    if (!settings.contains("tomatonum")) {
        settings.setValue("tomatonum",int(0));
        // 处理值的逻辑
    } else {
        // 键不存在的处理逻辑
    }
    if (!settings.contains("work_time")) {
        settings.setValue("work_time",int(0));
        // 处理值的逻辑
    } else {
        // 键不存在的处理逻辑
    }
    if (!settings.contains("medal_num")) {
        settings.setValue("medal_num",int(0));
        // 处理值的逻辑
    } else {
        // 键不存在的处理逻辑
    }
    ui->tomato_num->setText(settings.value("tomatonum").toString());
    ui->work_num->setText(settings.value("work_time").toString());
    ui->clock_num->setText(settings.value("medal_num").toString());
}

personal_details::~personal_details()
{
    delete ui;
}
