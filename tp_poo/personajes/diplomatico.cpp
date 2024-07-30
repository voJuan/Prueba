#include "diplomatico.h"

diplomatico::diplomatico() {
    //Se settea el tipo que corresponde.
    //Los puntos que se ganaran.
    //Los puntos que se perderan.
    //Booleano que determina si tiene los documentos en regla o no.
    setTipo("diplomatico");
    setPuntos(25);
    setSacarPunto(25);
    setDejarPasar(dejarPasarAleatorio());

}
