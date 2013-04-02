#include <QApplication>
#include "qtkamal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtkamal w;
    w.show();
    
    return a.exec();
}
