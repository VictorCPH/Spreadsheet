#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/splash.png"));
    splash->show();
    splash->showMessage(QObject::tr("Setting up the main window..."),
                        Qt::AlignRight|Qt::AlignTop, Qt::white);

    MainWindow * mainWin = new MainWindow;
    QTime t;
    t.start();
    while(t.elapsed()<1200);

    mainWin->show();
    splash->finish(mainWin);
    delete splash;
    return a.exec();
}
