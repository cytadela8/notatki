#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDir>
#include <QGuiApplication>
#include <QScreen>
#include <QStandardPaths>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "noteeditor.h"
#include "sidemenu.h"
#include "touchbutton.h"

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
private:
    NoteEditor *center;
    QWidget *top;
    SideMenu *side_menu;
};

#endif // MAINVIEW_H
