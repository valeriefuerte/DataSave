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
        "Авиакомпания",
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
    ui->queryComboBox->addItem("Все самолеты младше 10 лет");
    ui->queryComboBox->addItem("Список авиакомпаний из альянса OneWorld, которые вошли в него в 2008 году и вышли в 2010");
    ui->queryComboBox->addItem("Все авиакомпании, летающие из Москвы в Тиват");
    ui->queryComboBox->addItem("Все самолеты из альянса OneWorld в порядке, обратном лексиграфическому");
    ui->queryComboBox->addItem("Минимальный, максимальный и средний год начала эксплуатации самолетов");
    ui->queryComboBox->addItem("Все авиакомпании, которые состоят в альянсе OneWorld в настоящее время в порядке вхождения в альянс");
    ui->queryComboBox->addItem("Вывести список всех самолетов типа Airbus");
    ui->queryComboBox->addItem("Все самолеты, прилетающие в Пулково, терминал 1");
    ui->queryComboBox->addItem("Таблица, состоящая из полей: расположение, тип самолета, терминал, где номер терминала может быть от 1 до 3");
    ui->queryComboBox->addItem("Все рейсы, вылетающие из Гамбурга и все рейсы, прилетающие в Доху");
    ui->queryComboBox->addItem("Все самолеты, которые принадлежат авиакомпаниям входящим в альянс OneWorld, в алфавитном порядке по имени авиакомпании");
    ui->queryComboBox->addItem("Все самолеты, которые принадлежат авиакомпаниям вышедшим из альянса OneWorld");
    ui->queryComboBox->addItem("Все самолеты, прилетающие в Москву и данные о которых есть в таблицах Аэропорты и Самолеты в алфавитном порядке");
    ui->queryComboBox->addItem("Все авиакомпании, входящие в альянс OneWorld и летающие в Хельсинки");
    ui->queryComboBox->addItem("Все самолеты, вступившие в 1999 году и входящие в настоящее время в альянс OneWorld");
}

void MainWindow::on_queryComboBox_activated(int index)
{
    ui->sqlTextEdit->clear();
    ui->resultTableWidget->clear();
    switch (index)
    {
        case 0:
            {
            qDebug() << "Все самолеты младше 10 лет";
            QString request = "SELECT Name,  Airplane, Date FROM Airlines JOIN Airplanes ON (Airlines.Airplane = Airplanes.Type AND Airlines.Name == Airplanes.Airline)  WHERE (Airplanes.Date > 2008)";
            ui->sqlTextEdit->setText(request);
            QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);
            qDebug() << query.value(0);

            int count = 0;
            QStringList l1;
            QStringList l2;
            QStringList l3;
            while (query.next())
            {
                count++;
                QString n = query.value(0).toString();
                l1.push_back(n);
                QString a = query.value(1).toString();
                l2.push_back(a);
                QString d = query.value(2).toString();
                l3.push_back(d);
            }
            qDebug() << count;
            qDebug() << l1;
            qDebug() << l2;
            qDebug() << l3;

            QStringList labels = {
                "Название",
                "Самолет",
                "Дата начала эксплуатации"
            };
            ui->resultTableWidget->setColumnCount(labels.size());
            ui->resultTableWidget->setHorizontalHeaderLabels(labels);
            ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->resultTableWidget->setRowCount(l1.size());

            for(int i = 0; i < count; i++)
            {
                qDebug() << "i: "<< i;
                for(int j = 0; j < l1.size()/count; j++)
                {
//                    qDebug() << "j: "<< j;
//                    qDebug() << "l.value(i)" << l.value(i);
//                    qDebug() << "l.value(j)" << l.value(j);
                    QString n = l1.value(i);
                    QTableWidgetItem *item = new QTableWidgetItem(n);
                    QString a = l2.value(i);
                    QTableWidgetItem *itemA = new QTableWidgetItem(a);
                    QString d = l3.value(i);
                    QTableWidgetItem *itemD = new QTableWidgetItem(d);
                    ui->resultTableWidget->setItem(i, j, item);
                    ui->resultTableWidget->setItem(i, j+1, itemA);
                    ui->resultTableWidget->setItem(i, j+2, itemD);
                }
            }
            break;
            }
        case 1:
            {
            qDebug() << "Список авиакомпаний из альянса OneWorld, которые вошли в него в 2008 году и вышли в 2010";
            QString request = "SELECT OneWorld.Name, OneWorld.Country FROM OneWorld WHERE ( OneWorld.LoginDate = 2008 and OneWorld.ReleaseDate = 2010)";
            ui->sqlTextEdit->setText(request);
            QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

            int count = 0;
            QStringList listN;
            QStringList listC;
            while (query.next())
            {
                count++;
                QString n = query.value(0).toString();
                listN.push_back(n);
                QString c = query.value(1).toString();
                listC.push_back(c);
            }

            QStringList labels = {
                "Название",
                "Страна"
            };
            ui->resultTableWidget->setColumnCount(labels.size());
            ui->resultTableWidget->setHorizontalHeaderLabels(labels);
            ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->resultTableWidget->setRowCount(listN.size());

            for(int i = 0; i < count; i++)
            {
                for(int j = 0; j < listN.size()/count; j++)
                {
                    QString s = listN.value(i);
                    QTableWidgetItem *item = new QTableWidgetItem(s);
                    QString t = listC.value(i);
                    QTableWidgetItem *itemT = new QTableWidgetItem(t);
                    ui->resultTableWidget->setItem(i, j, item);
                    ui->resultTableWidget->setItem(i, j+1, itemT);
                }
            }
            break;
            }

        case 2:
            {
            qDebug() << "Все авиакомпании, летающие из Москвы в Тиват";
            QString request = "SELECT Name FROM Airlines WHERE (Airlines.FlightFrom = 'Москва' AND Airlines.FlightTo = 'Тиват')";
            ui->sqlTextEdit->setText(request);
            QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

            int count = 0;
            QStringList list;
            while (query.next())
            {
                count++;
                QString n = query.value(0).toString();
                list.push_back(n);
            }
            qDebug() << count;
            qDebug() << list;

            QStringList labels = {
                "Название"
            };
            ui->resultTableWidget->setColumnCount(labels.size());
            ui->resultTableWidget->setHorizontalHeaderLabels(labels);
            ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->resultTableWidget->setRowCount(list.size());

            for(int i = 0; i < count; i++)
            {
                for(int j = 0; j < list.size(); j++)
                {
                    QString s = list.value(i);
                    QTableWidgetItem *item = new QTableWidgetItem(s);
                    ui->resultTableWidget->setItem(i, j, item);
                }
            }
            break;
            }

        case 3:
            {
            qDebug() << "Все самолеты из альянса OneWorld в порядке, обратном лексиграфическому";
            QString request = "SELECT Type, Airline FROM Airplanes JOIN OneWorld On (Airplanes.Airline = OneWorld.Name) GROUP By Airplanes.Type ORDER BY Airplanes.Type DESC";
            ui->sqlTextEdit->setText(request);
            QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

            int count = 0;
            QStringList listN;
            QStringList listC;
            while (query.next())
            {
                count++;
                QString n = query.value(0).toString();
                listN.push_back(n);
                QString c = query.value(1).toString();
                listC.push_back(c);
            }
            qDebug() << count;
            qDebug() << listN;
            qDebug() << listC;

            QStringList labels = {
                "Название",
                "Авиакомпания"
            };
            ui->resultTableWidget->setColumnCount(labels.size());
            ui->resultTableWidget->setHorizontalHeaderLabels(labels);
            ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->resultTableWidget->setRowCount(listN.size());

            for(int i = 0; i < count; i++)
            {
                for(int j = 0; j < listN.size()/count; j++)
                {
                    QString s = listN.value(i);
                    QTableWidgetItem *item = new QTableWidgetItem(s);
                    QString t = listC.value(i);
                    QTableWidgetItem *itemT = new QTableWidgetItem(t);
                    ui->resultTableWidget->setItem(i, j, item);
                    ui->resultTableWidget->setItem(i, j+1, itemT);
                }
            }
            break;
            }

    case 4:
        {
        qDebug() << "Минимальный, максимальный и средний год (округлить до целого) начала эксплуатации самолетов";
        QString request = "SELECT min(Date), max(Date), ROUND(avg(Date), 0) FROM Airplanes";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList list;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            list.push_back(n);
            QString a = query.value(1).toString();
            list.push_back(a);
            QString d = query.value(2).toString();
            list.push_back(d);
        }
        qDebug() << count;
        qDebug() << list;

        QStringList labels = {
            "Минимум",
            "Максимум",
            "Средний"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(1);

        QString n = list.value(0);
        QTableWidgetItem *item = new QTableWidgetItem(n);
        ui->resultTableWidget->setItem(0, 0, item);
        QString m = list.value(1);
        QTableWidgetItem *item1 = new QTableWidgetItem(n);
        ui->resultTableWidget->setItem(0, 1, item1);
        QString a = list.value(2);
        QTableWidgetItem *item2 = new QTableWidgetItem(n);
        ui->resultTableWidget->setItem(0, 2, item2);
        break;
    }

    case 5:
        {
        qDebug() << "Все авиакомпании, которые состоят в альянсе OneWorld в настоящее время в порядке вхождения в альянс";
        QString request = "SELECT Name, LoginDate FROM OneWorld WHERE (OneWorld.ReleaseDate is Null) ORDER BY OneWorld.LoginDate ASC";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList listN;
        QStringList listC;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            listN.push_back(n);
            QString c = query.value(1).toString();
            listC.push_back(c);
        }
        qDebug() << count;
        qDebug() << listN;
        qDebug() << listC;

        QStringList labels = {
            "Название",
            "Год"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(listN.size());

        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < listN.size()/count; j++)
            {
                QString s = listN.value(i);
                qDebug() << s;
                QTableWidgetItem *item = new QTableWidgetItem(s);
                QString t = listC.value(i);
                qDebug() << t;
                QTableWidgetItem *item1 = new QTableWidgetItem(t);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, item1);
            }
        }
        break;
        }

    case 6:
        {
        qDebug() << "Вывести список всех самолетов типа Airbus";
        QString request = "SELECT DISTINCT Type, Airline, Date FROM Airplanes  JOIN Airports ON (Airplanes.Type = Airports.TypeOfPlane) WHERE (Airplanes.Type LIKE 'Airbus%') ";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList listT;
        QStringList listA;

        while (query.next())
        {
            count++;
            QString t = query.value(0).toString();
            listT.push_back(t);
            QString a = query.value(1).toString();
            listA.push_back(a);
        }
        qDebug() << count;
        qDebug() << listT;
        qDebug() << listA;

        QStringList labels = {
            "Тип самолета",
            "Авиакомпания"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(listT.size());

        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < listT.size()/count; j++)
            {
                QString t = listT.value(i);
                QTableWidgetItem *item1 = new QTableWidgetItem(t);
                QString a = listA.value(i);
                QTableWidgetItem *item2 = new QTableWidgetItem(a);
                ui->resultTableWidget->setItem(i, j, item1);
                ui->resultTableWidget->setItem(i, j+1, item2);

            }
        }
        break;
        }

    case 7:
        {
        qDebug() << "Все самолеты, прилетающие в Пулково, терминал 1";
        QString request = "SELECT TypeOfPlane, Name, Terminal FROM Airports WHERE Airports.Name = 'Пулково' AND Airports.Terminal = 1 ORDER BY Airports.TypeOfPlane ASC";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList l1;
        QStringList l2;
        QStringList l3;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            l1.push_back(n);
            QString a = query.value(1).toString();
            l2.push_back(a);
            QString d = query.value(2).toString();
            l3.push_back(d);
        }
        qDebug() << count;
        qDebug() << l1;
        qDebug() << l2;
        qDebug() << l3;

        QStringList labels = {
            "Самолет",
            "Название",
            "Терминал"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(l1.size());

        for(int i = 0; i < count; i++)
        {
            qDebug() << "i: "<< i;
            for(int j = 0; j < l1.size()/count; j++)
            {
//                    qDebug() << "j: "<< j;
//                    qDebug() << "l.value(i)" << l.value(i);
//                    qDebug() << "l.value(j)" << l.value(j);
                QString n = l1.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(n);
                QString a = l2.value(i);
                QTableWidgetItem *itemA = new QTableWidgetItem(a);
                QString d = l3.value(i);
                QTableWidgetItem *itemD = new QTableWidgetItem(d);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemA);
                ui->resultTableWidget->setItem(i, j+2, itemD);
            }
        }
        break;
        }

    case 8:
        {
        qDebug() << "Таблица, состоящая из полей: расположение, тип самолета, терминал, где номер терминала может быть от 1 до 3";
        QString request = "SELECT Location, TypeOfPlane, Terminal FROM Airports JOIN Airlines ON (Airlines.Airplane = Airports.TypeOfPlane AND (Airlines.FlightFrom = Airports.Location OR Airlines.FlightTo = Airports.Location) ) WHERE (Airports.Terminal BETWEEN 1 AND 3)";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList l1;
        QStringList l2;
        QStringList l3;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            l1.push_back(n);
            QString a = query.value(1).toString();
            l2.push_back(a);
            QString d = query.value(2).toString();
            l3.push_back(d);
        }
        qDebug() << count;
        qDebug() << l1;
        qDebug() << l2;
        qDebug() << l3;

        QStringList labels = {
            "Расположение",
            "Тип самолета",
            "Терминал"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(l1.size());

        for(int i = 0; i < count; i++)
        {
            qDebug() << "i: "<< i;
            for(int j = 0; j < l1.size()/count; j++)
            {
//                    qDebug() << "j: "<< j;
//                    qDebug() << "l.value(i)" << l.value(i);
//                    qDebug() << "l.value(j)" << l.value(j);
                QString n = l1.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(n);
                QString a = l2.value(i);
                QTableWidgetItem *itemA = new QTableWidgetItem(a);
                QString d = l3.value(i);
                QTableWidgetItem *itemD = new QTableWidgetItem(d);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemA);
                ui->resultTableWidget->setItem(i, j+2, itemD);
            }
        }
        break;
        }

    case 9:
        {
        qDebug() << "Все рейсы, вылетающие из Гамбурга и все рейсы, прилетающие в Доху";
        QString request = "SELECT Name, Airplane, FlightFrom, FlightTo FROM Airlines WHERE (Airlines.FlightFrom = 'Гамбург' OR Airlines.FlightTo = 'Лима')";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList l1;
        QStringList l2;
        QStringList l3;
        QStringList l4;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            l1.push_back(n);
            QString a = query.value(1).toString();
            l2.push_back(a);
            QString d = query.value(2).toString();
            l3.push_back(d);
            QString t = query.value(3).toString();
            l4.push_back(t);
        }
        qDebug() << count;
        qDebug() << l1;
        qDebug() << l2;
        qDebug() << l3;
        qDebug() << l4;

        QStringList labels = {
            "Название",
            "Тип самолета",
            "Вылет из",
            "Прилет в"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(l1.size());

        for(int i = 0; i < count; i++)
        {
            qDebug() << "i: "<< i;
            for(int j = 0; j < l1.size()/count; j++)
            {
//                    qDebug() << "j: "<< j;
//                    qDebug() << "l.value(i)" << l.value(i);
//                    qDebug() << "l.value(j)" << l.value(j);
                QString n = l1.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(n);
                QString a = l2.value(i);
                QTableWidgetItem *itemA = new QTableWidgetItem(a);
                QString d = l3.value(i);
                QTableWidgetItem *itemD = new QTableWidgetItem(d);
                QString t = l4.value(i);
                QTableWidgetItem *itemT = new QTableWidgetItem(t);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemA);
                ui->resultTableWidget->setItem(i, j+2, itemD);
                ui->resultTableWidget->setItem(i, j+3, itemT);
            }
        }
        break;
        }

    case 10:
        {
        qDebug() << "Все самолеты, которые принадлежат авиакомпаниям входящим в альянс OneWorld, в алфавитном порядке по имени авиакомпании";
        QString request = "SELECT Type, Airline FROM Airplanes JOIN OneWorld ON (Airplanes.Airline = OneWorld.Name) ORDER BY OneWorld.Name ASC";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList listN;
        QStringList listC;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            listN.push_back(n);
            QString c = query.value(1).toString();
            listC.push_back(c);
        }
        qDebug() << count;
        qDebug() << listN;
        qDebug() << listC;

        QStringList labels = {
            "Тип самолета",
            "Авиакомпания"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(listN.size());

        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < listN.size()/count; j++)
            {
                QString s = listN.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(s);
                QString t = listC.value(i);
                QTableWidgetItem *itemT = new QTableWidgetItem(t);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemT);
            }
        }
        break;
        }

    case 11:
        {
        qDebug() << "Все самолеты, которые принадлежат авиакомпаниям вышедшим из альянса OneWorld";
        QString request = "SELECT Type, Airline FROM Airplanes JOIN Airlines ON (Airplanes.Type = Airlines.Airplane AND Airplanes.Airline = Airlines.Name) JOIN OneWorld ON (Airplanes.Airline = OneWorld.Name) WHERE (OneWorld.ReleaseDate is NOT Null)";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList listN;
        QStringList listC;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            listN.push_back(n);
            QString c = query.value(1).toString();
            listC.push_back(c);
        }
        qDebug() << count;
        qDebug() << listN;
        qDebug() << listC;

        QStringList labels = {
            "Тип самолета",
            "Авиакомпания"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(listN.size());

        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < listN.size()/count; j++)
            {
                QString s = listN.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(s);
                QString t = listC.value(i);
                QTableWidgetItem *itemT = new QTableWidgetItem(t);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemT);
            }
        }
        break;
        }

    case 12:
        {
        qDebug() << "Все самолеты, прилетающие в Москву и данные о которых есть в таблицах Аэропорты и Самолеты в алфавитном порядке";
        QString request = "SELECT TypeOfPlane, Name, Terminal FROM Airports JOIN Airplanes ON (Airplanes.Type = Airports.TypeOfPlane) WHERE Airports.Location = 'Москва' ORDER BY Airports.TypeOfPlane ASC";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList l1;
        QStringList l2;
        QStringList l3;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            l1.push_back(n);
            QString a = query.value(1).toString();
            l2.push_back(a);
            QString d = query.value(2).toString();
            l3.push_back(d);
        }
        qDebug() << count;
        qDebug() << l1;
        qDebug() << l2;
        qDebug() << l3;

        QStringList labels = {
            "Тип самолета",
            "Аэропорт",
            "Терминал"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(l1.size());

        for(int i = 0; i < count; i++)
        {
            qDebug() << "i: "<< i;
            for(int j = 0; j < l1.size()/count; j++)
            {
//                    qDebug() << "j: "<< j;
//                    qDebug() << "l.value(i)" << l.value(i);
//                    qDebug() << "l.value(j)" << l.value(j);
                QString n = l1.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(n);
                QString a = l2.value(i);
                QTableWidgetItem *itemA = new QTableWidgetItem(a);
                QString d = l3.value(i);
                QTableWidgetItem *itemD = new QTableWidgetItem(d);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemA);
                ui->resultTableWidget->setItem(i, j+2, itemD);
            }
        }
        break;
        }

    case 13:
        {
        qDebug() << "Все авиакомпании, входящие в альянс OneWorld и летающие в Хельсинки";
        QString request = "SELECT Distinct OneWorld.Name, OneWorld.Country FROM OneWorld JOIN Airlines ON (Airlines.Name = OneWorld.Name) WHERE (Airlines.FlightFrom = 'Хельсинки' OR Airlines.FlightTo = 'Хельсинки')";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList listN;
        QStringList listC;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            listN.push_back(n);
            QString c = query.value(1).toString();
            listC.push_back(c);
        }
        qDebug() << count;
        qDebug() << listN;
        qDebug() << listC;

        QStringList labels = {
            "Авиакомпания",
            "Страна"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(listN.size());

        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < listN.size()/count; j++)
            {
                QString s = listN.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(s);
                QString t = listC.value(i);
                QTableWidgetItem *itemT = new QTableWidgetItem(t);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemT);
            }
        }
        break;
        }

    case 14:
        {
        qDebug() << "Все самолеты, вступившие в 1999 году и входящие в настоящее время в альянс OneWorld";
        QString request = "SELECT Type, Airline, Country FROM Airplanes JOIN OneWorld ON (Airplanes.Airline = OneWorld.Name) WHERE ( OneWorld.LoginDate=1999 AND OneWorld.ReleaseDate IS NULL)";
        ui->sqlTextEdit->setText(request);
        QSqlQuery query = mainWindowController->getSqliteAdapter()->runSQL(request);

        int count = 0;
        QStringList l1;
        QStringList l2;
        QStringList l3;
        while (query.next())
        {
            count++;
            QString n = query.value(0).toString();
            l1.push_back(n);
            QString a = query.value(1).toString();
            l2.push_back(a);
            QString d = query.value(2).toString();
            l3.push_back(d);
        }
        qDebug() << count;
        qDebug() << l1;
        qDebug() << l2;
        qDebug() << l3;

        QStringList labels = {
            "Тип самолета",
            "Авиакомпания",
            "Страна"
        };
        ui->resultTableWidget->setColumnCount(labels.size());
        ui->resultTableWidget->setHorizontalHeaderLabels(labels);
        ui->resultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->resultTableWidget->setRowCount(l1.size());

        for(int i = 0; i < count; i++)
        {
            qDebug() << "i: "<< i;
            for(int j = 0; j < l1.size()/count; j++)
            {
//                    qDebug() << "j: "<< j;
//                    qDebug() << "l.value(i)" << l.value(i);
//                    qDebug() << "l.value(j)" << l.value(j);
                QString n = l1.value(i);
                QTableWidgetItem *item = new QTableWidgetItem(n);
                QString a = l2.value(i);
                QTableWidgetItem *itemA = new QTableWidgetItem(a);
                QString d = l3.value(i);
                QTableWidgetItem *itemD = new QTableWidgetItem(d);
                ui->resultTableWidget->setItem(i, j, item);
                ui->resultTableWidget->setItem(i, j+1, itemA);
                ui->resultTableWidget->setItem(i, j+2, itemD);
            }
        }
        break;
        }

        default:
            break;
       }
}
