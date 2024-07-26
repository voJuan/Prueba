#include "refugiadopolitico.h"

refugiadoPolitico::refugiadoPolitico() {
    setTipo("refugiado");
    setPuntos(15);
    setSacarPunto(25);
    setDejarPasar(dejarPasarAleatorio());
}
