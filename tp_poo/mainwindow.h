#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "PantallaInicioUI/pantallainicioui.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStackedWidget *pantallas;
    PantallaInicioUI *pantallaInicio;
private:
    Ui::MainWindow *ui;
    void AnadirPantallas();
    void iraPantallaInicio();
};
#endif // MAINWINDOW_H
