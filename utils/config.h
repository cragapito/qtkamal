#ifndef CONFIG_H
#define CONFIG_H

// TODO: Implementar tela de configuração
// TODO: Trazer estilos para a configuração
class config {

public:
  double beam_azimuth;
  double beam_reach;

  double circ_radius;
  double circ_points;
  double circ_opening;

  config();
  void save();
};

#endif // CONFIG_H
