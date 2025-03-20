#include "Vector.hpp"

Vec3::Vec3(double x,double y,double z){
	data = new double[3];
	data[0] = x;
	data[1] = y;
	data[2] = z;
};
Vec3::Vec3(const Vec3& base){
	this->data = new double[3];
	memcpy(this->data,base.data,3*sizeof(double));
};

Vec3::Vec3(const double* data){
	this->data = new double[3];

	if(data)
		memcpy(this->data,data,3*sizeof(double));
}

Vec3::~Vec3(){
	delete[] data;
}

double Vec3::get(int i) const{
	return data[i];
}

void Vec3::set(int i, double v){
	data[i] = v;
}

double Vec3::mod() const{
	return sqrt( pow(x(),2) + pow(y(),2) + pow(z(),2));
}

Vec3 Vec3::Normalize() const{
	double m = mod();
	return (m == 0) ? *this : *this / m;
}

Vec3 Vec3::inverse() const{
	return Vec3( -x(), -y(), -z());
}

double Vec3::dotprod(const Vec3& b) const{
	return x() * b.x() + y() * b.y() + z() * b.z();
}

Vec3 Vec3::crossprod(const Vec3& b) const{
	return Vec3(
		y() * b.z() - z() * b.y(),
		z() * b.x() - x() * b.z(),
		x() * b.y() - y() * b.x()
	);
}

Vec3& Vec3::operator+=(const Vec3& b){
	_x += b.x();
	_y += b.y();
	_z += b.z();

	return *this;
}

Vec3& Vec3::operator-=(const Vec3& b){
	_x -= b.x();
	_y -= b.y();
	_z -= b.z();

	return *this;
}

Vec3& Vec3::operator*=(const double b){
	_x *= b;
	_y *= b;
	_z *= b;

	return *this;
}

Vec3& Vec3::operator/=(const double b){
	_x /= b;
	_y /= b;
	_z /= b;

	return *this;
}

Vec3 Vec3::operator+(const Vec3& b) const{
	return Vec3(x() + b.x(), y() + b.y(), z() + b.z());
};
Vec3 Vec3::operator-(const Vec3& b) const{
	return Vec3(x() - b.x(), y() - b.y(), z() - b.z());
};
Vec3 Vec3::operator*(const double b) const{
	return Vec3(x() * b, y() * b, z() * b);
};
Vec3 Vec3::operator/(const double b) const{
	return Vec3(x() / b, y() / b, z() / b);
};

Vec3& Vec3::operator=(const Vec3& b){
	_x = b.x();
	_y = b.y();
	_z = b.z();

	return *this;
}

double& Vec3::operator[](const int ix){
	return data[ix];
}

std::ostream& operator<<(std::ostream& os, const Vec3& v){
	os << "( " << v.x() << ", " << v.y() << ", " << v.z() << " )";
	return os;
}
