#include "Straight.h"

void Straight::define(const Point &pt, const double ang_rad){
	/*
	 * Equação geral da reta:  y - y0 = m(x - x0)
	 *
	 * sendo tan(a) = sen(a)/cos(a) podemos reescrever:
	 * sen(a).(x - x0) = cos(a).(y - y0)
	 *
	 * ( sen(a) ) x ( -cos(a) ) y - ( sen(a).x0 + cos(a).y0 ) = 0
	 *
	 */
	this->a =  sin(ang_rad);
	this->b = -cos(ang_rad);
	this->c = -( sin(ang_rad) * pt.x - cos(ang_rad) * pt.y );
}

Straight::Straight(){}

Straight::Straight( const double a, const double b, const double c){
	this->a = a;
	this->b = b;
	this->c = c;
}

Straight::Straight(const Point &pt, const double ang_graus){
	double ang_rad = ang_graus * M_PI / 180.0;
	define( pt, ang_rad);
}

void Straight::define(const Point &A, const Point &B){
	double m = (B.y - A.y) / (B.x - A.x);
	double ang_rad = atan(m);
	define( A, ang_rad);
	// Verifica se a reta calculada para A passa pelo ponto B também
	assert( fabs ( this->a * B.x + this->b * B.y + this->c ) < 0.000001 );
}

Straight::Straight(const Point &A, const Point &B){
	this->define( A, B);
}

std::ostream& operator<< (std::ostream& o, const Straight *s) {
	o << "(" << s->a << ").x + (" << s->b << ").y + (" << s->c << ") = 0";
	return o;
}
