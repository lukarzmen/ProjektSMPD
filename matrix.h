#ifndef MATRIX_H
#define MATRIX_H
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

class matrix
{
public:
    matrix(){}
};


namespace bnu = boost::numeric::ublas;

int determinant_sign(const bnu::permutation_matrix<std::size_t>& pm);

double determinant( bnu::matrix<double>& m );

#endif // MATRIX_H
