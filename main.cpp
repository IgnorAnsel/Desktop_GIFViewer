#include "gifviewer.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GIFViewer viewer;
    viewer.show();
    return a.exec();
}
