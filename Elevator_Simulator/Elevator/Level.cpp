#include "Level.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


Level::Level(int num, QObject *parent) : id(num), QObject(parent){}
Level::~Level(){}


int Level::getId(){return id;}
