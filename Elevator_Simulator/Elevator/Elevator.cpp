#include "Elevator.h"
#include <QObject>
#include <QTextStream>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

Elevator::Elevator(int num, QObject *parent) : id(num), QObject(parent){
}

Elevator::~Elevator(){}


bool Elevator::setLevel(int l){
   if (l == getLevel()){
       displayItem("You are already on this floor");
       return false;
   } else if (l > 7 || l < 1){
       displayItem("Level is not applicable");
       return false;
   } else {
       level = l;
       return true;
   }

}
void Elevator::setDoorState(QString state){
    doorState = state;
}
int Elevator::getLevel(){
   return level;
}
int Elevator::getId(){
    return id;
}
QString Elevator::getDoorState(){
    return doorState;
}
QString Elevator::ringBell(){
    return playAudio("**RING RING**");
}
QString Elevator::playAudio(QString audio){
    return audio;
}
QString Elevator::displayItem(QString item){
    return item;
}
QString Elevator::openDoor(){
    if (doorState == "closed"){
        setDoorState("open");
        return "Elevator door opens.";
    }
    return "Doors already open.";
}
QString Elevator::closeDoor(){
    if (doorState == "open"){
        setDoorState("closed");
        return "Elevator door closes.";
    }
    return "Doors already closed.";
}

