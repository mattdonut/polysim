#pragma once

#include <vector>
#include "Polymer.h"
#include "Solver.h"

class Sim
{
public:
	Sim(void);
	~Sim(void);

	void addPolymer(double x,double y,double z, int size, int seed);
	void addPolymer(Polymer * poly);
	int takeSteps(int steps);
	void initSys(void);
	void setOutputFile(char * filename);
	vector<Polymer*> sys;
	Polymer * yolk;
	Solver * sol;
	double sk, pk, stiffk, oseenk, shiftk;
	int numpin;
};

