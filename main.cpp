#include "mainview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    new MainView();

    return a.exec();
}

class Alfred
{
private:
    int x, y;
public:
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    void set_x( int new_x )
    {
        x = new_x;
    }
    void set_y( int new_y )
    {
        y = new_y;
    }
};
