#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QWidget>

namespace Ui {
class settingPage;
}

class settingPage : public QWidget
{
    Q_OBJECT

public:
    explicit settingPage(QWidget *parent = nullptr);
    ~settingPage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::settingPage *ui;
};

#endif // SETTINGPAGE_H
