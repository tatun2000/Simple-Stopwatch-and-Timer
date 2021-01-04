#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SEC_MS  1000
#define MIN_MS	(SEC_MS * 60)
#define HOUR_MS	(MIN_MS * 60)

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void Window1_Close(); // Signal to close the first form

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void Update_Time();     // Slot where the stopwatch is displayed on the screen
    void Substract_Time();  // Slot in which the number of ms is calculated
                            //from the moment the application is launched

    void Main_Times();      // A slot where real time is displayed on the screen
    void Show_Window();     // Slot for displaying a window on the screen
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QTimer *temp_timer;
    QTimer *main_timer;

    QTime a;
    QTime b = QTime::currentTime();
    QTime c = QTime::currentTime();

    QElapsedTimer qtimer;
    QElapsedTimer main_q_timer;

    int res = 0; // Variable for counting the ms that have
                 //passed since the program was launched
};

// Overloads of the " - " operator as free functions
QTime operator -( const QTime & t1, const QTime & t2 );
QTime operator -(const QTime & t1, const int & t2 );

#endif // MAINWINDOW_H
