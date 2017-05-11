/**
*
* ENTER key doesn't work either...
*
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
    operStr = "";
    ui->lineEdit->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot2(QString x)
{
    operStr = x.toStdString();
}

void MainWindow::setLineEdit(const char * str)
{
    operStr += str;
    ui->lineEdit->setText(operStr.c_str());
}

void MainWindow::resetLineEdit()
{
    operStr = "";
    ui->lineEdit->setText("");
}

void MainWindow::slotCopy()
{
    QApplication::clipboard()->setText(operStr.c_str());
}

void MainWindow::slotEnter()
{
    // change all ',' to '.'
    for (int i = 0; i < operStr.size(); i++)
    {
        if (operStr[i] == ',')
            operStr[i] = '.';
    }

    // just because it's fun...
    if (operStr == "42") {
        ui->lineEdit->setText("The answer to life the universe and everything.");
        return;
    }


    try
    {
        operStr = std::to_string(StringCalculator::calculator(operStr));
        ui->lineEdit->setText(operStr.c_str());
    }
    catch(std::runtime_error)
    {
        ui->lineEdit->setText("Invalid expression!");
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter)
        slotEnter();
}
