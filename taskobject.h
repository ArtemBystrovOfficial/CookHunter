#ifndef TASKOBJECT_H
#define TASKOBJECT_H

#include <QObject>

class Taskobject : public QObject
{
    Q_OBJECT
public:
    explicit Taskobject(QObject *parent = nullptr);

signals:

};

#endif // TASKOBJECT_H
