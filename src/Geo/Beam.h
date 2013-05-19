#ifndef BEAM_H_
#define BEAM_H_

#include "../Geo/Coordinate.h"
#include "../base/Straight.h"

// earth definido em Coordinate (p/ calc. distância)

class Beam : public Straight {
private:
	double to_rad ( const double d );
	double to_deg ( const double g );
	virtual void sync_base();
public:

	std::string* 	name;
	Coordinate* 	source;		// Origem
	Coordinate* 	scope;   	// Alcance
	double			daz;		// Azimute decimal

    Beam();
	Beam( Coordinate &source );
	virtual ~Beam(){};
	void proj( const double km );
	double azimute();
	friend std::ostream& operator<< ( std::ostream& o, const Beam *b );
};

class ErmBeam : public Beam {
public:
	ErmBeam ( Coordinate &source ) : Beam ( source ){};
	virtual ~ErmBeam(){};
};
class ManBeam : public Beam {
public:
	ManBeam ( Coordinate &source ) : Beam ( source ){};
	virtual ~ManBeam(){};
};

class CirBeam : public Beam {
public:
	double raioKm;
	double points;
	/* A reta da classe base possui coeficiente angular indefinido
	 * então não há necessidade de ajustar os parâmetros dela.
	 */
	virtual void sync_base() {};
	CirBeam ( Coordinate &source ) : Beam ( source ){
			raioKm = daz;
			points = 100 ;
		};
	virtual ~CirBeam(){};
};

#endif /* BEAM_H_ */
