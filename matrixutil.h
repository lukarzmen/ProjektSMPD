#ifndef MATRIXUTIL_H
#define MATRIXUTIL_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <string>
#include <vector>

namespace bnu = boost::numeric::ublas;

class matrixutil
{
public:
    matrixutil();
    int determinant_sign(const bnu::permutation_matrix<std::size_t>& pm);
    float determinant( bnu::matrix<float>& m );
    bnu::matrix<float> vectorsOfVectorsToMatrix(std::vector<std::vector<float>> vectorsOfVectors);
    bnu::matrix<float> vectorToMatrix(std::vector<float> vector);
};


#endif // MATRIXUTIL_H
