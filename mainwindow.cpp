#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    this->showMaximized();
    setup();
    setRequests();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mainWindowController;
}

void MainWindow::setup()
{
    mainWindowController = new MainWindowController();
    connect(mainWindowController->getSqliteAdapter(), SIGNAL(databaseIsOpen()), this, SLOT(showDatabaseConnected()));
    connect(mainWindowController->getSqliteAdapter(), SIGNAL(databaseIsNotOpen()), this, SLOT(showDatabaseDisconnected()));
    connect(mainWindowController->getSqliteAdapter(), SIGNAL(databaseIsOpen()), this, SLOT(setupDatabaseWidgets()));
    mainWindowController->openDatabase();
}

void MainWindow::setupDatabaseWidgets()
{
    viewTables();
    connect(mainWindowController->getSqliteAdapter(), SIGNAL(databaseStateIsChanged()), this, SLOT(update()));
}

void MainWindow::viewTables()
{
    updateOneWorld();
}

void MainWindow::showDatabaseDisconnected()
{
    ui->statusBar->showMessage("Database is disconnected");
}

void MainWindow::showDatabaseConnected()
{
    ui->statusBar->showMessage("Database is connected");
}

void MainWindow::updateOneWorld()
{
    QList< QList<QTableWidgetItem*> > OneWorld = mainWindowController->getOneWorld();
    qDebug() << "Fail!";
    QStringList labels = {
        "Название",
        "Страна",
        "Дата входа",
        "Дата выхода"
    };
    ui->AirlineAllianceTableWidget->setColumnCount(labels.size());
    ui->AirlineAllianceTableWidget->setHorizontalHeaderLabels(labels);
    ui->AirlineAllianceTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

/*
    ui->workersTableWidget->setColumnCount(labels.size());
    ui->workersTableWidget->setHorizontalHeaderLabels(labels);
    ui->workersTableWidget->setRowCount(workers.size());
    for(int i = 0; i < workers.size(); i++)
    {
        for(int j = 0; j < workers[i].size(); j++)
        {
            ui->workersTableWidget->setItem(i, j, workers[i][j]);
        }
    }


    QStringList workersCages;
    for(int i = 0; i < workers.size(); i++)
    {
        QString condition = "worker = " + workers[i][0]->text();
        QStringList cagesManufactoryNumbers = mainWindowController->getSqliteAdapter()->readFromTable("manufactory_number", "Cage", condition);
        QStringList cagesRowNumbers = mainWindowController->getSqliteAdapter()->readFromTable("row_number", "Cage", condition);
        QStringList cagesNumbers = mainWindowController->getSqliteAdapter()->readFromTable("cage_number", "Cage", condition);

        size_t length = std::min(cagesManufactoryNumbers.size(), std::min(cagesRowNumbers.size(), cagesNumbers.size()));
        QString cages;
        for(size_t j = 0; j < length; j++)
        {
            QString cage = cagesManufactoryNumbers[j] + ":" + cagesRowNumbers[j] + ":" + cagesNumbers[j];
            cages += cage + "; ";
        }
        workersCages.push_back(cages);
    }

    for(size_t i = 0; i < workers.size(); i++)
    {
        ui->workersTableWidget->setItem(i, workers[i].size(), new QTableWidgetItem(workersCages[i]));
    }

    ui->workersTableWidget->resizeColumnsToContents();
    ui->workersTableWidget->verticalHeader()->hide();
    */
}

void MainWindow::updateAirlines()
{

}

void MainWindow::updateAirplanes()
{

}

void MainWindow::updateAirports()
{

}

void MainWindow::setRequests()
{
    ui->queryComboBox->addItem("Все самолеты авиакомпании Аэрофлот старше 30 лет");
    ui->queryComboBox->addItem("Список авиакомпаний из альянса OneWorld, которые вошли в него в 2008 году и вышли в 2010");
    ui->queryComboBox->addItem("Все общие рейсы авиакомпаний   ");
    ui->queryComboBox->addItem("Все самолеты из альянса OneWorld");
}

void MainWindow::on_queryComboBox_activated(int index)
{
    switch (index)
       {
       case 0:
           qDebug() << "Все самолеты авиакомпании Аэрофлот старше 30 лет";
           break;

       case 1:
           qDebug() << "Список авиакомпаний из альянса OneWorld, которые вошли в него в 2008 году и вышли в 2010";
           break;

       case 2:
           qDebug() << "Все общие рейсы авиакомпаний   ";
           break;

       case 3:
           qDebug() << "Все самолеты из альянса OneWorld";
           break;

       default:
           break;
       }
}
