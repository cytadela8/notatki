#include "notelist.h"

NoteList::NoteList(QWidget *parent) : QScrollArea(parent)
{
    setWidgetResizable( true );
    setBackgroundRole(QPalette::Dark);
    QWidget *list = new QWidget();
    list -> setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    list->setLayout( new QVBoxLayout( list ) );

    TouchButton *button = new TouchButton( "+ New Note" );
    button -> setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
    connect( button, &TouchButton::clicked, [this](){ emit openNote(); } );
    list->layout()->addWidget( button );
    static_cast<QVBoxLayout*>(list->layout())->addSpacing( 20 );

    QDir note_dir( QStandardPaths::writableLocation(QStandardPaths::AppDataLocation ) );
    note_dir.setFilter( QDir::Files );
    note_dir.setSorting( QDir::Time );
    QFileInfoList file_list = note_dir.entryInfoList();
    for (int i = 0; i < file_list.size(); ++i)
    {
        QFileInfo fileInfo = file_list.at(i);

        button = new TouchButton( fileInfo.fileName() );
        button -> setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
        connect( button, &TouchButton::clicked, [this, fileInfo](){ emit openNote( fileInfo.fileName() ); } );
        list->layout()->addWidget( button );
    }
    static_cast<QVBoxLayout*>(list->layout())->addStretch( 1 );

    setWidget(list);
}
