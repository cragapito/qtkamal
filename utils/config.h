#ifndef CONFIG_H
#define CONFIG_H

//TODO: Bring styles confs

class config
{

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
