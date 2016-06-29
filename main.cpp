#include "guicalulatrice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUICalulatrice calculette;
    calculette.show();

    return a.exec();
}

