#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_3->setVisible(false);
    ui->pushButton_2->setEnabled(false);

    timer = new QTimer(); // Pointer to the QTimer for the stopwatch function

    temp_timer = new QTimer(); // Pointer to the QTimer to count the ms that
                               // have passed since the application was launched
    connect(temp_timer, SIGNAL(timeout()), this, SLOT(Substract_Time())); // Sending a timeout()
                                                                          //signal to the Substract_Time() slot
    temp_timer->setInterval(1000); // Set the interval = 1000 ms
    temp_timer->start();

    main_timer = new QTimer(); // Pointer to the QTimer for real-time display
    connect(main_timer, SIGNAL(timeout()), this, SLOT(Main_Times())); // Sending a timeout()
                                                                      //signal to the Main_Times() slot
    main_timer->start(1000);
    c.start();
    main_q_timer.start();

    b.start();
    ui->label_time->setText("00:00:00");
}



MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete temp_timer;
    delete main_timer;
}

// Slot where the stopwatch is displayed on the screen
void MainWindow::Update_Time()
{
    a = a.addMSecs(qtimer.restart());
    ui->label_time->setText((a).toString("hh:mm:ss"));
}

// Slot in which the number of ms is calculated from the moment the application is launched
void MainWindow::Substract_Time()
{
    res += temp_timer->interval();
}

// A slot where real time is displayed on the screen
void MainWindow::Main_Times()
{
    c = c.addMSecs(main_q_timer.restart());
    ui->label->setText((c).toString("hh:mm:ss"));
}

// Slot for displaying a window on the screen
void MainWindow::Show_Window()
{
    MainWindow::show();
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setEnabled(true);
    timer->start(1000);
    a.start();
    qtimer.start();
    a = a - b - res; // To start the countdown from 00:00:00 by the time the stopwatch starts.
                     // (The operator is overloaded for this operation "-")
    connect(timer, SIGNAL(timeout()), this, SLOT(Update_Time())); // Sending a timeout()
                                                                  //signal to the Update_Time() slot
}

QTime operator -( const QTime & t1, const QTime & t2 )
{
    int diff = t2.msecsTo(t1);
    return QTime(diff / HOUR_MS,
                (diff % HOUR_MS) / MIN_MS,
                (diff % MIN_MS) / SEC_MS,
                 diff % SEC_MS);
};

QTime operator -(const QTime & t1, const int & t2 )
{
    int t_temp1 = t1.hour();
    int t_temp2 = t1.minute();
    int t_temp3 = t1.second();
    int t_temp4 = t1.msec();
    return QTime(t_temp1 - (t2/HOUR_MS),
                 t_temp2 - ((t2 % HOUR_MS) / MIN_MS),
                 t_temp3 - ((t2 % MIN_MS) / SEC_MS),
                 t_temp4 - (t2 % SEC_MS));
};

void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_3->setVisible(true);
    if (ui->pushButton_2->text() == "Reset")
    {
        ui->label_time->setText((c).toString("00:00:00"));
        ui->pushButton_2->setText("Stop");
        timer->stop();
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setVisible(false);
        return;
    }
    if (timer->isActive())
    {
        timer->setInterval(0);
        ui->pushButton_2->setText("Reset");
        return;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setVisible(false);
    ui->pushButton_2->setText("Stop");
    timer->setInterval(1000);
}

void MainWindow::on_action_2_triggered()
{
    hide();
    emit Window1_Close();
}


