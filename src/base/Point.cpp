#include "Point.h"

Point::Point( double x, double y ){
	this->x = x;
	this->y = y;
}

double Point::operator- ( const Point &b ){
	/*
        ________________________________
       /             2                2
     \/ (|xb| - |xa|)  + (|yb| - |ya|)

	 */
	return sqrt( pow( fabs (b.x) - fabs (this->x) , 2.0 ) + pow( fabs (b.y) - fabs (this->y), 2.0 ) );
}

std::ostream& operator<< ( std::ostream& o, const Point *s ) {
	o.precision(6);
	o << "(" << s->x << ", " << s->y << ")";
	return o;
}

