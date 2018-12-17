#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QTableWidgetItem>

#include "./models/sqliteadapter.h"

class MainWindowController : public QObject
{
    Q_OBJECT
public:
    MainWindowController();
    ~MainWindowController();

    SQLiteAdapter *getSqliteAdapter() const;
    void setSqliteAdapter(SQLiteAdapter *value);

    void openDatabase();

    QString getDatabaseName();
    QStringList getTablesNames();
    QStringList readFromTable(QString data, QString tableName);

    QStringList getAllAirlinesList();
    //QStringList getAllFreeCagesList();

    QList<QList<QTableWidgetItem *> > getOneWorld();
    QList<QList<QTableWidgetItem *> > getAirlines();
    QList<QList<QTableWidgetItem *> > getAirplanes();
    QList<QList<QTableWidgetItem *> > getAirport();

    void setBuffer(const QString &value);

    QString getBuffer() const;

signals:

private:
    SQLiteAdapter* sqliteAdapter;
    QString path = "models/tables.db";
    QString buffer;

    void setupSQLiteAdapter();
};

#endif // MAINWINDOWCONTROLLER_H
