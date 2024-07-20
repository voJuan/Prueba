#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>
#include <QTimer>
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
protected:
private slots:
    void cooldownBotones();
    void activarBotones();


    void on_aceptar_clicked();
    void on_rechazar_clicked();
};

#endif // PANTALLAJUEGO_H
