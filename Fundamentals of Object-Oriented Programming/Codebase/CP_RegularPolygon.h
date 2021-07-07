#ifndef CP_REGULARPOLYGON_H
#define CP_REGULARPOLYGON_H

class CP_RegularPolygon
{
public:
	double sideLength;
	int sideNumber;

public:
	CP_RegularPolygon(int i = 0) { sideNumber = i, sideLength = 0; }
	CP_RegularPolygon(int x, double y) { sideNumber = x, sideLength = y; }
	~CP_RegularPolygon() {}

	double square();           // 面积
	double perimeter();        // 周长

	void initReport();
};

#endif
