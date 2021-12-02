#include "paint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    paint w;
    w.setWindowTitle("Paint");
    w.setWindowIcon(QIcon(":/tools/favicon.png"));
    w.show();
    return a.exec();
}
