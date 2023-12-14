#ifndef DEEPLEARNING_MATRICE_H
#define DEEPLEARNING_MATRICE_H
#include <vector>

class Matrice {

public:
    Matrice(std::vector<std::vector<double>> tab);

    void print(); //print the content of the matrice
    double getDet(); //return the determinant of the matrice

    std::vector<double> getRow(int i); //get the row number i of the matrice
    std::vector<double> getColumn(int j); //get the column number i of the matrice

    std::vector<std::vector<double>> getTab(); //return the associated vector of the matrice
    Matrice getMinor(unsigned int i,unsigned int j); //return the minor matrice
    Matrice getComatrice(); //return the comatrice
    Matrice getTranspose(); //return the transpose matrice
    Matrice getInverse(); //return the inverse matrice

    Matrice operator+(Matrice const& M); //return an addition with a same size matrice
    Matrice operator*(double const& x); //return a scale of the matrice with a number
    Matrice operator*(Matrice const& M); //return the multiplication of the matrice with another one
    Matrice operator^(int const& x); //return the matrice to a power

    unsigned int getHeight(); //return the Height of the matrice
    unsigned int getWidth(); //return the width of the matrice


    void freeConectedMatrice(); //free the alocation of the matrice

private:
    unsigned int m_height, m_width;
    std::vector<std::vector<double>> m_tab; //the matrice's values
    Matrice *pInverse;
    bool isInversedCalculed = 0;
    Matrice *pTranspose;
    bool isTransposeCalculed = 0;
    Matrice *pComatrice;
    bool isComatriceCalculed = 0;

    double determinant;
    bool isDeterminantCalculed;
};

Matrice randomMatrice(unsigned int I, unsigned int J);//return a random matrice
#endif //DEEPLEARNING_MATRICE_H