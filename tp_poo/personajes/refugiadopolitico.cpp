#include "refugiadopolitico.h"

refugiadoPolitico::refugiadoPolitico() {
    //Se settea el tipo que corresponde.
    //Los puntos que se ganaran.
    //Los puntos que se perderan.
    //Booleano que determina si tiene los documentos en regla o no.
    setTipo("refugiado");
    setPuntos(15);
    setSacarPunto(25);
    setDejarPasar(dejarPasarAleatorio());
}
