#include "noteeditor.h"

#include <QDebug>

NoteEditor::NoteEditor(QWidget *parent) : QWidget(parent)
{
    setLayout( new QGridLayout( this ) );
    note_edit = new QTextEdit();
    layout() -> addWidget( note_edit );
    current_note = new Note();
}

NoteEditor::~NoteEditor()
{
    saveCurrent();
    delete current_note;
}

bool NoteEditor::saveCurrent()
{
    current_note->contents = note_edit->toPlainText();
    qDebug() << current_note->contents;
    if( !current_note->contents.isEmpty() )
        return current_note->save();
    else
        return false;
}
bool NoteEditor::load( QString name )
{
    if( !current_note->contents.isEmpty() )
        current_note->save();

    if( current_note->load( name ) )
    {
        note_edit->clear();
        note_edit->setPlainText( current_note->contents );
        return true;
    }
    else
    {
        note_edit->clear();
        return false;
    }
}

void NoteEditor::removeCurrent()
{
    current_note->remove();
    note_edit->clear();
}
