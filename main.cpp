#include "videogui.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    videoGUI w;
    w.show();

    QApplication::setQuitOnLastWindowClosed(true);
    QCoreApplication::exit();
    return a.exec();
}
