#ifndef NIVEL5_H
#define NIVEL5_H
#include "nivel1.h"
#include <QWidget>

namespace Ui {
class nivel5;
}

class nivel5 : public nivel1
{
    Q_OBJECT

public:
    explicit nivel5(QWidget *parent = nullptr);
    void setupDocumentos() override;
    void SetDoc() override;
    QString obtenerReglas() override;
    virtual void SetNivel();
    int PasarNivel() override;
    void SetDireccion() override;
    // int PasarNivel() override;
    ~nivel5();

private:
    Ui::nivel5 *ui;
    QLabel* proposito;
    QLabel* integrantes;
    QLabel* ocupacion;
    QLabel* vacunas;
};

#endif // NIVEL5_H
