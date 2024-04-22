#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <QtCore/QObject>

class Level : public QObject{
    Q_OBJECT

public:
    explicit Level(int, QObject *parent = 0);
    ~Level();

    int getId();

private:
    int id;
};

#endif // LEVEL_H
