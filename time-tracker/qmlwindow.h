#ifndef QMLWINDOW_H
#define QMLWINDOW_H

#include <QWidget>

namespace Ui {
class QmlWindow;
}

class QmlWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit QmlWindow(QWidget *parent = 0);
    ~QmlWindow();

    void startAuthentication();
    
private:
    Ui::QmlWindow *ui;
};

#endif // QMLWINDOW_H
