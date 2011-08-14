#include "Sim.h"
#include "Vect3d.h"

Sim::Sim(void)
{
	sol = new Solver();
}

Sim::~Sim(void)
{
	sys.clear();
	delete sol;
}

void
Sim::initSys(void)
{
	sol->initSys(sys,yolk,pk,sk,stiffk,oseenk,shiftk,numpin);
}

void
Sim::addPolymer(double x, double y, double z, int size, int seed)
{
	sys.push_back(new Polymer(size, vect_d(x,y,z), seed));
}
void
Sim::addPolymer(Polymer * poly){
	sys.push_back(poly);
}

int
Sim::takeSteps(int steps)
{
	return sol->TakeSteps(steps);
}

void
Sim::setOutputFile(char * filename){

}