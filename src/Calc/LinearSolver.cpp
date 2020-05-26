#include "LinearSolver.h"

// TODO: Calcular área de incerteza
LinearSolver::LinearSolver(const vector<Straight *> &v) {

  // Dados insuficientes
  if (v.size() < 2)
    return;

  sto = v.size();
  m = gsl_matrix_alloc(sto, 2); // Matriz de incógnitas
  b = gsl_vector_alloc(sto);    // Matriz de independentes

  for (unsigned int i = 0; i < sto; i++) {
    gsl_matrix_set(m, i, 0, v.at(i)->a);
    gsl_matrix_set(m, i, 1, v.at(i)->b);
    gsl_vector_set(b, i, -v.at(i)->c);
  }
}

Point *LinearSolver::solve() {

  gsl_vector *m_tau, *m_x;

  // Dados insuficientes
  if (sto < 2)
    return NULL;

  m_x = gsl_vector_alloc(2);
  m_tau = gsl_vector_alloc(2);
  m_res = gsl_vector_alloc(sto);

  gsl_linalg_QR_decomp(m, m_tau);
  gsl_linalg_QR_lssolve(m, m_tau, b, m_x, m_res);

  res = new Point(gsl_vector_get(m_x, 0), gsl_vector_get(m_x, 1));

  gsl_vector_free(m_tau);
  gsl_vector_free(m_x);

  return res;
}

string LinearSolver::getIncognitas(void) {
  ostringstream o;
  o.precision(2);

  o << endl << "Incógnitas: " << endl;
  for (unsigned int i = 0; i < sto; i++) {
    for (int j = 0; j < 2; j++)
      o << gsl_matrix_get(m, i, j) << endl;
    o << endl;
  }
  return o.str();
}

string LinearSolver::getIndependentes(void) {
  ostringstream o;
  o.precision(2);

  o << endl << "Indepententes: " << endl;
  for (unsigned int i = 0; i < sto; i++)
    o << gsl_vector_get(b, i) << endl;
  return o.str();
}

string LinearSolver::getResidual(void) {
  ostringstream o;
  o.precision(2);

  o << endl << "Residual: " << endl;
  for (unsigned int i = 0; i < sto; i++)
    o << gsl_vector_get(m_res, i) << endl;
  return o.str();
}

LinearSolver::~LinearSolver() {
  gsl_vector_free(b);
  gsl_vector_free(m_res);
  gsl_matrix_free(m);
  // delete res;
}
