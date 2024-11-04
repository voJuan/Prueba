#ifndef NIVEL3_H
#define NIVEL3_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "nivel1.h"
namespace Ui {
class nivel3;
}

class nivel3 : public nivel1
{
    Q_OBJECT

public:
    explicit nivel3(QWidget *parent = nullptr);
    void  setupDocumentos() override;
    void SetDoc() override;
    QString obtenerReglas() override;
    virtual void SetNivel();
    int PasarNivel() override;
     void SetDireccion() override;
    void escribirLogs() override;
   // int PasarNivel() override;
    ~nivel3();

private:
    Ui::nivel3 *ui;
    QLabel* proposito;
    QLabel* integrantes;
    QSet<QString> fallos_nivel3;
};

#endif // NIVEL3_H
