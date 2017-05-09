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

void MainWindow::slotC()
{
    operStr = "";
    ui->lineEdit->setText("");
}

void MainWindow::slotCopy()
{
    QApplication::clipboard()->setText(operStr.c_str());
}
