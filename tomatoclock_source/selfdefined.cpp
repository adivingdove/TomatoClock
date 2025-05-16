#include "selfdefined.h"
#include "ui_selfdefined.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QSpinBox>
#include "tomatoclock.h"
selfdefined::selfdefined(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selfdefined)
{

    ui->setupUi(this);
    // 连接按钮点击事件
    connect(ui->btn1, &QPushButton::clicked, this, &selfdefined::on_btn1_clicked);
    connect(ui->btn2, &QPushButton::clicked, this, &selfdefined::on_btn2_clicked);
    connect(ui->btn3, &QPushButton::clicked, this, &selfdefined::on_btn3_clicked);

    // 加载数据
    loadData(ui->spinBox1,ui->spinBox2,ui->spinBox3,
             ui->spinBox1_2,ui->spinBox2_2,ui->spinBox3_2,
             ui->lineEdit,ui->lineEdit_2,ui->lineEdit_3);
}

selfdefined::~selfdefined()
{
    delete ui;
}

void selfdefined::on_btn1_clicked()
{
    QString newData1 = ui->spinBox1->text();
    QString newData1_2 = ui->spinBox1_2->text();
    QString newedit1 = ui->lineEdit->text();

    saveData("data1", newData1);
    saveData("data1_2", newData1_2);
    saveData("edit1", newedit1);

    ui->spinBox1->setValue(newData1.toInt());
    ui->spinBox1_2->setValue(newData1_2.toInt());
    ui->lineEdit->setText(newedit1);
}


void selfdefined::on_btn2_clicked()
{
    QString newData2 = ui->spinBox2->text();
    QString newData2_2 = ui->spinBox2_2->text();
    QString newedit2 = ui->lineEdit_2->text();

    saveData("data2", newData2);
    saveData("data2_2", newData2_2);
    saveData("edit2", newedit2);

    ui->spinBox2->setValue(newData2.toInt());
    ui->spinBox2_2->setValue(newData2_2.toInt());
    ui->lineEdit_2->setText(newedit2);
}


void selfdefined::on_btn3_clicked()
{
    QString newData3 = ui->spinBox3->text();
    QString newData3_2 = ui->spinBox3_2->text();
    QString newedit3 = ui->lineEdit_3->text();

    saveData("data3", newData3);
    saveData("data3_2", newData3_2);
    saveData("edit3", newedit3);

    ui->spinBox3->setValue(newData3.toInt());
    ui->spinBox3_2->setValue(newData3_2.toInt());
    ui->lineEdit_3->setText(newedit3);
}


void selfdefined::on_start1_clicked()
{
    this->close();
    QSettings settings("MyCompany", "MyApp");
    tomatoClock *t = new tomatoClock( nullptr,settings.value("data1").toInt(),settings.value("data1_2").toInt());
    t->show();
}


void selfdefined::on_start2_clicked()
{
    this->close();
    QSettings settings("MyCompany", "MyApp");
    tomatoClock *t = new tomatoClock( nullptr,settings.value("data2").toInt(),settings.value("data2_2").toInt());
    t->show();
}


void selfdefined::on_start3_clicked()
{
    this->close();
    QSettings settings("MyCompany", "MyApp");
    tomatoClock *t = new tomatoClock( nullptr,settings.value("data3").toInt(),settings.value("data3_2").toInt());
    t->show();
}

void selfdefined::saveData(const QString &key, const QString &value)
{
    QSettings settings("MyCompany", "MyApp");
    settings.setValue(key, value);
}


void selfdefined::loadData(QSpinBox *spinBox1,QSpinBox *spinBox2,QSpinBox *spinBox3,
                      QSpinBox *spinBox1_2,QSpinBox *spinBox2_2,QSpinBox *spinBox3_2,
                      QLineEdit *lineEdit1,QLineEdit *lineEdit2,QLineEdit *lineEdit3)
{
    QSettings settings("MyCompany", "MyApp");
    QString data1 = settings.value("data1").toString();
    QString data2 = settings.value("data2").toString();
    QString data3 = settings.value("data3").toString();

    QString data1_2 = settings.value("data1_2").toString();
    QString data2_2 = settings.value("data2_2").toString();
    QString data3_2 = settings.value("data3_2").toString();

    QString edit1 = settings.value("edit1").toString();
    QString edit2 = settings.value("edit2").toString();
    QString edit3 = settings.value("edit3").toString();

    spinBox1->setValue(data1.toInt());
    spinBox2->setValue(data2.toInt());
    spinBox3->setValue(data3.toInt());

    spinBox1_2->setValue(data1_2.toInt());
    spinBox2_2->setValue(data2_2.toInt());
    spinBox3_2->setValue(data3_2.toInt());


    lineEdit1->setText(edit1);
    lineEdit2->setText(edit2);
    lineEdit3->setText(edit3);
}

void selfdefined::paintEvent(QPaintEvent*){
    QPainter painter(this);

    QPixmap pixmap(":/photos/backgreen.jpeg");
    painter.drawPixmap(this->rect(),pixmap);
}
