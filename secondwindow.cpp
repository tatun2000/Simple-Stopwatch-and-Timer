#include "secondwindow.h"
#include "ui_secondwindow.h"


SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setVisible(false);

    timer1_sw = new QTimer(); // Pointer to the QTimer for real-time display
    connect(timer1_sw, SIGNAL(timeout()), this, SLOT(Main_Times_sw())); // Sending a timeout()
                                                                         //signal to the Main_Times_sw() slot

    timer1_sw->start(1000); // Start the timer with an interval of 1000 ms
    time1_sw.start();
    qtimer1_sw.start();

    timer2_sw = new QTimer(); // Pointer to the QTimer for our timer to work
    timer2_sw->setInterval(1000); // Set the interval = 1000 ms
    connect(timer2_sw, SIGNAL(timeout()), this, SLOT(Timer_Update())); // Sending a timeout()
                                                                        //signal to the Timer_Update()slot
}
SecondWindow::~SecondWindow()
{
    delete ui;
    delete timer1_sw;
    delete timer2_sw;
}

// Slot for displaying the second window
void SecondWindow::Window2_Show()
{
    SecondWindow::show();
}

void SecondWindow::on_action_triggered()
{
    hide();
    emit Window2_Close(); // Forming a signal
}

// A slot where real time is displayed on the screen
void SecondWindow::Main_Times_sw()
{
    time1_sw = time1_sw.addMSecs(qtimer1_sw.restart());
    ui->label_2->setText((time1_sw).toString("hh:mm:ss"));
}

// Slot for timer operation
void SecondWindow::Timer_Update()
{
    if (ui->spinBox->value() == 0 && ui->spinBox_2->value() == 0 && ui->spinBox_3->value() == 0) // The timer has finished working
    {
        timer2_sw->stop();
        QMessageBox::information(this, "Uh-huh", "The timer worked successfully");
        return;
    }
    if (ui->spinBox_3->value() == 0)
    {
        ui->spinBox_3->setVisible(false);
    }
    if (ui->spinBox->value() == 0 && ui->spinBox_2->value() != 0) // The minute ended
    {
        ui->spinBox->setValue(ui->spinBox->value() + 59);
        ui->spinBox_2->setValue(ui->spinBox_2->value()- 1);
        return;
    }
    if (ui->spinBox->value() == 0 && ui->spinBox_2->value() == 0 && ui->spinBox_3->value() != 0) // The hour was over
    {
        ui->spinBox->setValue(ui->spinBox->value() + 59);
        ui->spinBox_2->setValue(ui->spinBox_2->value() + 59);
        ui->spinBox_3->setValue(ui->spinBox_3->value()- 1);
        return;
    }
    if (ui->spinBox->value() != 0)
    {
        ui->spinBox->setValue(ui->spinBox->value() - 1);
        return;
    }
}

void SecondWindow::on_pushButton_2_clicked()
{
    if (ui->spinBox->value() == 0 && ui->spinBox_2->value() == 0 && ui->spinBox_3->value() == 0)
    {
        QMessageBox::warning(this, "Warning", "The timer value is not set!");
        return;
    }
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(true);

    ui->spinBox->setEnabled(false);
    ui->spinBox_2->setEnabled(false);
    ui->spinBox_3->setEnabled(false);
    timer2_sw->start();
}

void SecondWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_3->setText("Pause");

    timer2_sw->stop();
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);

    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->spinBox_3->setEnabled(true);
    if (ui->spinBox_3->isVisible() == false)
    {
        ui->spinBox_3->setVisible(true);
    }

}

void SecondWindow::on_pushButton_3_clicked()
{
    if (timer2_sw->isActive())
    {
        timer2_sw->stop();
        ui->pushButton_3->setText("Continue");
        return;
    }
    else
    {
        timer2_sw->start();
        ui->pushButton_3->setText("Pause");
        return;
    }
}
