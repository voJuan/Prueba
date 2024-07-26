#include "diplomatico.h"

diplomatico::diplomatico() {
    setTipo("diplomatico");
    setPuntos(25);
    setSacarPunto(25);
    setDejarPasar(dejarPasarAleatorio());

}
