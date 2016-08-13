#include "mainview.h"

#include <QDebug>

MainView::MainView(QWidget *parent)
    : QWidget(parent)
{
    //Some basic layout for debugging

    setLayout( new QVBoxLayout( this ) );

    //Top bar with buttons

    top = new QWidget( this );
    top -> setLayout( new QHBoxLayout( top ) );

    TouchButton *button = new TouchButton("#");

    top -> layout() -> addWidget( button );
    static_cast<QHBoxLayout*>( top -> layout() ) -> addStretch( 1 );

    //button = new TouchButton("NoteEditView");
    //connect( button, &TouchButton::clicked, [this](){ deleteLater(); new NoteEditView(); } );
    //top -> layout() -> addWidget( button );

    layout() -> addWidget( top );


    //Center widget with QTextEdit

    center = new NoteList( this );
    center -> setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout() -> addWidget( center );
    connect( center, &NoteList::openNote, [this]( QString filename ){ deleteLater(); new NoteEditView(filename); } );


    //Side menu

    side_menu = new SideMenu( this );
    connect( button, &TouchButton::clicked, side_menu, &SideMenu::open ); //This has to be done after side_menu is created (unless done with a lambda)
    side_menu -> setLayout( new QVBoxLayout( side_menu ) );

    button = new TouchButton("Debug #1");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"Debug #1 clicked!";} );
    side_menu -> layout() -> addWidget( button );

    static_cast<QVBoxLayout*>( side_menu -> layout() ) -> addStretch( 1 );

    button = new TouchButton("Debug #2");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"Debug #2 clicked!";} );
    side_menu -> layout() -> addWidget( button );
    button = new TouchButton("Debug #3 with a super long name that will almost certainly NOT fit into the side menu width and therefore will let me see what happens in that case");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"Debug #3 clicked!";} );
    side_menu -> layout() -> addWidget( button );



    show();
}



