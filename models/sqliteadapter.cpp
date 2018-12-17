#include "sqliteadapter.h"

SQLiteAdapter::SQLiteAdapter(QString path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}
SQLiteAdapter::~SQLiteAdapter()
{
    db.close();
}

void SQLiteAdapter::open()
{
    if(!db.open())
    {
        emit databaseIsNotOpen();
        throw std::runtime_error("database is not connected");
    }
    else
    {
        emit databaseIsOpen();
    }
    QSqlQuery query;
    qDebug() << query.exec("PRAGMA foreign_keys = ON;");

    qDebug() << db;
    qDebug() << "db.tables" << db.tables();
}

QStringList SQLiteAdapter::readFromTable(QString data, QString tableName)
{
    QStringList response;
    QString request = "SELECT " + data + " FROM " + tableName + ";";
    qDebug() << "request readFromTable" << request;
    QSqlQuery query;
    if(query.prepare(request))
    {
        if(query.exec())
        {
            if(query.lastError().text() != " ")
            {
                qDebug() << query.lastError().text();
            }
            while (query.next())
            {
                QString parametr = query.value(0).toString();
                response.push_back(parametr);
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу выполнить запрос!");
        }
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу подготовить запрос!");
    }
    qDebug() << response << "\n";
    return response;
}

QStringList SQLiteAdapter::readFromTable(QString data, QString tableName, QString condition)
{
    QStringList response;
    QString request = "SELECT " + data + " FROM " + tableName + " WHERE " + condition + ";";
    qDebug() << request;
    QSqlQuery query;
    if(query.prepare(request))
    {
        if(query.exec())
        {
            if(query.lastError().text() != " ")
            {
                qDebug() << query.lastError().text();
            }
            while (query.next())
            {
                QString parametr = query.value(0).toString();
                response.push_back(parametr);
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу выполнить запрос!");
        }
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу подготовить запрос!");
    }
    qDebug() << response << "\n";
    return response;
}

QString SQLiteAdapter::getDatabaseName()
{
    return db.databaseName();
}

QStringList SQLiteAdapter::getTablesNames()
{
    return db.tables();
}

QSqlQuery SQLiteAdapter::runSQL(QString request)
{
    qDebug() << request;
    QString tmp = request;
    QSqlQuery query;
    if(query.prepare(tmp))
    {
        if(query.exec())
        {
            if(query.lastError().text() != " ")
            {
                qDebug() << query.lastError().text();
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу выполнить запрос!");
        }
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Не могу подготовить запрос!");
    }
    emit databaseStateIsChanged();
    return query;
}
