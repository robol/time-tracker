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
    void onClientConnected();
    void onAuthenticationFailed();
    void on_computeButton_clicked();
    void on_connectPushButton_clicked();

private:
    Ui::MainWindow *ui;
    CalendarClient *m_client;
};

#endif // MAINWINDOW_H
