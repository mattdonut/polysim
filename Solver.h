#pragma once
#include <vector>
#include "Polymer.h"
#include "Modifier.h"

class Solver
{
public:
	double h;
	double h2;
	double h6;
	vector<Polymer*> sys0, sys1, sys2, sys3;
	Polymer * yolk0, * yolk1, * yolk2, * yolk3;
	Solver(void);
	~Solver(void);

	void initSys(vector<Polymer*> sys, Polymer* yolk, double initpk, double initsk, double initstiffk, double oseenk, double shiftk, int numpin );
	void SetStepSize(double);
	int TakeSteps(int);
	vector<Modifier*> mods;
};

