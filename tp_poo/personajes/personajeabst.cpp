#include "personajeabst.h"
#include "aldeano.h"
#include "revolucionario.h"
#include "diplomatico.h"
#include "refugiadopolitico.h"

personajeAbst::personajeAbst() : puntos(0), sacarPunto(0), dejarPasar(dejarPasarAleatorio()) {}

QString personajeAbst::getTipo() const { return tipo; } //Para que otras clases obtengan el tipo del personaje.
int personajeAbst::getPuntos() const { return puntos; } //Para que otras clases obtengan los puntos a ganar
int personajeAbst::getSacarPunto() const { return sacarPunto; } //Para que otras clases obtengan los puntos a perder
bool personajeAbst::getDejarPasar() const { return dejarPasar; } //Para que otras clases obtengan el bool F = Se debe rechazar, V = Se debe aceptar


void personajeAbst::setTipo(const QString &tipo) { this->tipo = tipo; } //Para establecer el tipo
void personajeAbst::setPuntos(int puntos) { this->puntos = puntos; } //Para establecer el tipo
void personajeAbst::setSacarPunto(int sacarPunto) { this->sacarPunto = sacarPunto; } //Para establecer el tipo
void personajeAbst::setDejarPasar(bool dejarPasar) { this->dejarPasar = dejarPasar; } //Para establecer el tipo

//Este metodo de forma aleatoria desreferencia de la clase base a la clase derivada (Downcasting)
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
//Se elige de forma aleatoria si el personaje debera pasar o no por el control fronterizo.
bool personajeAbst::dejarPasarAleatorio(){
   int dejarPasar = QRandomGenerator::global()->bounded(2);
    switch (dejarPasar) {
    case 0: return true;
    case 1: return false;
    default: return false; // Esto no debería ocurrir
    }
}


