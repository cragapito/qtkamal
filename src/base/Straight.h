#ifndef STRAIGHT_H_
#define STRAIGHT_H_

#include "Point.h"
#include <assert.h>

class Straight {

protected:
	Straight();
	void define(const Point &pt, const double ang);
	void define(const Point &A, const Point &B);
	Straight( const double a, const double b, const double c);

public:
	double a;
	double b;
	double c;

	Straight(const Point &pt, const double ang);
	Straight(const Point &A, const Point &B);

	friend std::ostream& operator<< ( std::ostream& o, const Straight *s );
};

#endif /* STRAIGHT_H_ */
