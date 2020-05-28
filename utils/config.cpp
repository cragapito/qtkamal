#include "config.h"
#include <QDebug>
#include <QDir>
#include <QSettings>

using namespace std;

// TODO: Desenvolver tela de configuração para os parâmatros
config::config() {
  // Grava no diretório de configurações do usuário conforme o padrão do sistema
  // de destino
  // QSettings settings(QSettings::IniFormat, QSettings::UserScope, "qtkamal",
  // "qtkamal");

  // Grava no diretório de execução. A chamada no destrutor precisa ser igual.
  QSettings settings("qtkamal.ini", QSettings::IniFormat);

  settings.beginGroup("Beam");
  beam_reach = settings.value("reach_km", 5).toDouble();
  beam_azimuth = settings.value("azimuth", 0).toDouble();
  settings.endGroup();

  settings.beginGroup("Circle");
  circ_radius = settings.value("radius", 0.3).toDouble();
  circ_points = settings.value("points", 100).toDouble();
  circ_opening = settings.value("opening", 10).toDouble();
  settings.endGroup();
}

void config::save() {
  QSettings settings("qtkamal.ini", QSettings::IniFormat);

  settings.beginGroup("Beam");
  settings.setValue("reach_km", beam_reach);
  settings.setValue("azimuth", beam_azimuth);
  settings.endGroup();

  settings.beginGroup("Circle");
  settings.setValue("radius", circ_radius);
  settings.setValue("points", circ_points);
  settings.setValue("opening", circ_opening);
  settings.endGroup();

  settings.sync();

  qDebug() << "Arquivo de configurações salvo em " << settings.fileName();
}