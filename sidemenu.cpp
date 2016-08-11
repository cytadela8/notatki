#include "sidemenu.h"
#include <QDebug>

SideMenu::SideMenu(QWidget *parent) : QWidget(parent)
{
    qApp->installEventFilter( this );

    is_open = false;
    is_dragged = false;

    animation = new QPropertyAnimation(this, "pos");

    rescale();
    show();
    close();
}

void SideMenu::open()
{
    is_dragged = false;
    is_open = true;
    raise();
    double duration_modifier = static_cast<double>( -x() ) / width();
    animation->setDuration( kAnimLengthMs * duration_modifier ); //TODO: touch velocity?
    animation->setStartValue( QPoint( x(), 0 ) );
    animation->setEndValue( QPoint( 0, 0 ) );
    animation->start();
}

void SideMenu::close()
{
    is_dragged = false;
    is_open = false;
    double duration_modifier = static_cast<double>( width() + x() ) / width();
    animation->setDuration( kAnimLengthMs * duration_modifier ); //TODO: touch velocity?
    animation->setStartValue( QPoint( x(), 0 ) );
    animation->setEndValue( QPoint( -width(), 0 ) );
    animation->start();
}

void SideMenu::drop()
{
    double drop_threshold = kDropThresholdWidthPercentage;
    if( is_open == false )
        drop_threshold = 1 - drop_threshold;

    if( x() > -width() * drop_threshold )
        open();
    else
        close();
}

//TODO: interpolate position to reduce jumpy movement
void SideMenu::shift( int dif_x )
{
    int new_x = x() + dif_x;
    new_x = qBound( -width(), new_x, 0 );
    move( new_x, 0 );
}

void SideMenu::rescale()
{
    animation->stop();

    int menu_width = QWidget::window()->width() * kMenuWidthScreenPercentage;

    if( is_open )
        setGeometry( 0, 0, menu_width, QWidget::window()->height() );
    else
        setGeometry( -menu_width, 0, menu_width, QWidget::window()->height() );
}


bool SideMenu::eventFilter(QObject *object, QEvent *event)
{
    switch( event->type() )
    {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        {
            if( is_dragged )
            {
                int dif_x_last = 0;
                bool all_fingers_released = true;
                QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent*>(event)->touchPoints();
                foreach( const QTouchEvent::TouchPoint &touchPoint, touchPoints )
                {
                    dif_x_last += touchPoint.pos().x() - touchPoint.lastPos().x();
                    if( touchPoint.state() != Qt::TouchPointReleased )
                        all_fingers_released = false;
                }
                if( event->type() == QEvent::TouchEnd && all_fingers_released )
                    drop();
                else
                    shift( dif_x_last );

                return true;
            }
            else if( is_open )
            {
                bool close_menu = true;

                int dif_x_start = 0;
                QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent*>(event)->touchPoints();
                foreach( const QTouchEvent::TouchPoint &touchPoint, touchPoints )
                {
                    dif_x_start += touchPoint.pos().x() - touchPoint.startPos().x();
                    if( touchPoint.state() != Qt::TouchPointReleased || geometry().contains( touchPoint.pos().toPoint() ) )
                        close_menu = false;
                }

                if( abs( dif_x_start ) > kMinimalSwipeScreenPercentage * QWidget::window()->width() )
                    is_dragged = true;

                if( close_menu )
                    close();

                return is_dragged || close_menu;
            }
            else //Check if the left side of the window was grabbed
            {
                QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent*>(event)->touchPoints();
                foreach( const QTouchEvent::TouchPoint &touchPoint, touchPoints )
                    if( touchPoint.screenPos().x() < kSideGrabZoneScreenPercentage * QWidget::window()->width() && touchPoint.lastPos() != touchPoint.pos() )
                        is_dragged = true;

                return is_dragged;
            }
        }

        case QEvent::Resize:
        {
            if( object == parent() )
                rescale();
            return false;
        }

        default:
            return false;
    }
}
