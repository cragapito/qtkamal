#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "../base/Point.h"
#include <string>

const double earth = 6378.137; // WGS-84
const double magic = ( 2 * M_PI * earth ) / 360;

class Coordinate: public Point {
public:

	std::string name;

	Coordinate();
	Coordinate( const double lat, const double lon);
	Coordinate( const int lat_gr, const int lat_min, const double lat_seg,
            const int lon_gr, const int lon_min, const double lon_seg );

    int setGMS(const int lat_gr, const int lat_min, const double lat_seg,
           const int lon_gr, const int lon_min, const double lon_seg);

	double dist ( const Coordinate &c );
	double operator- ( const Coordinate& c );
	friend std::ostream& operator<< ( std::ostream& o, const Coordinate *p );
};

#endif /* COORDINATE_H_ */
