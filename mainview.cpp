#include "mainview.h"

#include <QDebug>

MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    //Some basic layout for debugging

    setLayout( new QVBoxLayout() );

    //Top bar with buttons

    top = new QWidget( this );
    top -> setLayout( new QHBoxLayout( top ) );

    TouchButton *button = new TouchButton("#");

    connect( button, &TouchButton::clicked, [=](){ qDebug()<<"#"; side_menu->open(); } );
    top -> layout() -> addWidget( button );
    static_cast<QHBoxLayout*>( top -> layout() ) -> addStretch( 1 );

    button = new TouchButton("1");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"1";} );
    top -> layout() -> addWidget( button );

    button = new TouchButton("2");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"2";} );
    top -> layout() -> addWidget( button );

    button = new TouchButton("3");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"3";} );
    top -> layout() -> addWidget( button );

    layout() -> addWidget( top );


    //Center widget with QTextEdit

    center = new QWidget( this );
    center -> setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Expanding );
    center -> setLayout( new QGridLayout( center ) );
    center -> layout() -> addWidget( new QTextEdit() );
    layout() -> addWidget( center );


    //Side menu

    side_menu = new SideMenu( this );
    side_menu -> setLayout( new QVBoxLayout( side_menu ) );

    button = new TouchButton("a");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"a";} );
    side_menu -> layout() -> addWidget( button );

    static_cast<QVBoxLayout*>( side_menu -> layout() ) -> addStretch( 1 );

    button = new TouchButton("b");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"b";} );
    side_menu -> layout() -> addWidget( button );

    button = new TouchButton("c");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"c";} );
    side_menu -> layout() -> addWidget( button );

    button = new TouchButton("d");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"d";} );
    side_menu -> layout() -> addWidget( button );
}



