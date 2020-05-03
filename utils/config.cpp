#include "config.h"
#include <QSettings>
#include <QDebug>
#include <QDir>

using namespace std;

config::config() {
    // Grava no diretório de configurações do usuário conforme o padrão do sistema de destino
    //QSettings settings(QSettings::IniFormat, QSettings::UserScope, "qtkamal", "qtkamal");

    // Grava no diretório de execução. A chamada no destrutor precisa ser igual.
    QSettings settings ("qtkamal.ini", QSettings::IniFormat);

    settings.beginGroup("Beam");
    beam_reach      = settings.value("reach",    5  ).toDouble();
    beam_azimute    = settings.value("azimute", 45  ).toDouble();
    settings.endGroup();

    settings.beginGroup("Circle");
    circ_radius     = settings.value("radius", 0.3  ).toDouble();
    circ_points     = settings.value("points", 100  ).toDouble();
    circ_azimute    = settings.value("azimuth", 45  ).toDouble();
    circ_abertura   = settings.value("opening", 10  ).toDouble();
    settings.endGroup();
}

void config::save() {
    QSettings settings ("qtkamal.ini", QSettings::IniFormat);

    settings.beginGroup("Beam");
    settings.setValue("reach",      beam_reach      );
    settings.setValue("azimuth",    beam_azimute    );
    settings.endGroup();

    settings.beginGroup("Circle");
    settings.setValue("radius",     circ_radius     );
    settings.setValue("points",     circ_points     );
    settings.setValue("azimuth",    circ_azimute    );
    settings.setValue("opening",    circ_abertura   );
    settings.endGroup();

    settings.sync();

    qDebug() << "Arquivo de configurações salvo em " << settings.fileName();
}
