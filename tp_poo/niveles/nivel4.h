#ifndef NIVEL4_H
#define NIVEL4_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "nivel1.h"

namespace Ui {
class nivel4;
}

class nivel4 : public nivel1
{
    Q_OBJECT

public:
    explicit nivel4(QWidget *parent = nullptr);
    void setupDocumentos() override;
    void SetDoc() override;
    QString obtenerReglas() override;
    virtual void SetNivel();
    int PasarNivel() override;
    void SetDireccion() override;
    // int PasarNivel() override;
    ~nivel4();

private:
    Ui::nivel4 *ui;
    QLabel* proposito;
    QLabel* integrantes;
    QLabel* ocupacion;

};

#endif // NIVEL4_H
