#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

void mult(double* q1, double* q2, double* res) {
    double w = q1[3]*q2[3] - (q1[0]*q2[0] + q1[1]*q2[1] + q1[2]*q2[2]);

    double x = q1[3]*q2[0] + q2[3]*q1[0] + q1[1]*q2[2] - q1[2]*q2[2];
    double y = q1[3]*q2[1] + q2[3]*q1[1] + q1[2]*q2[0] - q1[0]*q2[2];
    double z = q1[3]*q2[2] + q2[3]*q1[2] + q1[0]*q2[1] - q1[1]*q2[0];
	res[0] = x;
	res[1] = y;
	res[2] = z;
	res[3] = w;
  }

int main(int argc, char* argv[]) {
	if (argc != (5)) {
        	std::cout << "Usage: qx qy qz qw\n";
        	return 1;
	}
	double quatBase[4] = {strtof(argv[1], NULL), strtof(argv[2], NULL), strtof(argv[3], NULL), strtof(argv[4], NULL)};
	double quatX[4] = {-1*sin(M_PI/4), 0, 0, cos(M_PI/4)};
	double quatY[4] = {0, sin((M_PI-0.2)/4), 0, cos((M_PI-0.2)/4)};
	double quatZ[4] = {0, 0, -sin(0.25/4), cos(0.25/4)};
	double quatRes[4];
	mult(quatBase, quatX, quatRes);
	mult(quatRes, quatY, quatRes);
	double quatXBis[4] = {-sin(0.13/2), 0, 0, cos(0.13/2)};
	mult(quatRes, quatXBis, quatRes);
	mult(quatRes, quatZ, quatRes);

	for (int i = 0; i<4; i++) {
		std::cout << quatRes[i] << std::endl;
	}
	return 0;
}
