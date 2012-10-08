#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calendarclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_2_clicked();
    void onClientConnected();
    void onAuthenticationFailed();

private:
    Ui::MainWindow *ui;
    CalendarClient *m_client;
};

#endif // MAINWINDOW_H
