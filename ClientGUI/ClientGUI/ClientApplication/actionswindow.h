#ifndef ACTIONSWINDOW_H
#define ACTIONSWINDOW_H

#include <QMainWindow>

namespace Ui {
class ActionsWindow;
}

class ActionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActionsWindow(QWidget *parent = nullptr);
    ~ActionsWindow();

private:
    Ui::ActionsWindow *ui;
};

#endif // ACTIONSWINDOW_H
