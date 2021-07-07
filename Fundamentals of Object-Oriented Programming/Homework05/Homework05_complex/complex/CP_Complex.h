#ifndef CP_COMPLEX_H
#define CP_COMPLEX_H

class CP_Complex
{
public:
	double m_real, m_imaginary;

public:
	CP_Complex(double Real = 0, double Imaginary = 0) { m_real = Real, m_imaginary = Imaginary; }
	~CP_Complex() {}

	void mb_show(const char* s);
};

extern CP_Complex operator + (CP_Complex& c1, CP_Complex& c2);
extern CP_Complex operator + (double& c1, CP_Complex& c2);
extern CP_Complex operator + (CP_Complex& c1, double& c2);
extern CP_Complex operator + (int& c1, CP_Complex& c2);
extern CP_Complex operator + (CP_Complex& c1, int& c2);

extern CP_Complex operator - (CP_Complex& c1, CP_Complex& c2);
extern CP_Complex operator - (double& c1, CP_Complex& c2);
extern CP_Complex operator - (CP_Complex& c1, double& c2);
extern CP_Complex operator - (int& c1, CP_Complex& c2);
extern CP_Complex operator - (CP_Complex& c1, int& c2);

extern CP_Complex operator * (CP_Complex& c1, CP_Complex& c2);
extern CP_Complex operator * (double& c1, CP_Complex& c2);
extern CP_Complex operator * (CP_Complex& c1, double& c2);
extern CP_Complex operator * (int& c1, CP_Complex& c2);
extern CP_Complex operator * (CP_Complex& c1, int& c2);

extern CP_Complex operator / (CP_Complex& c1, CP_Complex& c2);
extern CP_Complex operator / (double& c1, CP_Complex& c2);
extern CP_Complex operator / (CP_Complex& c1, double& c2);
extern CP_Complex operator / (int& c1, CP_Complex& c2);
extern CP_Complex operator / (CP_Complex& c1, int& c2);

extern CP_Complex& operator ++ (CP_Complex& c);
extern CP_Complex operator ++ (CP_Complex& c, int);
extern CP_Complex& operator -- (CP_Complex& c);
extern CP_Complex operator -- (CP_Complex& c, int);

extern bool operator == (CP_Complex& c1, CP_Complex& c2);
extern bool operator != (CP_Complex& c1, CP_Complex& c2);

#endif
