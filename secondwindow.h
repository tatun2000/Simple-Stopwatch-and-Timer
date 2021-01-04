#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QMessageBox>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void Window2_Close(); // Signal to close second windows

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

public slots:
    void Window2_Show();       // Slot for displaying the second window
    void Main_Times_sw();      // A slot where real time is displayed on the screen
    void Timer_Update();       // Slot for timer operation

private slots:
    void on_action_triggered();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::SecondWindow *ui;
    QTimer *timer1_sw;
    QTime time1_sw = QTime::currentTime();
    QElapsedTimer qtimer1_sw;
    QTimer *timer2_sw;
};

#endif // SECONDWINDOW_H
