#ifndef CP_CIRCLE_H
#define CP_CIRCLE_H

class CP_Circle
{
public:
	double radius;

public:
	CP_Circle(int i = 0):radius(i) {}
	~CP_Circle() {}

	double square();           // 面积
	double perimeter();        // 周长

	void initReport();
};

#endif
