#pragma once
#include "Vect3d.h"
#include <vector>
class Polymer
{
public:
	vector<vect_d>  Loc;
	vector<vect_d>  Vel;
	int Length;

	Polymer(int length);
	Polymer(int length, vect_d origin, int seed);
	int pushMonomer(double x, double y, double z);
	~Polymer(void);
};

