#ifndef PANTALLAINICIOUI_H
#define PANTALLAINICIOUI_H

#include <QWidget>
#include <QSoundEffect>
QT_BEGIN_NAMESPACE
namespace Ui {
class PantallaInicioUI;
}
QT_END_NAMESPACE

class PantallaInicioUI : public QWidget
{
    Q_OBJECT
public:
    QSoundEffect *getMusicaFondo() {return this->sonidoFondo;}
    explicit PantallaInicioUI(QWidget *parent = nullptr);
    ~PantallaInicioUI();
signals:
    void iniciarJuegoClicked();
private:
    QSoundEffect *sonidoFondo;
    Ui::PantallaInicioUI *ui;
protected:
private slots:
    void configurarSonidoFondo();
};

#endif // PANTALLAINICIOUI_H
