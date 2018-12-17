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
    updateAirlines();
    updateAirplanes();
    updateAirports();
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
    QStringList labels = {
        "Код",
        "Название",
        "Страна",
        "Дата входа",
        "Дата выхода"
    };
    ui->AirlineAllianceTableWidget->setColumnCount(labels.size());
    ui->AirlineAllianceTableWidget->setHorizontalHeaderLabels(labels);
    ui->AirlineAllianceTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->AirlineAllianceTableWidget->setRowCount(OneWorld.size());
    ui->AirlineAllianceTableWidget->setColumnHidden(0, true);

    for(int i = 0; i < OneWorld.size(); i++)
    {
        for(int j = 0; j < OneWorld[i].size(); j++)
        {
            ui->AirlineAllianceTableWidget->setItem(i, j, OneWorld[i][j]);
        }
    }
}

void MainWindow::updateAirlines()
{
    QList< QList<QTableWidgetItem*> > Airlines = mainWindowController->getAirlines();
    QStringList labels = {
        "Код",
        "Название",
        "Самолет",
        "Вылет из",
        "Полет в"
    };
    ui->AirlinesTableWidget->setColumnCount(labels.size());
    ui->AirlinesTableWidget->setHorizontalHeaderLabels(labels);
    ui->AirlinesTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->AirlinesTableWidget->setRowCount(Airlines.size());
    ui->AirlinesTableWidget->setColumnHidden(0, true);

    for(int i = 0; i < Airlines.size(); i++)
    {
        for(int j = 0; j < Airlines[i].size(); j++)
        {
            ui->AirlinesTableWidget->setItem(i, j, Airlines[i][j]);
        }
    }
}

void MainWindow::updateAirplanes()
{
    QList< QList<QTableWidgetItem*> > Airplanes = mainWindowController->getAirplanes();
    QStringList labels = {
        "Код",
        "Тип самолета",
        "Дата начала эксплуатации"
    };
    ui->AirplaneTableWidget->setColumnCount(labels.size());
    ui->AirplaneTableWidget->setHorizontalHeaderLabels(labels);
    ui->AirplaneTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->AirplaneTableWidget->setRowCount(Airplanes.size());
    ui->AirplaneTableWidget->setColumnHidden(0, true);

    for(int i = 0; i < Airplanes.size(); i++)
    {
        for(int j = 0; j < Airplanes[i].size(); j++)
        {
            ui->AirplaneTableWidget->setItem(i, j, Airplanes[i][j]);
        }
    }
}

void MainWindow::updateAirports()
{
    QList< QList<QTableWidgetItem*> > Airports = mainWindowController->getAirport();
    QStringList labels = {
        "Код",
        "Название",
        "Местоположение",
        "Тип самолета",
        "Терминал"
    };
    ui->AirportTableWidget->setColumnCount(labels.size());
    ui->AirportTableWidget->setHorizontalHeaderLabels(labels);
    ui->AirportTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->AirportTableWidget->setRowCount(Airports.size());
    ui->AirportTableWidget->setColumnHidden(0, true);

    for(int i = 0; i < Airports.size(); i++)
    {
        for(int j = 0; j < Airports[i].size(); j++)
        {
            ui->AirportTableWidget->setItem(i, j, Airports[i][j]);
        }
    }
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
