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

signals:
    void authenticated();
    
private slots:
    void onClientConnected();
    void onAuthenticationFailed();
    void on_computeButton_clicked();
    void on_calendarComboBox_currentIndexChanged(int index);
    void on_actionDisconnect_triggered();

public slots:
    void clientLoadingEventsStarted();
    void clientLoadingEventsFinished();
    void startAuthentication();

private:
    Ui::MainWindow *ui;
    CalendarClient *m_client;
};

#endif // MAINWINDOW_H
