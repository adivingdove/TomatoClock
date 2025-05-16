#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_btninsert_clicked();


    void on_btnquery_clicked();

    void on_btndelete_clicked();

    void on_btnupdate_clicked();

private:
    Ui::Widget *ui;
    void Query();
    void createTable();
};
#endif // WIDGET_H
