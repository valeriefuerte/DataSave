#include "mainwindowcontroller.h"

MainWindowController::MainWindowController()
{
    setupSQLiteAdapter();
}

MainWindowController::~MainWindowController()
{
    delete sqliteAdapter;
}

SQLiteAdapter *MainWindowController::getSqliteAdapter() const
{
    return sqliteAdapter;
}

void MainWindowController::setSqliteAdapter(SQLiteAdapter *value)
{
    sqliteAdapter = value;
}

void MainWindowController::openDatabase()
{
    try
    {
        sqliteAdapter->open();
    }
    catch(std::runtime_error e)
    {
        QMessageBox(QMessageBox::Warning, "Error", e.what()).exec();
    }
}

QString MainWindowController::getDatabaseName()
{
    return sqliteAdapter->getDatabaseName();
}

QStringList MainWindowController::getTablesNames()
{
    return sqliteAdapter->getTablesNames();
}

QStringList MainWindowController::readFromTable(QString data, QString tableName)
{
    return sqliteAdapter->readFromTable(data, tableName);
}

/*QStringList MainWindowController::getAllFreeCagesList()
{
    QStringList freeCages;

    QString request = "SELECT manufactory_number, row_number, cage_number FROM Cage"
            " EXCEPT SELECT cage_manufactory, cage_row, cage_number FROM Hen";
    QSqlQuery query = sqliteAdapter->runSQL(request);
    while (query.next())
    {
        QString freeCage;
        freeCage += query.value("manufactory_number").toString() + ":" + query.value("row_number").toString() + ":" + query.value("cage_number").toString();
        freeCages.push_back(freeCage);
    }

    return freeCages;
}*/

QList<QList<QTableWidgetItem *> > MainWindowController::getOneWorld()
{
    QList< QList<QTableWidgetItem*> > oneWorld;
    QStringList airlinesNames = sqliteAdapter->readFromTable("Name", "OneWorld");

    for(auto airlineName : airlinesNames)
    {
        QList<QTableWidgetItem*> name;
        QTableWidgetItem* item = new QTableWidgetItem(airlineName);
        name.push_back(item);
        oneWorld.push_back(name);
    }

    for(int i = 0; i < airlinesNames.size(); i++)
    {
        QString condition = "Name = " + airlinesNames[i];
        QStringList country = sqliteAdapter->readFromTable("Country", "OneWorld", condition);
        QStringList loginDate = sqliteAdapter->readFromTable("Login Date", "OneWorld", condition);
        QStringList releaseDate = sqliteAdapter->readFromTable("Release Date", "OneWorld", condition);

        /*oneWorld[i].push_back(new QTableWidgetItem(country[0]));
        qDebug() << country[0];
        oneWorld[i].push_back(new QTableWidgetItem(loginDate[0]));
        oneWorld[i].push_back(new QTableWidgetItem(releaseDate[0]));
        qDebug() << oneWorld;*/
    }
    qDebug() << "Fail!";
    return oneWorld;
}

QList<QList<QTableWidgetItem *> > MainWindowController::getAirlines()
{
    QList< QList<QTableWidgetItem*> > Airlines;
    QStringList airlinesNames = sqliteAdapter->readFromTable("Name", "Airlines");

    for(auto airlineName : airlinesNames)
    {
        QList<QTableWidgetItem*> name;
        QTableWidgetItem* item = new QTableWidgetItem(airlineName);
        name.push_back(item);
        Airlines.push_back(name);
    }

    for(int i = 0; i < airlinesNames.size(); i++)
    {
        QString condition = "name = " + airlinesNames[i];
        QStringList airplane = sqliteAdapter->readFromTable("Airplane", "Airlines", condition);
        QStringList flightFrom = sqliteAdapter->readFromTable("Flight From", "Airlines", condition);
        QStringList flightTo = sqliteAdapter->readFromTable("Flight To", "Airlines", condition);

        Airlines[i].push_back(new QTableWidgetItem(airplane[0]));
        Airlines[i].push_back(new QTableWidgetItem(flightFrom[0]));
        Airlines[i].push_back(new QTableWidgetItem(flightTo[0]));
    }

    return Airlines;
}

QList<QList<QTableWidgetItem *> > MainWindowController::getAirplanes()
{
    QList< QList<QTableWidgetItem*> > Airplanes;
    QStringList airplanesNames = sqliteAdapter->readFromTable("Type", "Airplanes");

    for(auto airlineName : airplanesNames)
    {
        QList<QTableWidgetItem*> name;
        QTableWidgetItem* item = new QTableWidgetItem(airlineName);
        name.push_back(item);
        Airplanes.push_back(name);
    }

    for(int i = 0; i < airplanesNames.size(); i++)
    {
        QString condition = "type = " + airplanesNames[i];
        QStringList date = sqliteAdapter->readFromTable("Date", "Airplanes", condition);
        Airplanes[i].push_back(new QTableWidgetItem(date[0]));
    }

    return Airplanes;
}

QList<QList<QTableWidgetItem *> > MainWindowController::getAirport()
{
    QList< QList<QTableWidgetItem*> > Airports;
    QStringList airportsNames = sqliteAdapter->readFromTable("Name", "Airports");

    for(auto airportName : airportsNames)
    {
        QList<QTableWidgetItem*> name;
        QTableWidgetItem* item = new QTableWidgetItem(airportName);
        name.push_back(item);
        Airports.push_back(name);
    }

    for(int i = 0; i < airportsNames.size(); i++)
    {
        QString condition = "name = " + airportsNames[i];
        QStringList location = sqliteAdapter->readFromTable("Location", "Airports", condition);
        QStringList typeOfPlane = sqliteAdapter->readFromTable("Type of plane", "Airports", condition);
        QStringList terminal = sqliteAdapter->readFromTable("Terminal", "Airports", condition);

        Airports[i].push_back(new QTableWidgetItem(location[0]));
        Airports[i].push_back(new QTableWidgetItem(typeOfPlane[0]));
        Airports[i].push_back(new QTableWidgetItem(terminal[0]));
    }

    return Airports;
}

void MainWindowController::setupSQLiteAdapter()
{
    sqliteAdapter = new SQLiteAdapter("/home/valerie/Projects/DataSave/models/tables.db");
}
