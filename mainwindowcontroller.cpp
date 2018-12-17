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
    QStringList airlinesNames = sqliteAdapter->readFromTable("Code", "OneWorld");

    for(auto airlineName : airlinesNames)
    {
        QList<QTableWidgetItem*> code;
        QTableWidgetItem* item = new QTableWidgetItem(airlineName);
        code.push_back(item);
        oneWorld.push_back(code);
    }
    for(int i = 0; i < airlinesNames.size(); i++)
    {
        QString condition = "Code = " + airlinesNames[i];
        QStringList name = sqliteAdapter->readFromTable("Name", "OneWorld", condition);
        QStringList country = sqliteAdapter->readFromTable("Country", "OneWorld", condition);
        QStringList loginDate = sqliteAdapter->readFromTable("LoginDate", "OneWorld", condition);
        QStringList releaseDate = sqliteAdapter->readFromTable("ReleaseDate", "OneWorld", condition);

        oneWorld[i].push_back(new QTableWidgetItem(name[0]));
        oneWorld[i].push_back(new QTableWidgetItem(country[0]));
        oneWorld[i].push_back(new QTableWidgetItem(loginDate[0]));
        oneWorld[i].push_back(new QTableWidgetItem(releaseDate[0]));
    }
    return oneWorld;
}

QList<QList<QTableWidgetItem *> > MainWindowController::getAirlines()
{
    QList< QList<QTableWidgetItem*> > Airlines;
    QStringList airlinesNames = sqliteAdapter->readFromTable("Code", "Airlines");

    for(auto airlineName : airlinesNames)
    {
        QList<QTableWidgetItem*> code;
        QTableWidgetItem* item = new QTableWidgetItem(airlineName);
        code.push_back(item);
        Airlines.push_back(code);
    }

    for(int i = 0; i < airlinesNames.size(); i++)
    {
        QString condition = "Code = " + airlinesNames[i];
        QStringList name = sqliteAdapter->readFromTable("Name", "Airlines", condition);
        QStringList airplane = sqliteAdapter->readFromTable("Airplane", "Airlines", condition);
        QStringList flightFrom = sqliteAdapter->readFromTable("FlightFrom", "Airlines", condition);
        QStringList flightTo = sqliteAdapter->readFromTable("FlightTo", "Airlines", condition);

        Airlines[i].push_back(new QTableWidgetItem(name[0]));
        Airlines[i].push_back(new QTableWidgetItem(airplane[0]));
        Airlines[i].push_back(new QTableWidgetItem(flightFrom[0]));
        Airlines[i].push_back(new QTableWidgetItem(flightTo[0]));
    }

    return Airlines;
}

QList<QList<QTableWidgetItem *> > MainWindowController::getAirplanes()
{
    QList< QList<QTableWidgetItem*> > Airplanes;
    QStringList airplanesNames = sqliteAdapter->readFromTable("Code", "Airplanes");

    for(auto airlineName : airplanesNames)
    {
        QList<QTableWidgetItem*> code;
        QTableWidgetItem* item = new QTableWidgetItem(airlineName);
        code.push_back(item);
        Airplanes.push_back(code);
    }

    for(int i = 0; i < airplanesNames.size(); i++)
    {
        QString condition = "Code = " + airplanesNames[i];
        QStringList type = sqliteAdapter->readFromTable("Type", "Airplanes", condition);
        QStringList date = sqliteAdapter->readFromTable("Date", "Airplanes", condition);
        Airplanes[i].push_back(new QTableWidgetItem(type[0]));
        Airplanes[i].push_back(new QTableWidgetItem(date[0]));
    }

    return Airplanes;
}

QList<QList<QTableWidgetItem *> > MainWindowController::getAirport()
{
    QList< QList<QTableWidgetItem*> > Airports;
    QStringList airportsNames = sqliteAdapter->readFromTable("Code", "Airports");

    for(auto airportName : airportsNames)
    {
        QList<QTableWidgetItem*> code;
        QTableWidgetItem* item = new QTableWidgetItem(airportName);
        code.push_back(item);
        Airports.push_back(code);
    }

    for(int i = 0; i < airportsNames.size(); i++)
    {
        QString condition = "Code = " + airportsNames[i];
        QStringList name = sqliteAdapter->readFromTable("Name", "Airports", condition);
        QStringList location = sqliteAdapter->readFromTable("Location", "Airports", condition);
        QStringList typeOfPlane = sqliteAdapter->readFromTable("TypeOfPlane", "Airports", condition);
        QStringList terminal = sqliteAdapter->readFromTable("Terminal", "Airports", condition);

        Airports[i].push_back(new QTableWidgetItem(name[0]));
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
