#include "Matrix.hpp"

Matrix::Matrix(std::initializer_list<double> data){
    this->data = new double[9];

    for(int i = 0; i < 9 && i < (int)data.size(); i ++){
        this->data[i] = data.begin()[i];
    }
}

Matrix::Matrix(const double* data){
    this->data = new double[9];

    if(data)
        memcpy(this->data,data,9 * sizeof(double));
}

Matrix::Matrix(const Matrix& base){
    data = new double[9];

    memcpy(data,base.data,9*sizeof(double));
}

Matrix::~Matrix(){
    delete[] data;
}

Matrix& Matrix::cleanup(){
    for(int i = 0; i < 9; i ++){
        if( fabs( data[i] ) < ZERO_THRESHOLD)
            data[i] = 0;
    }
    return *this;
}

double Matrix::get(int i) const{
    return data[i%9];
}

double Matrix::get(int i, int j) const{
    return data[3*(i%3)+(j%3)];
}

void Matrix::set(int i,double v){
    data[i] = v;
}

Matrix& Matrix::set(int i, int j, double v){
    data[3*i+j] = v;
    return *this;
}

/*
    Matrix a(*this);
    Matrix L({1,0,0,0,1,0,0,0,1});
    Matrix Id(L);

    double k = ( get(1) * get(6) - get( 0 ) * get(7) ) / ( get(0) * get(4) - get(1) * get (3) );

    Matrix m = {
        1 , 0 , 0,
        -get(3)/get(0),1,0,
        - k * get(3) / get(0) - get(6) / get(0) ,k,1
    };


    return m * a;
*/

double Matrix::det() const {
    double ris = 0;
    
    for(int i = 0; i < 3;i++){
        double a = 1,b = 1;
        for(int j = 0; j < 3; j++){
            a*=get(i+j+3,j);
            b*=get(i-j+3,j);
        }
        ris += a-b;
    }

    return ris;
}

Matrix Matrix::transpose() const{
    Matrix ris;

    for(int i = 0; i < 9; i ++)
        ris.set(i/3,i%3, get(i%3,i/3));

    return ris;
}

Matrix Matrix::cofactor() const{
    Matrix ris = 0;

    for(int i = 0; i < 3; i ++)
        for(int j = 0; j < 3; j++)
            ris[i][j] = get(i+1,j+1) * get(i+2,j+2) - get(i+1,j+2) * get(i+2,j+1);
    
    return ris;
}

Matrix Matrix::invert() const{
    return cofactor().transpose() / det();
}


double* Matrix::operator[](const int ix){
    return data+ix*3;
}

Matrix& Matrix::operator+=(const Matrix& b){
    for(int i = 0; i < 9;i++)
        data[i] += b.get(i);
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& b){
    for(int i = 0; i < 9;i++)
        data[i] -= b.get(i);
    return *this;
}

Matrix& Matrix::operator*=(const double b){
    for(int i = 0; i < 9;i++)
        data[i] *= b;
    return *this;
}

Matrix& Matrix::operator/=(const double b){
    for(int i = 0; i < 9;i++)
        data[i] /= b;
    return *this;
}

Matrix Matrix::operator+(const Matrix& b) const{
    Matrix a(*this);
    return a+=b;
}

Matrix Matrix::operator-(const Matrix& b) const{
    Matrix a(*this);
    return a-=b;
}

Matrix Matrix::operator*(const double b) const{
    Matrix a(*this);
    return a*=b;
}

Matrix Matrix::operator/(const double b) const{
    Matrix a(*this);
    return a/=b;
}

Matrix& Matrix::operator*=(const Matrix& b){
    *this = *this * b;
    return *this;
}

Matrix Matrix::operator*(const Matrix& b) const{
    Matrix ris;

    for(int i = 0; i < 9; i ++){
        ris.data[i] = 0;
        for(int j = 0; j < 3;j++)
            ris.data[i] += get(i/3,j) * b.get(j,i%3);
    }

    return ris.cleanup();
}

Vec3 Matrix::operator*(const Vec3& b ) const{
    double* data = new double[3]{0,0,0};

    for(int i = 0; i < 9; i++)
        data[i/3] += get(i) * b.get(i%3);
    
    Vec3 ris(data);
    delete[] data;
    return ris;
}

Matrix& Matrix::operator=(const Matrix& b){
    memcpy(this->data,b.data,9*sizeof(double));
    return *this;
}

Matrix& Matrix::operator=(std::initializer_list<double> data){
    for(int i = 0; i < 9 && i < (int)data.size(); i ++){
        this->data[i] = data.begin()[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& v){
    for(int i = 0; i < 3; i++)
        std::cout << "| " << v.get(i,0) << " , " << v.get(i,1) << " , " << v.get(i,2) << " |" << std::endl;
    return os;
}