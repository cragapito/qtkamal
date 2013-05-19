#ifndef LINEARSOLVER_H_
#define LINEARSOLVER_H_

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>

#include <vector>
#include <sstream>

#include "../base/Point.h"
#include "../base/Straight.h"

using namespace std;

class LinearSolver {
private:
	gsl_matrix * m;
	gsl_vector * b, * m_res;
	Point* res;
	unsigned int sto;

public:
	LinearSolver( const vector<Straight*> &v );
	virtual ~LinearSolver();

	void add(const vector<Straight*> &v);
	Point* solve();
	string getIncognitas(void);
	string getIndependentes(void);
	string getResidual(void);
	friend ostream& operator<<(ostream& o, LinearSolver *t);
};

#endif /* LINEARSOLVER_H_ */
