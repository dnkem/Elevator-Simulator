#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <cstdlib>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    // initialize gui
    initialize();

    // & thisss allows other classes to have connections
    //QObject::connect(ui->help, &QPushButton::released, e, &Elevator::callForHelp);
    QObject::connect(ui->help, &QPushButton::released, this, &MainWindow::callForHelp);
    QObject::connect(ui->weight, &QSpinBox::textChanged, this, &MainWindow::checkWeight);
    QObject::connect(ui->poweroutage, &QPushButton::released, this, &MainWindow::powerOutage);
    //connect(ui->poweroutage, &QPushButton::released, po_sigmapper, SLOT(map()));
    QObject::connect(ui->fire, &QPushButton::released, this, &MainWindow::fire);
    QObject::connect(ui->block_door, &QPushButton::released, this, &MainWindow::blockDoor);
    QObject::connect(ui->open, &QPushButton::released, e, &Elevator::openDoor);
    QObject::connect(ui->close, &QPushButton::released, e, &Elevator::closeDoor);
    QObject::connect(ui->reset, &QPushButton::released, this, &MainWindow::initialize);
    QObject::connect(ui->b1, &QPushButton::released, this, &MainWindow::level1);
    QObject::connect(ui->b2, &QPushButton::released, this, &MainWindow::level2);
    QObject::connect(ui->b3, &QPushButton::released, this, &MainWindow::level3);
    QObject::connect(ui->b4, &QPushButton::released, this, &MainWindow::level4);
    QObject::connect(ui->b5, &QPushButton::released, this, &MainWindow::level5);
    QObject::connect(ui->b6, &QPushButton::released, this, &MainWindow::level6);
    QObject::connect(ui->b7, &QPushButton::released, this, &MainWindow::level7);
    QObject::connect(ui->f1_up, &QPushButton::released, this, &MainWindow::requestF1);
    QObject::connect(ui->f7_down, &QPushButton::released, this, &MainWindow::requestF7);
    QObject::connect(ui->f2_up, &QPushButton::released, this, &MainWindow::requestF2_up);
    QObject::connect(ui->f2_down, &QPushButton::released, this, &MainWindow::requestF2_down);
    QObject::connect(ui->f3_up, &QPushButton::released, this, &MainWindow::requestF3_up);
    QObject::connect(ui->f3_down, &QPushButton::released, this, &MainWindow::requestF3_down);
    QObject::connect(ui->f4_up, &QPushButton::released, this, &MainWindow::requestF4_up);
    QObject::connect(ui->f4_down, &QPushButton::released, this, &MainWindow::requestF4_down);
    QObject::connect(ui->f5_up, &QPushButton::released, this, &MainWindow::requestF5_up);
    QObject::connect(ui->f5_down, &QPushButton::released, this, &MainWindow::requestF5_down);
    QObject::connect(ui->f6_up, &QPushButton::released, this, &MainWindow::requestF6_up);
    QObject::connect(ui->f6_down, &QPushButton::released, this, &MainWindow::requestF6_down);

    // Establish signal mapper
    //po_sigmapper -> setMapping (ui->poweroutage, e);
    //connect(po_sigmapper, SIGNAL(mapped(Elevator*)), this, SLOT(powerOutage(Elevator*)));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::updateConsole(QString s){
    ui->listWidget->addItem(s);
    ui->listWidget->update();
}

void MainWindow::powerOutage(){
    // elevator 1
    sendLevel(e, 1);
    updateConsole(e->playAudio("E1 Audio: Caution! There is a POWER OUTAGE. Elevator is headed to the safe floor, level 1"));
    updateDisplayE1(e->displayItem("E1 Display System: Caution! There is a POWER OUTAGE. Heading to Level 1"));
    updateConsole("E1: " + e->ringBell());
    updateConsole("E1: " +e->openDoor());
    // elevator 2
    sendLevel(e2, 1);
    updateConsole(e2->playAudio("E2 Audio: Caution! There is a POWER OUTAGE. Elevator is headed to the safe floor, level 1"));
    updateDisplayE2(e3->displayItem("E2 Display System: Caution! There is a POWER OUTAGE. Heading to Level 1"));
    updateConsole("E2: " + e2->ringBell());
    updateConsole("E2: " + e2->openDoor());
    // elevator 2
    sendLevel(e3, 1);
    updateConsole(e3->playAudio("E3 Elevator Audio: Caution! There is a POWER OUTAGE. Elevator is headed to the safe floor, level 1"));
    updateDisplayE3(e3->displayItem("E3 Display System: Caution! There is a POWER OUTAGE. Heading to Level 1"));
    updateConsole("E3: " +e3->ringBell());
    updateConsole("E3: " +e3->openDoor());

    updateConsole("End of POWER OUTAGE segment.\n\n");
}

void MainWindow::callForHelp(){
   updateConsole("Elevator calls for building safety!");

}

void MainWindow::sendLevel(Elevator* el, int newLevel){
    updateConsole(el->closeDoor());
    if (el->setLevel(newLevel) == false){
        updateConsole("Already at this level");
    } else {
        if (el->getId() == 1){
            updateDisplayE1(QString::number(e->getLevel()));
            ui->floor_screen->setText(QString::number(e->getLevel()));
        } else if (el->getId() == 2){
            e2->setLevel(newLevel);
            updateDisplayE2(QString::number(e2->getLevel()));
        } else if (el->getId() == 3){
            e3->setLevel(newLevel);
            updateDisplayE3(QString::number(e3->getLevel()));
        } else {
            qInfo("something wroooong");
        }
        updateConsole("Sending E" + QString::number(el->getId()) + " to Level " + QString::number(newLevel));
        updateConsole(el->openDoor());
    }
}

void MainWindow::updateDisplayE1(QString text){
    ui->e1_screen->clear();
    ui->e1_screen->addItem(text);
    ui->e1_screen->update();
    ui->floor_screen->clear();
    ui->floor_screen->setText(QString::number(e->getLevel()));
    ui->floor_screen->update();
}
void MainWindow::updateDisplayE2(QString text){
    ui->e2_screen->clear();
    ui->e2_screen->addItem(text);
    ui->e2_screen->update();
}
void MainWindow::updateDisplayE3(QString text){
    ui->e3_screen->clear();
    ui->e3_screen->addItem(text);
    ui->e3_screen->update();
}

void MainWindow::checkWeight(){
    if (ui->weight->value() > 200){
        updateConsole(e->ringBell());
        updateConsole(e->playAudio("E1 Audio: This maximum weight limit has been exceeded"));
        updateDisplayE1(e->displayItem("E1 Display: This maximum weight limit has been exceeded"));
        updateConsole(e->openDoor());
    } else {
//        updateDisplay("nothing");
//        sendLevel()
    }
}

void MainWindow::fire(){
    // elevator 1
    sendLevel(e, 1);
    updateConsole(e->playAudio("E1 Audio: Caution! There is a FIRE in the building. Elevator is headed to the safe floor, level 1"));
    updateDisplayE1(e->displayItem("E1 Display System: Caution! There is a FIRE in the building. Heading to Level 1"));
    updateConsole("E1: " + e->ringBell());
    updateConsole("E1: " + e->openDoor());
    // elevator 2
    sendLevel(e2, 1);
    updateConsole(e2->playAudio("E2 Audio: Caution! There is a FIRE in the building. Elevator is headed to the safe floor, level 1"));
    updateDisplayE2(e2->displayItem("E2 Display System: Caution! There is a FIRE in the building. Heading to Level 1"));
    updateConsole("E2: " + e2->ringBell());
    updateConsole("E2:" + e2->openDoor());
    // elevator 2
    sendLevel(e3, 1);
    updateConsole(e3->playAudio("E3 Audio: Caution! There is a FIRE in the building. Elevator is headed to the safe floor, level 1"));
    updateDisplayE3(e3->displayItem("E3 Display System: Caution! There is a FIRE in the building. Heading to Level 1"));
    updateConsole("E3: " + e3->ringBell());
    updateConsole("E3: " + e3->openDoor());

    updateConsole("End of FIRE segment.\n\n");
}
void MainWindow::initialize(){
    ui->e1_screen->clear();
    sendLevel(e, 3);
    sendLevel(e2, 3);
    sendLevel(e3, 3);
    e->setDoorState("closed");
    e2->setDoorState("closed");
    e3->setDoorState("closed");

    // main display
    ui->listWidget->clear();
    ui->weight->setValue(150);
    ui->elevator_screen->setText("E1");
    ui->floor_screen->setText(QString::number(e->getLevel()));
    updateDisplayE1(QString::number(e->getLevel()));
}

void MainWindow::blockDoor(){
    updateConsole(e->playAudio("E1 Audio: Please allow the doors to close."));
    updateDisplayE1(e->displayItem("E1 Display System: Please allow the doors to close."));
    updateConsole("E1: " + e->ringBell());
    updateConsole("E1: " + e3->openDoor());

    updateConsole("End of BLOCK DOOR segment.\n\n");
}

void MainWindow::level1(){sendLevel(e, 1);}
void MainWindow::level2(){sendLevel(e, 2);}
void MainWindow::level3(){sendLevel(e, 3);}
void MainWindow::level4(){sendLevel(e, 4);}
void MainWindow::level5(){sendLevel(e, 5);}
void MainWindow::level6(){sendLevel(e, 6);}
void MainWindow::level7(){sendLevel(e, 7);}

void MainWindow::requestF1(){
    //send elevator to its level
    sendLevel(e2, l1->getId());
    // send elevator to random level
    int newFloor = rand() % (7 + 1 - 2) + 2;
    updateConsole("F1 requested an elevator, E2 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e2, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF7(){
    //send elevator to its level
    sendLevel(e3, l7->getId());
    // send elevator to random level
    int newFloor = rand() % 7;
    updateConsole("F7 requested an elevator, E3 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e3, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF2_up(){
    //send elevator to its level
    sendLevel(e2, l2->getId());
    // send elevator to random level
    int newFloor = rand() % (7 + 1 - 3) + 3;
    updateConsole("F2 requested an elevator, E2 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e2, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF2_down(){
    //send elevator to its level
    sendLevel(e2, l2->getId());
    // send elevator to random level
    int newFloor = 1;
    updateConsole("F2 requested an elevator, E2 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e2, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF3_up(){
    //send elevator to its level
    sendLevel(e2, l3->getId());
    // send elevator to random level
    int newFloor = rand() % (7 + 1 - 4) + 4;
    updateConsole("F3 requested an elevator, E2 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e2, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF3_down(){
    //send elevator to its level
    sendLevel(e2, l3->getId());
    // send elevator to random level
    int newFloor = rand() % (2  + 1 - 1) + 1;;
    updateConsole("F3 requested an elevator, E2 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e2, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF4_up(){
    //send elevator to its level
    sendLevel(e2, l4->getId());
    // send elevator to random level
    int newFloor = rand() % (7 + 1 - 5) + 5;
    updateConsole("F4 requested an elevator, E2 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e2, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF4_down(){
    //send elevator to its level
    sendLevel(e2, l4->getId());
    // send elevator to random level
    int newFloor = rand() % (3  + 1 - 1) + 1;;
    updateConsole("F4 requested an elevator, E2 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e2, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF5_up(){
    //send elevator to its level
    sendLevel(e3, l5->getId());
    // send elevator to random level
    int newFloor = rand() % (7 + 1 - 6) + 6;
    updateConsole("F5 requested an elevator, E3 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e3, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF5_down(){
    //send elevator to its level
    sendLevel(e3, l5->getId());
    // send elevator to random level
    int newFloor = rand() % (4  + 1 - 1) + 1;;
    updateConsole("F5 requested an elevator, E3 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e3, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF6_up(){
    //send elevator to its level
    sendLevel(e3, l6->getId());
    // send elevator to random level
    int newFloor = 7;
    updateConsole("F6 requested an elevator, E3 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e3, newFloor);
    updateConsole("\n\n,");
}

void MainWindow::requestF6_down(){
    //send elevator to its level
    sendLevel(e3, l6->getId());
    // send elevator to random level
    int newFloor = rand() % (5  + 1 - 1) + 1;;
    updateConsole("F6 requested an elevator, E3 arrives -- going to F" + QString::number(newFloor));
    sendLevel(e3, newFloor);
    updateConsole("\n\n,");
}
