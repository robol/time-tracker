#define QT_NO_KEYWORDS

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
    
private Q_SLOTS:
    void onClientConnected();
    void onAuthenticationFailed();
    void on_computeButton_clicked();
    void on_connectPushButton_clicked();
    void on_calendarComboBox_currentIndexChanged(int index);
    void on_clientLoadingEventsStarted();
    void on_clientLoadingEventsFinished();

private:
    Ui::MainWindow *ui;
    CalendarClient *m_client;
};

#endif // MAINWINDOW_H
