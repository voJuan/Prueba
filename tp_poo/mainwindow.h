#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QSoundEffect>
#include "PantallaInicioUI/pantallainicioui.h"
#include "pantallaJuego/pantallajuego.h"

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
    pantallajuego *pantallaJugar;
private:
    Ui::MainWindow *ui;
    void cargarPartida();
    void AnadirPantallas();
    void iraPantallaInicio();
    void iraPantallaJuego();
    void stopMusica();
};
#endif // MAINWINDOW_H
