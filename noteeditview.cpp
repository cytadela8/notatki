#include "noteeditview.h"

#include <QDebug>

NoteEditView::NoteEditView(QWidget *parent, QString note_filename) : QWidget(parent)
{
    //Some basic layout for debugging

    setLayout( new QVBoxLayout( this ) );

    //Top bar with buttons

    top = new QWidget( this );
    top -> setLayout( new QHBoxLayout( top ) );

    TouchButton *button = new TouchButton("#");

    connect( button, &TouchButton::clicked, [this](){ side_menu->open(); } );
    top -> layout() -> addWidget( button );
    static_cast<QHBoxLayout*>( top -> layout() ) -> addStretch( 1 );

    button = new TouchButton("Save");
    connect( button, &TouchButton::clicked, [this](){ center->saveCurrent(); } );
    top -> layout() -> addWidget( button );

    //maybe some kind of confirmation dialog pls?
    button = new TouchButton("Delete");
    connect( button, &TouchButton::clicked, [this](){ center->removeCurrent(); } );
    top -> layout() -> addWidget( button );

    layout() -> addWidget( top );


    //Center widget with QTextEdit

    center = new NoteEditor( this );
    center -> setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout() -> addWidget( center );
    if( !note_filename.isEmpty() )
        center->load(note_filename);

    //Side menu

    side_menu = new SideMenu( this );
    side_menu -> setLayout( new QVBoxLayout( side_menu ) );
    side_menu -> layout() -> addWidget( new QLabel( "Tags" ) );
    //TAGLIST WILL BE HERE


    show();
}

NoteEditView::~NoteEditView()
{
    new MainView();
}

void NoteEditView::keyReleaseEvent(QKeyEvent * event)
{
    if( event->key() == Qt::Key_Back )
        deleteLater();
    else
        QWidget::keyReleaseEvent( event );
}
