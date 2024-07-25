#ifndef PERSONAJEABST_H
#define PERSONAJEABST_H
#include <QString>
#include <QRandomGenerator>
class personajeAbst
{
public:
    personajeAbst();
    virtual ~personajeAbst() = default;
    QString getTipo() const;
    int getPuntos() const;
    int getSacarPunto() const;
    bool getDejarPasar() const;
    static personajeAbst* crearPersonajeAleatorio();

protected:
    void setTipo(const QString &tipo);
    void setPuntos(int puntos);
    void setSacarPunto(int sacarPunto);
    void setDejarPasar(bool dejarPasar);
    bool dejarPasarAleatorio();

private:
    int puntos;
    int sacarPunto;
    QString tipo;
    bool dejarPasar;


};

#endif // PERSONAJEABST_H
