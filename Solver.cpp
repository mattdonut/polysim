#include "Solver.h"
//#include <iostream>
Solver::Solver(void)
{

}


Solver::~Solver(void)
{
}

void
Solver::initSys(vector<Polymer*> sys)
{
	sys0.clear();
	sys1.clear();
	sys2.clear();
	sys3.clear();
	sys0 = sys;
	for(unsigned int i=0; i< sys.size(); i++){
		sys1.push_back(new Polymer(sys[i]->Length));
		sys2.push_back(new Polymer(sys[i]->Length));
		sys3.push_back(new Polymer(sys[i]->Length));
	}
	mods.clear();
	mods.push_back(new PinBackbone(sys,100,100,10));
	mods.push_back(new OseenTensor(sys,.1));
	mods.push_back(new KinesinShift(1));
}

void 
Solver::SetStepSize(double size)
{
	h = size;
	h2 = size/2.0;
	h6 = size/6.0;
}

int
Solver::TakeSteps(int num_steps)
{
	int taken = 0;
	for(int i=0;i<num_steps;i++){

		//do hella stuff here
		//cout << "Starting sub step " << i << endl;
		//clear old velocities
		for(unsigned i=0; i<sys0.size(); i++){
			for(int j=0;j<sys0[i]->Length;j++){
				sys0[i]->Vel[j].set(0,0,0);
				sys1[i]->Vel[j].set(0,0,0);
				sys2[i]->Vel[j].set(0,0,0);
				sys3[i]->Vel[j].set(0,0,0);
			}
		}
		//act forces at initial point (k1)
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys0);
		}
		//cout << "Finished acting forces..." <<endl;

		//determine the locations for the first midpoint step
		for(unsigned i=0; i<sys0.size(); i++){
			for(int j=0;j<sys0[i]->Length;j++){
				sys1[i]->Loc[j] = sys0[i]->Loc[j] + sys0[i]->Vel[j]*h2;
			}
		}

		//act forces at second point (k2)
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys1);
		}

		//determine locations for the second midpoint step
		for(unsigned i=0; i<sys1.size(); i++){
			for(int j=0;j<sys1[i]->Length;j++){
				sys2[i]->Loc[j] = sys0[i]->Loc[j] + sys1[i]->Vel[j]*h2;
			}
		}

		//calculate forces for the third midpoint step
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys2);
		}
		//determine the locations for the third midpoint step
		for(unsigned i=0; i<sys2.size(); i++){
			for(int j=0;j<sys2[i]->Length;j++){
				sys3[i]->Loc[j] = sys0[i]->Loc[j] + sys2[i]->Vel[j]*h;
			}
		}
		//calculate forces for the endpoint
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys3);
		}
		//apply the transform to the whole system
		for(unsigned i=0; i<sys3.size(); i++){
			for(int j=0;j<sys3[i]->Length;j++){
				sys0[i]->Loc[j] += (sys0[i]->Vel[j] + sys3[i]->Vel[j] + (sys1[i]->Vel[j] + sys2[i]->Vel[j])*2.0)*h6;
			}
		}

		taken++;
	}
	return taken;
}
