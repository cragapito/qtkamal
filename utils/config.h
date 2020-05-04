#ifndef CONFIG_H
#define CONFIG_H

class config
{

public:
    double beam_azimute;
    double beam_reach;

    double circ_radius;
    double circ_points;
    double circ_abertura;

    config();
    void save();
};


#endif // CONFIG_H
