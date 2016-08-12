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

    button = new TouchButton("Save");
    connect( button, &TouchButton::clicked, [this](){center->saveCurrent();} );
    top -> layout() -> addWidget( button );

    button = new TouchButton("Delete"); //maybe some kind of confirmation dialog pls?
    connect( button, &TouchButton::clicked, [this](){center->removeCurrent();} );
    top -> layout() -> addWidget( button );

    button = new TouchButton("Refresh");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"3";} );
    top -> layout() -> addWidget( button );

    layout() -> addWidget( top );


    //Center widget with QTextEdit

    center = new NoteEditor( this );
    center -> setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout() -> addWidget( center );


    //Side menu

    side_menu = new SideMenu( this );
    side_menu -> setLayout( new QVBoxLayout( side_menu ) );

    button = new TouchButton("a");
    connect( button, &TouchButton::clicked, [=](){qDebug()<<"a";} );
    side_menu -> layout() -> addWidget( button );

    static_cast<QVBoxLayout*>( side_menu -> layout() ) -> addStretch( 1 );

    QDir note_dir( QStandardPaths::writableLocation(QStandardPaths::AppDataLocation ) );
    qDebug() << note_dir.exists();
    qDebug() << note_dir.path();
    note_dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    note_dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = note_dir.entryInfoList();
    qDebug() << "     Bytes Filename";
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        qDebug() << QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName());

        button = new TouchButton( fileInfo.fileName() );
        connect( button, &TouchButton::clicked, [this, fileInfo](){ center->load( fileInfo.fileName() ); } );
        side_menu -> layout() -> addWidget( button );
    }
    //Yeah, well, THIS SHOULD BE UPDATED EVERY ONCE IN A WHILE Y'KNOW
    //LIKE GOD DAMN THERE SHOULD BE SOMETHING SYNCING THIS TO THE CURRENT NOTE LIST OR SOMETHING I DON'T KNOW
    //OR MAYBE RECONSTRUCT IT EVERYTIME SOMETHING CHANGES, BUT HOW?


    //Ok, so i make a refresh slot in MainView
    //Make NoteEditView as a new widget on top of this one (which will HOPEFULLY work, oh wait it won't, because sidebar, shit
    //Ok so i need to KILL MainView
    //Then how do I connect the Views?
    //Perhaps the only way to do it is manually in each view define which view creates which.
    //I can do "delete this" and create a new view without a parent, seems pretty legit if you ask me
    //Then I wouldn't have any need for refreshing the MainView note list, since it would be constructed from anew every time!
}



