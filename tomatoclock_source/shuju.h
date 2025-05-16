#ifndef SHUJU_H
#define SHUJU_H

#include <QWidget>
#include <QtSql>


namespace Ui { class shuju; }


class shuju : public QWidget
{
    Q_OBJECT

public:
    explicit shuju (QWidget *parent = nullptr);
    ~shuju();

private slots:

    void on_btninsert_clicked();


    void on_btnquery_clicked();

    void on_btndelete_clicked();

    void on_btnupdate_clicked();

private:
    Ui::shuju *ui;
    shuju * s;
    void Query();
    void createTable();
};
#endif // SHUJU_H
