#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QClipboard>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot1() { QApplication::aboutQt(); }
    void slot2(QString);        // setting operStr from inputfield

    void slotC();
    void slotEnter() {}

    void slotNum1() { setLineEdit("1"); }
    void slotNum2() { setLineEdit("2"); }
    void slotNum3() { setLineEdit("3"); }
    void slotNum4() { setLineEdit("4"); }
    void slotNum5() { setLineEdit("5"); }
    void slotNum6() { setLineEdit("6"); }
    void slotNum7() { setLineEdit("7"); }
    void slotNum8() { setLineEdit("8"); }
    void slotNum9() { setLineEdit("9"); }
    void slotNum0() { setLineEdit("0"); }

    void slotDot() { setLineEdit("."); }

    void slotPlus() { setLineEdit("+"); }
    void slotSub() { setLineEdit("-"); }
    void slotMult() { setLineEdit("*"); }
    void slotDiv() { setLineEdit("/"); }

    void slotCopy();



private:
    Ui::MainWindow *ui;
    std::string operStr;

    void setLineEdit(const char * str);
    void resetLineEdit();
};

#endif // MAINWINDOW_H
