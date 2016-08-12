#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QWidget>
#include <QLayout>
#include <QTextEdit>
#include "note.h"

class NoteEditor : public QWidget
{
    Q_OBJECT
public:
    explicit NoteEditor(QWidget *parent = 0);
    ~NoteEditor();
    Note *current_note;
    QTextEdit *note_edit;
signals:

public slots:
    bool saveCurrent();
    bool load( QString name );
    void removeCurrent();
};

#endif // NOTEEDITOR_H
