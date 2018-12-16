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
    qDebug() << db.tables();/*
    qDebug() << readFromTable("weight", "Hen");
    qDebug() << readFromTable("age", "Hen");*/
}

QStringList SQLiteAdapter::readFromTable(QString data, QString tableName)
{
    QStringList response;
    QString request = "SELECT " + data + " FROM " + tableName + ";";
    //qDebug() << request;
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
    return response;
}

QStringList SQLiteAdapter::readFromTable(QString data, QString tableName, QString condition)
{
    QStringList response;
    QString request = "SELECT " + data + " FROM " + tableName + " WHERE " + condition + ";";
    //qDebug() << request;
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

void SQLiteAdapter::insertData(QString tableName, QStringList arguments, QStringList data)
{
    QString request = "INSERT INTO " + tableName + "(";
    unsigned int argumentsLength = arguments.length();
    for(unsigned int i = 0; i < argumentsLength - 1; i++)
    {
        QString tmp = arguments[i] + ", ";
        request += tmp;
    }
    request += arguments[argumentsLength - 1] + ") VALUES (";
    unsigned int dataLength = data.length();
    for(unsigned int i = 0; i < dataLength - 1; i++)
    {
        QString tmp = data[i] + ", ";
        request += tmp;
    }
    request += data[dataLength - 1] + ")";
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
}

void SQLiteAdapter::deleteData(QString tableName, QString key, QString value)
{
    QString request = "DELETE FROM " + tableName + " WHERE " + key + " = " + value + ";";
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
}

void SQLiteAdapter::deleteData(QString tableName, QString condition)
{
    QString request = "DELETE FROM " + tableName + " WHERE " + condition + ";";
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
}

void SQLiteAdapter::updateData(QString tableName, QString updateKey, QString updateValue, QString findKey, QString findValue)
{
    QString request = "UPDATE " + tableName + " SET " + updateKey + " = " + updateValue + " WHERE " + findKey + " = " + findValue;
    //qDebug() << request;
    QSqlQuery query;
    if(query.prepare(request))
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
