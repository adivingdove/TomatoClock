#include "shuju.h"
#include "ui_shuju.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QMessageBox>


shuju::shuju(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::shuju)
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
    db.setDatabaseName("shuju.db");  // Database in memory

    if (db.open()) {
        qDebug() << "Connected to SQLite in-memory database!";
        createTable();  // Create table if not exists
    } else {
        qDebug() << "Failed to connect to SQLite in-memory database:" << db.lastError().text();
    }
}

shuju::~shuju()
{
    delete ui;
}
void shuju::createTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS SysAdmins ("
               "LoginID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
               "LoginName TEXT NOT NULL,"
               "LoginPwd TEXT NOT NULL,"
               "Role TEXT NOT NULL"
               ")");
}



void shuju::on_btninsert_clicked()
{    int loginID = ui->txt_id->toPlainText().toInt();
    QString loginName = ui->txt_name->toPlainText();
    QString loginPwd = ui->txt_pwd->toPlainText();
    QString role = ui->txt_role->toPlainText();
    QSqlQuery query;
    query.prepare("INSERT INTO SysAdmins (LoginID, LoginName, LoginPwd,Role) VALUES (:value1, :value2, :value3,:value4)");
    query.bindValue(":value1", ui->txt_id->toPlainText().toInt());
    query.bindValue(":value2", ui->txt_name->toPlainText());
    query.bindValue(":value3", ui->txt_pwd->toPlainText());
    query.bindValue(":value4", ui->txt_role->toPlainText());
    if (query.exec()) {
        Query();
    } else {
        qDebug() << "插入失败: " << query.lastError().text();
        // 检查是否是唯一约束失败的错误
        QString errorText = query.lastError().text();
        if (errorText.contains("UNIQUE constraint failed")) {
            QMessageBox::warning(this, "插入失败", "插入数据失败：登录ID已存在，请输入唯一的登录ID。");
        } else {
            QMessageBox::warning(this, "插入失败", "插入数据失败：" + errorText);
        }
    }
}


void shuju::Query()
{
    int row = 0;

    ui->tableWidget->setRowCount(0);  // 清空表格行数

    QSqlQuery query;
    if (query.exec("SELECT * FROM SysAdmins")) {
        QSqlRecord record = query.record();
        ui->tableWidget->setColumnCount(record.count());  // 设置表格列数

        // 设置表头标签
        ui->tableWidget->setHorizontalHeaderLabels({"编号", "人名", "任务名", "内容"});

        // 输出查询结果到表格
        while (query.next()) {
            ui->tableWidget->insertRow(row);
            for (int var = 0; var < record.count(); ++var) {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(var).toString());
                item->setToolTip(query.value(var).toString());  // 设置提示为完整的文本内容
                ui->tableWidget->setItem(row, var, item);
            }
            row++;
        }

        // 调整列宽和设置其他属性
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->setWordWrap(true);  // 允许文本换行
    } else {
        qDebug() << "查询失败: " << query.lastError().text();
    }
}


void shuju::on_btnquery_clicked()
{
    Query();
}


void shuju::on_btndelete_clicked()
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

void shuju::on_btnupdate_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE SysAdmins SET  LoginName=:value2, LoginPwd=:value3,Role=:value4 WHERE LoginID=:value1");
    query.bindValue(":value1", ui->txt_id->toPlainText().toInt());
    query.bindValue(":value2", ui->txt_name->toPlainText());
    query.bindValue(":value3", ui->txt_pwd->toPlainText());
    query.bindValue(":value4", ui->txt_role->toPlainText());
    if (query.exec()) {
        Query();
    } else {
        qDebug() << "更新失败: " << query.lastError().text();
    }
}


