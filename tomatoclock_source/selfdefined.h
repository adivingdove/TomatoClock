#ifndef SELFDEFINED_H
#define SELFDEFINED_H

#include <QWidget>
#include <QSpinBox>
#include<QPainter>

namespace Ui {
class selfdefined;
}

class selfdefined : public QWidget
{
    Q_OBJECT

public:
    explicit selfdefined(QWidget *parent = nullptr);
    ~selfdefined();

private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_start1_clicked();

    void on_start2_clicked();

    void on_start3_clicked();

    void paintEvent(QPaintEvent*);

private:
    Ui::selfdefined *ui;
    // 保存数据到配置文件
    void saveData(const QString &key, const QString &value);


    // 从配置文件加载数据
    void loadData(QSpinBox *spinBox1,QSpinBox *spinBox2,QSpinBox *spinBox3,
                  QSpinBox *spinBox1_2,QSpinBox *spinBox2_2,QSpinBox *spinBox3_2,
                  QLineEdit *lineEdit1,QLineEdit *lineEdit2,QLineEdit *lineEdit3);
};

#endif // SELFDEFINED_H
