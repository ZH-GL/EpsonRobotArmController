#include "MouseZoomImage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MouseZoomImage w;
	w.show();
    return a.exec();
}
