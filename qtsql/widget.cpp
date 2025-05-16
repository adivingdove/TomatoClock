#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <qDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Connect signals and slots
    connect(ui->tableWidget, &QTableWidget::cellClicked, [&](int row, int col) {
        ui->txt_id->setText(ui->tableWidget->item(row, 0)->text());
        ui->txt_name->setText(ui->tableWidget->item(row, 1)->text());
        ui->txt_pwd->setText(ui->tableWidget->item(row, 2)->text());
        ui->txt_role->setText(ui->tableWidget->item(row, 3)->text());
    });

    // Create an in-memory SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");  // Database in memory

    if (db.open())
    {
        qDebug() << "Connected to SQLite in-memory database!";
        createTable();  // Create table if not exists
    } else {
        qDebug() << "Failed to connect to SQLite in-memory database:" << db.lastError().text();
    }
}

Widget::~Widget()
{
    delete ui;
}
void Widget::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS SysAdmins ("
               "LoginID INTEGER PRIMARY KEY AUTOINCREMENT,"
               "LoginName TEXT NOT NULL,"
               "LoginPwd TEXT NOT NULL,"
               "Role INTEGER NOT NULL"
               ")");
}


void Widget::on_btninsert_clicked()
{
    QSqlQuery query;
        query.prepare("INSERT INTO SysAdmins (LoginID, LoginName, LoginPwd,Role) VALUES (:value1, :value2, :value3,:value4)");
        query.bindValue(":value1", ui->txt_id->toPlainText().toInt());
        query.bindValue(":value2", ui->txt_name->toPlainText());
        query.bindValue(":value3", ui->txt_pwd->toPlainText());
        query.bindValue(":value4", ui->txt_role->toPlainText().toInt());
        if (query.exec()) {
                Query();
            } else {
                qDebug() << "插入失败: " << query.lastError().text();
        }
}


void Widget::Query()
{
    int row= 0;

    ui->tableWidget->setRowCount(0);

    QSqlQuery query;
    if (query.exec("SELECT * FROM SysAdmins")) {

            QSqlRecord record = query.record();
            ui->tableWidget->setColumnCount(record.count());
            ui->tableWidget->setHorizontalHeaderLabels({"编号","人名","任务名","内容"});
            // 输出查询结果
            while (query.next()) {
                ui->tableWidget->insertRow(row);
                for (int var = 0; var < record.count(); ++var) {
                    ui->tableWidget->setItem(row,var,new QTableWidgetItem(query.value(var).toString()));
                }
                row++;
        }
    } else {
        qDebug() << "查询失败: " << query.lastError().text();
    }
}


void Widget::on_btnquery_clicked()
{
   Query();
}


void Widget::on_btndelete_clicked()
{
    QSqlQuery query;
        query.prepare("DELETE FROM SysAdmins WHERE LoginID = :value1");
        query.bindValue(":value1", ui->txt_id->toPlainText().toInt());

        if (query.exec()) {
                Query();
            } else {
                qDebug() << "删除失败: " << query.lastError().text();
        }

}

void Widget::on_btnupdate_clicked()
{
    QSqlQuery query;
        query.prepare("UPDATE SysAdmins SET  LoginName=:value2, LoginPwd=:value3,Role=:value4 WHERE LoginID=:value1");
        query.bindValue(":value1", ui->txt_id->toPlainText().toInt());
        query.bindValue(":value2", ui->txt_name->toPlainText());
        query.bindValue(":value3", ui->txt_pwd->toPlainText());
        query.bindValue(":value4", ui->txt_role->toPlainText().toInt());
        if (query.exec()) {
                Query();
            } else {
                qDebug() << "更新失败: " << query.lastError().text();
        }
}


