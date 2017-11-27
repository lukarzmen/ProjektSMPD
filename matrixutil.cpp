#include "matrixutil.h"

matrixutil::matrixutil()
{

}

int matrixutil::determinant_sign(const boost::numeric::ublas::permutation_matrix<std::size_t>& pm)
{
        int pm_sign = 1;
        std::size_t size = pm.size();
        for (std::size_t i = 0; i < size; ++i)
                if (i != pm(i))
                        pm_sign *= -1.0; // swap_rows would swap a pair of rows here, so wechange sign
        return pm_sign;
}

float matrixutil::determinant(bnu::matrix<float> &m ) {
    bnu::permutation_matrix<std::size_t> pm(m.size1());
    double det = 1.0;
    if( bnu::lu_factorize(m,pm) ) {
        det = 0.0;
    } else {
        for(int i = 0; i < m.size1(); i++)
            det *= m(i,i); // multiply by elements on diagonal
        det = det * determinant_sign( pm );
    }
    return det;
}

bnu::matrix<float> matrixutil::vectorToMatrix(std::vector<float> &vector)
{
    bnu::matrix<float> matrix (vector.size(), 1);
    for (int i = 0; i < matrix.size1(); i++)
        matrix(i, 1) = vector.at(i);
    return matrix;
}

bnu::matrix<float> matrixutil::vectorsOfVectorsToMatrix(std::vector<std::vector<float>> &vectorsOfVectors)
{
    bnu::matrix<float> matrix (vectorsOfVectors.size(), vectorsOfVectors.front().size());
    for (int i = 0; i < matrix.size1(); i++)
        for (int j = 0; j < matrix.size2(); j++) {
            matrix(i, j) = vectorsOfVectors[i][j];
        }
    return matrix;
}
