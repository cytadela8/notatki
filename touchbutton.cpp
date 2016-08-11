#include "touchbutton.h"
#include <QDebug>

TouchButton::TouchButton( QWidget *parent ) : QPushButton( parent )
{
    setAttribute( Qt::WA_AcceptTouchEvents, true );
}

TouchButton::TouchButton( const QString &text, QWidget *parent ) : QPushButton( text, parent )
{
    setAttribute( Qt::WA_AcceptTouchEvents, true );
}

TouchButton::TouchButton( const QIcon &icon, const QString &text, QWidget *parent ) : QPushButton( icon, text, parent )
{
    setAttribute( Qt::WA_AcceptTouchEvents, true );
}

bool TouchButton::event( QEvent *event )
{
    switch( event->type() )
    {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        {
            bool event_handled = false;

            QList<QTouchEvent::TouchPoint> touch_points = static_cast<QTouchEvent*>(event)->touchPoints();
            foreach (const QTouchEvent::TouchPoint &touch_point, touch_points)
            {
                if( hitButton( touch_point.pos().toPoint() ) )
                {
                    event_handled = true;
                    setFocus( Qt::MouseFocusReason );

                    switch( touch_point.state() )
                    {
                        case Qt::TouchPointPressed:
                        {
                            setDown(true);
                            emit pressed();
                            break;
                        }
                        case Qt::TouchPointReleased:
                        {
                            if( isDown() )
                            {
                                emit clicked();
                                setDown(false);
                            }
                            break;
                        }
                        case Qt::TouchPointMoved:
                        case Qt::TouchPointStationary:
                        {
                            if( hitButton( touch_point.startPos().toPoint() ) )
                                setDown(true);
                            break;
                        }
                    }
                }
                else
                {
                    emit released();
                    setDown(false);
                    clearFocus();
                }
            }

            if( !event_handled )
                event->ignore();

            return event_handled;
        }
        default:
            return QPushButton::event( event );
    }
}
