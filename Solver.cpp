#include "Solver.h"
//#include <iostream>
Solver::Solver(void)
{

}


Solver::~Solver(void)
{
}
//pk, sk = 100, stiffk = 10, oseenk = .1, shiftk = 1
void
Solver::initSys(vector<Polymer*> sys, Polymer* yolk, double initpk, double initsk, double initstiffk, double oseenk, double shiftk, int numpin )
{
	sys0.clear();
	sys1.clear();
	sys2.clear();
	sys3.clear();
	sys0 = sys;
	yolk1 = new Polymer(yolk->Length);
	yolk2 = new Polymer(yolk->Length);
	yolk3 = new Polymer(yolk->Length);
	yolk0 = yolk;
	for(unsigned int i=0; i< sys.size(); i++){
		sys1.push_back(new Polymer(sys[i]->Length));
		sys2.push_back(new Polymer(sys[i]->Length));
		sys3.push_back(new Polymer(sys[i]->Length));
	}
	mods.clear();
	mods.push_back(new PinBackbone(sys,initpk,initsk,initstiffk,numpin));
	mods.push_back(new OseenTensor(sys,oseenk));
	mods.push_back(new KinesinShift(shiftk));
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
		for(int j=0; j<yolk0->Length; j++){
			yolk0->Vel[j].set(0,0,0);
			yolk1->Vel[j].set(0,0,0);
			yolk2->Vel[j].set(0,0,0);
			yolk3->Vel[j].set(0,0,0);
		}
		//act forces at initial point (k1)
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys0,yolk0);
		}
		//cout << "Finished acting forces..." <<endl;

		//determine the locations for the first midpoint step
		for(unsigned i=0; i<sys0.size(); i++){
			for(int j=0;j<sys0[i]->Length;j++){
				sys1[i]->Loc[j] = sys0[i]->Loc[j] + sys0[i]->Vel[j]*h2;
			}
		}
		for(int i=0; i<yolk0->Length; i++){
			yolk1->Loc[i] = yolk0->Loc[i] + yolk0->Vel[i]*h2;
		}

		//act forces at second point (k2)
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys1,yolk1);
		}

		//determine locations for the second midpoint step
		for(unsigned i=0; i<sys1.size(); i++){
			for(int j=0;j<sys1[i]->Length;j++){
				sys2[i]->Loc[j] = sys0[i]->Loc[j] + sys1[i]->Vel[j]*h2;
			}
		}
		for(int i=0; i<yolk0->Length; i++){
			yolk2->Loc[i] = yolk0->Loc[i] + yolk1->Vel[i]*h2;
		}

		//calculate forces for the third midpoint step
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys2,yolk2);
		}
		//determine the locations for the third midpoint step
		for(unsigned i=0; i<sys2.size(); i++){
			for(int j=0;j<sys2[i]->Length;j++){
				sys3[i]->Loc[j] = sys0[i]->Loc[j] + sys2[i]->Vel[j]*h;
			}
		}
		for(int i=0; i<yolk0->Length; i++){
			yolk3->Loc[i] = yolk0->Loc[i] + yolk2->Vel[i]*h;
		}

		//calculate forces for the endpoint
		for(unsigned int i=0; i<mods.size(); i++) {
			mods[i]->Act(sys3,yolk3);
		}
		//apply the transform to the whole system
		for(unsigned i=0; i<sys3.size(); i++){
			for(int j=0;j<sys3[i]->Length;j++){
				sys0[i]->Loc[j] += (sys0[i]->Vel[j] + sys3[i]->Vel[j] + (sys1[i]->Vel[j] + sys2[i]->Vel[j])*2.0)*h6;
			}
		}
		for(unsigned i=0;i<yolk0->Length;i++){
			yolk0->Loc[i] += (yolk0->Vel[i] + yolk3->Vel[i] + (yolk1->Vel[i] + yolk2->Vel[i])*2.0)*h6;
		}

		taken++;
	}
	return taken;
}
