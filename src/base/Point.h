#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include <iostream>

class Point {
public:
	double x;
	double y;

	Point( double x = 0 , double y = 0 );
	virtual double operator- ( const Point &b );
	friend std::ostream& operator<< ( std::ostream& o, const Point *p );
    virtual ~Point() {};
};

#endif /* POINT_H_ */
