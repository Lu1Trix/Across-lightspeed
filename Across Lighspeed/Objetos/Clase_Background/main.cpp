#include "background.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    background w;
    w.show();
    return a.exec();
}
