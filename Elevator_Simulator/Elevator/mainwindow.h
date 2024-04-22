#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Elevator.h"
#include "Level.h"
#include <QMainWindow>
#include <QSignalMapper>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Elevator *e = new Elevator(1, this);
    Elevator *e2 = new Elevator(2, this);
    Elevator *e3 = new Elevator(3, this);
    Level *l1 = new Level(1, this);
    Level *l2 = new Level(2, this);
    Level *l3 = new Level(3, this);
    Level *l4 = new Level(4, this);
    Level *l5 = new Level(5, this);
    Level *l6 = new Level(6, this);
    Level *l7 = new Level(7, this);

// not in use
//QSignalMapper* po_sigmapper = new QSignalMapper(this);
//    QTimer *timer = new QTimer(this);

public:
    void updateDisplayE1(QString);
    void updateDisplayE2(QString);
    void updateDisplayE3(QString);
    void updateConsole(QString);
    void sendLevel(Elevator*, int);



private slots:
    void powerOutage();
    void callForHelp();
    void checkWeight();
    void fire();
    void blockDoor();
    void level1();
    void level2();
    void level3();
    void level4();
    void level5();
    void level6();
    void level7();
    void initialize();
    void requestF1();
    void requestF2_up();
    void requestF2_down();
    void requestF3_up();
    void requestF3_down();
    void requestF4_up();
    void requestF4_down();
    void requestF6_up();
    void requestF6_down();
    void requestF5_up();
    void requestF5_down();
    void requestF7();


};
#endif // MAINWINDOW_H
