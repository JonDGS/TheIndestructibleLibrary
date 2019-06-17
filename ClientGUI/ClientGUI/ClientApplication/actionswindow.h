#ifndef ACTIONSWINDOW_H
#define ACTIONSWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "bitconverter.h"
#include "connector.h"

namespace Ui {
class ActionsWindow;
}

class ActionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActionsWindow(QWidget *parent = nullptr);
    void setUser(std::string user);
    ~ActionsWindow();

private slots:

    void on_browsePushButton_clicked();

    void on_uploadPushButton_clicked();

private:
    Ui::ActionsWindow *ui;
    QString currentPath;
    bool isImageLoaded = false;
    std::string user;
};

#endif // ACTIONSWINDOW_H
