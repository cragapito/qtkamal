#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "../base/Point.h"
#include <string>

const double earth_radius = 6378.137; // WGS-84
const double magic = ( 2 * M_PI * earth_radius ) / 360;

class Coordinate: public Point {
public:

	std::string name;

	Coordinate();
	Coordinate( const double lat, const double lon);
	Coordinate( const int lat_gr, const int lat_min, const double lat_seg,
            const int lon_gr, const int lon_min, const double lon_seg );

    int setGMS(const int lat_gr, const int lat_min, const double lat_seg,
           const int lon_gr, const int lon_min, const double lon_seg);

    /*
    *
    * Fórmula de Haversine
    *
    * earth = 6378.137; // WGS-84
    * magic = ( 2 * M_PI * earth ) / 360;
    *
    * Parâmetros em radianos:
    *
                  /     ____________________________________________________________________  \
                  |    /    / lat1 - lat2 \ 2                               / lon1 - lon2 \ 2 |
         2 . asin |   / sin | ----------- |  + cos(lat1) . cos (lat2) . sin | ----------- |   | . magic
                  \ \/      \      2      /                                 \      2      /   /

   */

    double dist ( const Coordinate &c );
	double operator- ( const Coordinate& c );

	friend std::ostream& operator<< ( std::ostream& o, const Coordinate *p );
    virtual ~Coordinate() {};
};

#endif /* COORDINATE_H_ */
