#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QString>
#include <QtCore/QObject>

class Elevator : public QObject{
    Q_OBJECT

public:
    explicit Elevator(int, QObject *parent = 0);
    //explicit Elevator(int num, QString as, QString ds, QObject *parent = 0);/
    ~Elevator();


private:
    int id;
    int level = 1;
    QString doorState = "closed";
//    QString sensor;
//    QString audioSystem;
//    QString displaySystem;

//  Button levelBtns;
//  Button openCloseBtns;
//  Button helpBtns;
//  Door door;

signals:
    void somethingHappen();

public slots:
    QString ringBell();
    QString displayItem(QString);
    QString playAudio(QString);
    QString openDoor();
    QString closeDoor();

public:
    bool setLevel(int);
    void setDoorState(QString);
    int getLevel();
    int getId();
    QString getDoorState();
};

#endif // ELEVATOR_H
