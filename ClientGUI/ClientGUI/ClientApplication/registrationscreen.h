#ifndef REGISTRATIONSCREEN_H
#define REGISTRATIONSCREEN_H

#include <QMainWindow>
#include "connector.h"
#include "selectionwindow.h"

namespace Ui {
class RegistrationScreen;
}

class RegistrationScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationScreen(QWidget *parent = nullptr);
    ~RegistrationScreen();

private slots:
    void on_acceptButton_clicked();

private:
    Ui::RegistrationScreen *ui;
    SelectionWindow* selectionWindow;
};

#endif // REGISTRATIONSCREEN_H
