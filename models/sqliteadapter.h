#ifndef SQLITEADAPTER_H
#define SQLITEADAPTER_H

#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>

class SQLiteAdapter : public QObject
{
    Q_OBJECT
public:
    SQLiteAdapter(QString path);
    ~SQLiteAdapter();

    void open();

    QStringList readFromTable(QString data, QString tableName);
    QStringList readFromTable(QString data, QString tableName, QString condition);

    QString getDatabaseName();
    QStringList getTablesNames();

    QSqlQuery runSQL(QString request);

signals:
    void databaseIsOpen();
    void databaseIsNotOpen();
    void databaseStateIsChanged();
private:
    QSqlDatabase db;
};

#endif // SQLITEADAPTER_H
