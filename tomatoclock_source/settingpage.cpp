#include "settingpage.h"
#include "ui_settingpage.h"
#include "daiban.h"
#include "personal_details.h"
#include "achievements.h"

settingPage::settingPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::settingPage)
{
    ui->setupUi(this);

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/photos/backgreen.jpeg").scaled(this->size(), Qt::KeepAspectRatio));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    backgroundLabel->setAlignment(Qt::AlignCenter);
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower();   //显示在最下层
}

settingPage::~settingPage()
{
    delete ui;
}

void settingPage::on_pushButton_clicked()
{
    daiban *s = new daiban;
    //this->hide();
    s->show();
}


void settingPage::on_pushButton_3_clicked()
{
    personal_details *p=new personal_details;
    p->show();
}


void settingPage::on_pushButton_2_clicked()
{
    achievements *a=new achievements;
    a->show();
}

