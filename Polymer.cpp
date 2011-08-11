#include "Polymer.h"
//#include <random>
#include <math.h>

Polymer::Polymer(int length)
{
	Length = length;
	//Loc = new vect_d[length];
	//Vel = new vect_d[length];
	for(int i=0;i<length;i++){
		Loc.push_back(vect_d(0,0,0));
		Vel.push_back(vect_d(0,0,0));
	}
}
Polymer::Polymer(int length, vect_d origin, int seed)
{
	Length = length;
	Loc.push_back(origin);
	Vel.push_back(vect_d(0,0,0));
//	std::tr1::mt19937 mt((unsigned long)seed);
//	std::tr1::uniform_real<double> dist(-1.0,1.0);
	int i = 1;
	vect_d temp;
	double size;
	do{
		temp = vect_d(.5,.5,.5);
		size = temp*temp;
		if(size > 1.0 || size == 0.0){
			continue;
		}
		temp /= sqrt(size);
		Loc.push_back(Loc[i-1] + temp);
		Vel.push_back(vect_d(0,0,0));
		i++;
	} while(i < length);
}

int
Polymer::pushMonomer(double x, double y, double z) {
	Loc.push_back(vect_d(x,y,z));
	Vel.push_back(vect_d(0,0,0));
	Length++;
	return Length;
}

Polymer::~Polymer(void)
{
	Loc.clear();
	Vel.clear();
}
