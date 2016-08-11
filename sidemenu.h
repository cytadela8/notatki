#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QApplication>
#include <QElapsedTimer>
#include <QPropertyAnimation>
#include <QTouchEvent>
#include <QWidget>

class SideMenu : public QWidget
{
    Q_OBJECT

public:

    explicit SideMenu(QWidget *parent = 0);

    //Filters:
    //Touch events for any object
    //Resize events for the parent
    //Should be set up to filter from qApp
    bool eventFilter(QObject *object, QEvent *event);

private:

    //Changes the size of the menu to match the QWidget::window()->width()
    //Is called after a resize event
    void rescale();

    void shift( int dif_x ); //Shifts the menu right by dif_x pixels

    bool is_open;
    bool is_dragged;

    QPropertyAnimation *animation;

    const int kAnimLengthMs = 250; //Default length of the opening/closing animation
    const double kMenuWidthScreenPercentage = .80; //Percentage of the screen width that the menu takes up
    const double kDropThresholdWidthPercentage = .25; //Percentage of the menu width that the menu has to be moved by in order to open or close it
    const double kSideGrabZoneScreenPercentage = .10; //Percentage of the screen width (on the left side) where menu reacts to touchevents when closed
    const double kMinimalSwipeScreenPercentage = .05; //Percentage of the screen width that the touch event has to move before the menu reacts

public slots:
    void close();
    void open();
    void drop(); //Opens or closes the menu, depending on its position on screen
};

#endif // SIDEMENU_H
