#include "aldeano.h"

aldeano::aldeano() {
    setTipo("aldeano"); //Se settea el tipo que corresponde.
    setPuntos(10); //Los puntos que se ganaran.
    setSacarPunto(15); //Los puntos que se perderan.
    setDejarPasar(dejarPasarAleatorio()); //Booleano que determina si tiene los documentos en regla o no.
}
