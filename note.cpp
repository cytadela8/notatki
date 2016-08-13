#include "note.h"

#include <QDebug>

Note::Note()
{
    std::mt19937_64 random( std::hash<std::string>()( QUuid::createUuid().toString().toStdString() ) + QDateTime::currentDateTime().toMSecsSinceEpoch() );
    id = QString::number( random() );
}

bool Note::save()
{
    QString filename( id );
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + filename;
    QFile file(path);
    if( file.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ) )
    {
        QTextStream out( &file );
        out << contents;
        qDebug() << "saving note: " << filename;
        return true;
    }
    else
        return false;
}

bool Note::load( QString name ) //na cholerę mi ten bóól...
{
    QFile file( QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + name );
    if( !file.exists() )
        return false;
    id = name;
    contents = QString();
    if( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QTextStream in( &file );
        while ( !in.atEnd() )
        {
            QString line = in.readLine();
            contents += line;
        }
        qDebug() << "loading note: " << name;
        return true;
    }
    else
        return false;
}

void Note::remove()
{
    QString filename( id );
    qDebug() << "removing note: " << filename;
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + filename;
    QFile file(path);
    if( file.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ) )
        file.remove();
    contents = QString();
}
