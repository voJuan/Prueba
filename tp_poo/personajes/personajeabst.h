#ifndef PERSONAJEABST_H
#define PERSONAJEABST_H
#include <QString>
class personajeAbst
{
public:
    personajeAbst();
    personajeAbst* crearPersonajeAleatorio();
private:
    int puntos;
    int sacarPunto;
    QString tipo;
    bool dejarPasar;


};

#endif // PERSONAJEABST_H
