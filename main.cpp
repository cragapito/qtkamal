#include <QApplication>
#include "qtkamal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList args = a.arguments();

    qtkamal w;
    w.args( args );
    w.show();
    
    return a.exec();
}
