#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

class config {

public:
  double beam_azimuth;
  double beam_reach;

  double circ_radius;
  double circ_points;
  double circ_opening;

  double gattack;
  double gproj;

  config();
  void save();
  void reset();
};

#endif // CONFIG_H
