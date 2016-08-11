#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGuiApplication>
#include <QScreen>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "sidemenu.h"
#include "touchbutton.h"

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
private:
    QWidget *center;
    QWidget *top;
    SideMenu *side_menu;
};

#endif // MAINVIEW_H
