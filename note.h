#ifndef NOTE_H
#define NOTE_H

#include <QFile>
#include <random>
#include <QDir>
#include <QUuid>
#include <functional>
#include <QDateTime>
#include <QStandardPaths>
#include <QTextStream>

class Note
{
public:
    Note();
    ~Note();
    QString id;
    QString contents;
public slots:
    bool save();
    bool load( QString name );
    void remove();
};

#endif // NOTE_H
