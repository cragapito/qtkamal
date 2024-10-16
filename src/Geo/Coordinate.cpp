#include "Coordinate.h"
#include <math.h>

Coordinate::Coordinate(){
	this->x = 0;
	this->y = 0;
};

Coordinate::Coordinate( const double lat, const double lon){
	this->x = lat;
	this->y = lon;
}

Coordinate::Coordinate( const int lat_gr, const int lat_min, const double lat_seg,
		const int lon_gr, const int lon_min, const double lon_seg){

    this->setGMS( lat_gr, lat_min, lat_seg, lon_gr, lon_min, lon_seg );
}

int Coordinate::setGMS(const int lat_gr, const int lat_min, const double lat_seg, const int lon_gr, const int lon_min, const double lon_seg)
{
    this->x = ( lat_gr > 0 ?
            lat_gr + lat_min / 60.0 + lat_seg / 3600.0 :
            lat_gr - lat_min / 60.0 - lat_seg / 3600.0 ) ;

    this->y = ( lon_gr > 0 ?
            lon_gr + lon_min / 60.0 + lon_seg / 3600.0 :
                    lon_gr - lon_min / 60.0 - lon_seg / 3600.0 ) ;

    return 0;
}

double Coordinate::operator- ( const Coordinate& c ) {
    /*
     * Em Coordinate.h:
     * const double earth = 6378.137; // WGS-84
     * const double magic = ( 2 * M_PI * earth ) / 360;
     *
     *
     * Fórmula de Haversine
     *
     *
                   /     ____________________________________________________________________  \
                   |    /    / lat1 - lat2 \ 2                               / lon1 - lon2 \ 2 |
          2 . asin |   / sin | ----------- |  + cos(lat1) . cos (lat2) . sin | ----------- |   | . magic
                   \ \/      \      2      /                                 \      2      /   /

    */


    // TODO: Reescrever com funções de chamada para ficar mais clara a conversão necessária para radianos.
    double ret = 2 * asin(
                sqrt(
                    pow( ( sin( (this->x / 180 * M_PI - c.x / 180 * M_PI)/2) ), 2)
                  + cos( this->x / 180 * M_PI)
                  * cos( c.x     / 180 * M_PI)
                  * pow( ( sin( (this->y / 180 * M_PI - c.y / 180 * M_PI)/2) ), 2)
                )
               ) * magic *180 / M_PI;

    return ret;
}

std::ostream& operator<< ( std::ostream& o, const Coordinate *s ) {
	double fractpart, intpart;
	fractpart = modf(s->x, &intpart);
	int gr = (int) intpart;
	double seg = modf((fabs(fractpart) * 60.0), &intpart) * 60.0;
	int min = (int) intpart;

	o.precision(2);
	o << gr << "° " << min << "' " << std::fixed << seg << "\" ";

	fractpart = modf(s->y, &intpart);
	gr = (int) intpart;
	seg = modf((fabs(fractpart) * 60.0), &intpart) * 60.0;
	min = (int) intpart;
	o << gr << "° " << min << "' " << std::fixed << seg << "\"";

	return o;
}
