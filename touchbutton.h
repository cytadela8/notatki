#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

/*
TouchButton
A button class subclassing QPushButton to handle touch events.
*/

#include <QPushButton>
#include <QTouchEvent>

class TouchButton : public QPushButton
{
    Q_OBJECT

public:

    explicit TouchButton( QWidget *parent = Q_NULLPTR );
    explicit TouchButton( const QString &text, QWidget *parent = Q_NULLPTR );
    explicit TouchButton( const QIcon &icon, const QString &text, QWidget *parent = 0 );

protected:

    bool event( QEvent *event ); //Handles QEvent::TouchBegin, QEvent::TouchUpdate and QEvent::TouchEnd type events
};

#endif // TOUCHBUTTON_H
