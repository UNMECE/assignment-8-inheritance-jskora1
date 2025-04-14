#include <iostream>
#include <cmath>

class Field
{
protected:

	double *value;
	double x, y, z;
public:
		
	Field(double x, double y, double z) : x(x), y(y), z(z){
	  value = new double[3]{0.0,0.0,0.0};	  
}
		
virtual void print() const {
std::cout << "\nField Location (" << x << "," << y  << "," << z << ")  \n";
}		 
		
};

class Electric_Field : public Field
{
	private:
   		double E;
	public:
		Electric_Field() : Field (0.0,0.0,0.0) {}
		Electric_Field(double x, double y, double z) : Field (x, y, z) {}
	
	void calcElectricField (double Q) { 
		double r = std::sqrt (x*x + y*y + z*z);
		double k = 8.988e9; 	

			E = k * Q / (r*r);

std::cout << "Electric Field with " << Q << " charge: " << E << "\n" << std::endl; 

}

Electric_Field operator+(const Electric_Field& other) const { 
	Electric_Field result;
	result.x = this->x; result.y = this->y; result.z = this->z;
	result.setE(this->getE() + other.getE());
	return result;
}

	void setE(double value) { 
		E = value;
	}
	
	double getE() const {
		return E;
	}
};

class Magnetic_Field : public Field
{
  private:
	double M;
  public:
 	Magnetic_Field() : Field (0.0,0.0,0.0) {}       
        Magnetic_Field(double x, double y, double z) : Field (x, y, z) {}
		
	void calcMagneticField (double I) {
		const double mu = 4 * M_PI * 1e-7;
		double r = std::sqrt(x * x + y * y + z * z);

			M = mu * I / (2 * M_PI * r);
	
std::cout << "Magnetic Field with " << I << " Amps: " << M << "\n" << std::endl;
} 

Magnetic_Field operator+(const Magnetic_Field& other) const {
	Magnetic_Field result;
	result.x = x; result.y = y; result.z = z;
	result.M = this->M + other.M;
	return result;
}

	void setM(double value) {
		M = value;
	}

	double getM() const {
		return M;
	}
};

int main () 
{

Electric_Field E(0,1e5,1e3);
E.print();
E.calcElectricField(1e-6);

Electric_Field E2(1e3,1e5,0);
E2.print();
E2.calcElectricField(2e-6);

Electric_Field E3(1e3,0,1e5);
E3.print();
E3.calcElectricField(3e-6);

Electric_Field E1 = E2 + E3;
std::cout << "Overloaded Electric Field: " << E1.getE() << "\n";

Magnetic_Field M(1,22,333);
M.print();
M.calcMagneticField(10);

Magnetic_Field M2(333,22,1);
M2.print();
M2.calcMagneticField(200);

Magnetic_Field M3(22,1,333);
M3.print();
M3.calcMagneticField(300);

Magnetic_Field M1 = M2 + M3;
std::cout << "Overloaded Magnetic Field: " << M1.getM() << "\n";

return 0;
}

