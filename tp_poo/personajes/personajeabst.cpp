#include "personajeabst.h"
#include "aldeano.h"
#include "revolucionario.h"
#include "diplomatico.h"
#include "refugiadopolitico.h"

personajeAbst::personajeAbst() : puntos(0), sacarPunto(0), dejarPasar(dejarPasarAleatorio()) {}

QString personajeAbst::getTipo() const { return tipo; }
int personajeAbst::getPuntos() const { return puntos; }
int personajeAbst::getSacarPunto() const { return sacarPunto; }
bool personajeAbst::getDejarPasar() const { return dejarPasar; }


void personajeAbst::setTipo(const QString &tipo) { this->tipo = tipo; }
void personajeAbst::setPuntos(int puntos) { this->puntos = puntos; }
void personajeAbst::setSacarPunto(int sacarPunto) { this->sacarPunto = sacarPunto; }
void personajeAbst::setDejarPasar(bool dejarPasar) { this->dejarPasar = dejarPasar; }


personajeAbst* personajeAbst::crearPersonajeAleatorio() {
    int tipoPersonaje = QRandomGenerator::global()->bounded(4);

    switch (tipoPersonaje) {
    case 0: return new aldeano();
    case 1: return new revolucionario();
    case 2: return new diplomatico();
    case 3: return new refugiadoPolitico();
    default: return nullptr; // Esto no debería ocurrir
    }
}

bool personajeAbst::dejarPasarAleatorio(){
   int dejarPasar = QRandomGenerator::global()->bounded(2);
    switch (dejarPasar) {
    case 0: return true;
    case 1: return false;
    default: return false; // Esto no debería ocurrir
    }
}


