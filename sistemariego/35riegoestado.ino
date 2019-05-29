enum ESTADO_SISTEMA_RIEGO {
  REPOSO = 0,
  ABRIENDO = 1,
  REGANDO = 2,
  CERRANDO = 3
};

ESTADO_SISTEMA_RIEGO estado;

void iniciarEstado(){
  estado = REPOSO;
}

char * devuelveEstado(){
  if(estado == REPOSO) {
    return "Reposo";
  }
  if(estado == ABRIENDO) {
    return "Abriendo";
  }
  if(estado == REGANDO) {
    return "Regando";
  }
  if(estado == CERRANDO) {
    return "Cerrando";
  }
  return "Desconocido";
}
