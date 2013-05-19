
#include "Beam.h"

Beam::Beam(){
    this->source = new Coordinate();
    this->name = &source->name;
    scope = NULL;
}

Beam::Beam( Coordinate &source ){
	this->source = &source;
	this->name = &source.name;
	scope = NULL;
}

double Beam::to_rad( const double d ){
	return d /180 * M_PI ;
}

double Beam::to_deg( const double g ){
	return g *180 / M_PI ;
}

void Beam::proj( const double km ){
	scope = new Coordinate();
	double rad  = to_rad( this->daz );
	double lat1 = to_rad( source->x );
	double lon1 = to_rad( source->y );

	double lat2 = asin ( sin(lat1) * cos(km / earth) + cos(lat1) * sin (km / earth) * cos (rad) );
	double lon2 = lon1 + atan2( sin(rad) * sin(km / earth) * cos(lat1), cos(km / earth) - sin(lat1) * sin (lat2));

	scope->x = to_deg( lat2 );
	scope->y = to_deg( lon2 );

	this->sync_base();
};

void Beam::sync_base(){
	this->define( *source, *scope );
}

double Beam::azimute(){
	if ( ! scope ) return this->daz;
	double lat1 = to_rad( source->x );
	double lon1 = to_rad( source->y );
	double lat2 = to_rad( scope->x  );
	double lon2 = to_rad( scope->y  );

	double azrad = atan2( sin(lon2 - lon1) * cos(lat2) , cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(lon2 - lon1));

	return fmod( azrad * 180.0 / M_PI + 360.0, 360.0);
}

std::ostream & operator <<(std::ostream & o, const Beam *b){
	o << b->source << " -> " <<  b->daz;
	return o;
};
