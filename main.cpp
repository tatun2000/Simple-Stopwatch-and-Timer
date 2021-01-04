#include "mainwindow.h"
#include "secondwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SecondWindow sw;
    w.show();
    QObject::connect(&w, SIGNAL(Window1_Close()), &sw, SLOT(Window2_Show())); //Sending the window1_close signal from
                                                                              //the first form to the second form
                                                                              //in the window2_show slot()

    QObject::connect(&sw, SIGNAL(Window2_Close()), &w, SLOT(Show_Window()));   //Sending the window2_close signal from
                                                                               //the second form to the first form
                                                                               //in the show_window slot()
    return a.exec();
}
