#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QVBoxLayout>
#include "../PersonajeUI/personajeui.h"
#include "../niveles/nivel1.h"
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui {
class pantallajuego;
}
QT_END_NAMESPACE

class pantallajuego : public QWidget
{
    Q_OBJECT

public:
    explicit pantallajuego(QWidget *parent = nullptr);
    ~pantallajuego();
signals:

private:
    Ui::pantallajuego *ui;
    QTimer *deshabilitarBoton;
    PersonajeUI *personaje;
    nivel1 *nivel;
    QVBoxLayout *layoutPersonaje;
    int puntaje;
    void anadirPersonaje(QWidget *parent);

protected:
public slots:
    void iniciarAnimacionPersonaje(int deltaX);
private slots:
    void cooldownBotones();
    void activarBotones();
    void mostrarMensajePerdida();
    void ActualizarPuntaje(int puntos);

    void on_aceptar_clicked();
    void on_rechazar_clicked();
};

#endif // PANTALLAJUEGO_H
