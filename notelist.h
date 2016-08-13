#ifndef NOTELIST_H
#define NOTELIST_H

#include <QScrollArea>
#include <QLayout>
#include <QDir>
#include <QStandardPaths>

#include "touchbutton.h"

class NoteList : public QScrollArea
{
    Q_OBJECT
public:
    explicit NoteList(QWidget *parent = 0);

signals:
    void openNote( QString filename = QString() );

public slots:
};

#endif // NOTELIST_H
