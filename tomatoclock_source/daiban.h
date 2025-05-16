#ifndef DAIBAN_H
#define DAIBAN_H

#include <QWidget>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlError>
#include<QMessageBox>
#include <QListWidget>
#include"tomatoclock.h"
#include<QPaintEvent>

namespace Ui
{
class daiban;
}

class daiban : public QWidget
{
    Q_OBJECT

public:
    explicit daiban(QWidget *parent = nullptr);
    ~daiban();

private slots:

    void on_insertButton_clicked();

    void on_deleteButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void CreateDatabase();
    void CreateTable();
    void QueryTable();
    void paintEvent(QPaintEvent *);

    QSqlDatabase db;
    QSqlQueryModel  dbmodel;

    void initializeDatabase();
    void loadTasksForData(const QDate &date);

private:
    Ui::daiban *ui;
};

#endif // DAIBAN_H

