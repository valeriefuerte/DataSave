#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mainwindowcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void viewTables();
    void setRequests();

private slots:


    void on_queryComboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    MainWindowController *mainWindowController;

    void setup();
};

#endif // MAINWINDOW_H
