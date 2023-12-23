#include <iostream>
#include "matrixLib.h"

using namespace std;

//initialisation
Matrice::Matrice(vector<std::vector<double>> tab){
    m_tab = tab;
    m_height = tab.size();
    m_width = tab[0].size();

    //initialisation des matrices obtenus à partir de l'objet :
    pInverse = (Matrice*) malloc(sizeof(Matrice));
    pTranspose = (Matrice*) malloc(sizeof(Matrice));
    pComatrice = (Matrice*) malloc(sizeof(Matrice));

    for(unsigned int i(1);i<m_height;i++){
        if(m_tab[i].size() != m_width){
            throw std::runtime_error("ERROR : Invalid shape !");}
            } //vérification de la forme de la matrice.
}

//retourne le tableau de nombre associé à la matrice
std::vector<vector<double>> Matrice::getTab() {
    return m_tab;
}

//addition de deux matrices
Matrice Matrice::operator+(const Matrice &M) {
    //vérification de la formes des matrices :
    if((m_height != M.m_height) | (m_width != M.m_width)){cout << "ERROR : shapes are not matching for an addition !"<<endl;}
    //calcul :
    std::vector<std::vector<double>> resTab;
    for(unsigned int i(0);i<m_height;i++){
        resTab.push_back({});
        for (unsigned int j = 0; j < m_width; ++j) {
        resTab[i].push_back(m_tab[i][j] + M.m_tab[i][j]);
        }} return {resTab};
}

//multiplication d'une matrice par un scalaire
Matrice Matrice::operator*(double const& x){
    std::vector<std::vector<double>> resTab;
    for( unsigned int i(0);i<m_height;i++){
        resTab.push_back({});
        for (unsigned int j = 0; j < m_width; ++j) {
            resTab[i].push_back(m_tab[i][j] * x);
        }} return {resTab};
}

//multiplication d'une matrice par une autre
Matrice Matrice::operator*(const Matrice &M) {
    if(m_width != M.m_height ){cout << "ERROR : shapes are not matching for an addition !"<<endl;}
    std::vector<std::vector<double>> resTab;
    for(unsigned int i(0);i<m_height;i++){
        resTab.push_back({});
        for (unsigned int j = 0; j < M.m_width; ++j) {
            resTab[i].push_back(0);
            for (unsigned int k(0);k<m_width;k++){
                resTab[i][j] += m_tab[i][k] * M.m_tab[k][j];
                }
        }} return {resTab};
}

//exponentiation d'une matrice
Matrice Matrice::operator^(const int &n) {
    if(n == 0){    vector<vector<double>> tab;
        for (unsigned int i = 0; i < m_width; ++i) {
            tab.push_back({});
            for (unsigned int j = 0; j < m_width; ++j) {
                if(i == j){tab[i].push_back(1.0);}
                else{tab[i].push_back(0.0);}
            }
        } return {tab};}
    else if(n == 1){return {m_tab};}
    else if(n < 0){return getInverse()^(0-n);}
    else if(n % 2 == 0){return (*this * *this)*(n/2);}
    else if(n % 2 == 1){return *this * (*this * *this)*((n-1)/2);}
    return {{{NULL}}};
}

//retourne une ligne ou une colonne i ou j
vector<double> Matrice::getRow(int i) {return m_tab[i];}
vector<double> Matrice::getColumn(int j) {
    vector<double> res;
    for(unsigned int i(0);i<m_height;i++){
        res.push_back(m_tab[i][j]);
    } return res;}

//renvoie la matrice mineur (je suis pas sûr du nom de cette dernière x) )
Matrice Matrice::getMinor(unsigned int I, unsigned int J) {
    vector<vector<double>> res;
    for (unsigned int i = 0; i < m_height; ++i) {
        if (I != i) {
            res.push_back({});
            for (unsigned int j = 0; j < m_width; ++j) {
                if (J != j) {
                    res.back().push_back(m_tab[i][j]);
                }
            }
        }}return {res};
}

//renvoie la comatrice
Matrice Matrice::getComatrice() {
    if(isComatriceCalculed) return *pComatrice;

    vector<vector<double>> res;
    for (unsigned int i = 0; i < m_height; ++i) {
        res.push_back({});
        for (unsigned int j = 0; j < m_width; ++j) {
        res[i].push_back((1-((i+j)%2)*2)* getMinor(i,j).getDet()); // (1-((i+j)%2)*2) pow(-1,i+j)
        }
    }
    Matrice result = Matrice({res});
    result.pComatrice = this;
    result.isComatriceCalculed = true;
    *pComatrice = result;
    isComatriceCalculed = true;
    return *pComatrice;
}

//renvoie le déterminant de la matrice
double Matrice::getDet() {
    if(isDeterminantCalculed) return determinant;
    if(m_width != m_height){return 0;}
    if(m_width == 1){return m_tab[0][0];}
    if(m_width == 2){return m_tab[0][0] * m_tab[1][1] - m_tab[0][1] * m_tab[1][0];}
    else{
        Matrice C = getComatrice();
        double determinant = 0;
        for (unsigned int i = 0; i < m_height; ++i) {
            determinant += C.m_tab[i][0] * m_tab[i][0];
        }
        isDeterminantCalculed = true;
        return determinant;
    }
}

//renvoie la transposé de la matrice
Matrice Matrice::getTranspose() {
    if(isTransposeCalculed) return *pTranspose;

    vector<vector<double>> resTab;
    for (unsigned int i = 0; i < m_width; ++i) {
        resTab.push_back({});
        for (unsigned int j = 0; j < m_height; ++j) {
            resTab[i].push_back(m_tab[j][i]);
        }
    }
    Matrice result = Matrice({resTab});
    result.pTranspose = this;
    result.isTransposeCalculed = true;

    *pTranspose = result;
    isTransposeCalculed = true;
    return *pTranspose;
}

//renvoie l'inverse de la matrice
Matrice Matrice::getInverse() { //🤮🤮🤮
    if(isInversedCalculed) return *pInverse ;
    else{
        Matrice result = getComatrice().getTranspose() * (1/getDet());
        result.pInverse = this;
        result.isInversedCalculed=true;
        *pInverse = result;
        isInversedCalculed = true;
        return *pInverse;
    }
}

//variables privées corespondant à la largeur et la hauteur de la matrice
unsigned int Matrice::getHeight() {return m_width;}
unsigned int Matrice::getWidth(){return m_height;}

void Matrice::freeConectedMatrice()
{
    free(pComatrice);
    free(pInverse);
    free(pTranspose);
}

//affiche la matrice
void Matrice::print() {
    for(unsigned int i(0);i < m_height;i++){
        cout << '|';
        for(unsigned int j(0);j<m_width;j++){
            printf("%3f|",m_tab[i][j]);
        }
        cout << endl;
    }
}

Matrice randomMatrice(unsigned int I, unsigned int J){
    vector<vector<double>> tab;
    for (unsigned int i = 0; i < I; ++i) {
        tab.push_back({});
        for (unsigned int j = 0; j < J; ++j) {
                 tab[i].push_back(rand()%100 -50);
        }
    }return {tab};
}