#ifndef NOTEEDITVIEW_H
#define NOTEEDITVIEW_H

#include <QDir>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>
#include <QStandardPaths>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "mainview.h"
#include "noteeditor.h"
#include "sidemenu.h"
#include "touchbutton.h"

class NoteEditView : public QWidget
{
    Q_OBJECT
public:
    explicit NoteEditView(QWidget *parent = 0, QString note_filename = QString());
    explicit NoteEditView(QString note_filename) : NoteEditView( 0, note_filename ) {}
    ~NoteEditView();
    void keyReleaseEvent(QKeyEvent * event);
private:
    NoteEditor *center;
    QWidget *top;
    SideMenu *side_menu;

signals:

public slots:
};

#endif // NOTEEDITVIEW_H
