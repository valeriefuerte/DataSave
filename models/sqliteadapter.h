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

    void insertData(QString tableName, QStringList arguments, QStringList data);
    void deleteData(QString tableName, QString key, QString value);
    void deleteData(QString tableName, QString condition);
    void updateData(QString tableName,
                    QString updateKey,
                    QString updateValue,
                    QString findKey,
                    QString findValue);
    QSqlQuery runSQL(QString request);

signals:
    void databaseIsOpen();
    void databaseIsNotOpen();
    void databaseStateIsChanged();
private:
    QSqlDatabase db;
};

#endif // SQLITEADAPTER_H
