#include <iostream>
//#include <random>
#include <fstream>
#include <vector>
#include "Vect3d.h"
#include "Polymer.h"
#include "Solver.h"
#include "Sim.h"
//#include <fcntl.h>
#include "polysim.pb.h"
using namespace std;

void outputPolys(vector<Polymer*>, ofstream&);
void savePolys(vector<Polymer*>, polysim::SSystem*);
void readSaveSim(Sim* sim, polysim::SSim& save);
int main(int argc, char* argv[]){
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	int numsteps = 100;
	if(argc > 2){
		numsteps = atoi(argv[2]);
	}
	int start_step = 0;
	//ofstream outfile("bdata.dat", ios::out | ios::binary | ios::trunc);
	//cout << sizeof(vect_d);
	//Polymer * poly = new Polymer(200,vect_d(0,0,0),123);
	//for(int i=0; i< poly->Length; i++){
	//	cout << poly->Loc[i];
	//}
	//outfile.write((const char*)&poly->Length, sizeof(poly->Length));
	//outfile.write((const char*)&poly->Loc[0], poly->Length * sizeof(vect_d));
	//outfile.close();

	//ifstream ifile("bdata.dat", ios::in | ios::binary);
	//int size;
	//ifile.read((char*)&size, sizeof(int));
	//Polymer * poly2 = new Polymer(size);
	//ifile.read((char*)&poly2->Loc[0], size* sizeof(vect_d));

	//for(int i=0; i< poly2->Length; i++){
	//	cout << poly2->Loc[i];
	//}


	polysim::SSim saveSim;
	fstream input(argv[1], ios::in | ios::binary);
	if(!input){
		cout<<":File fail, making new file." <<endl;
	}else if (!saveSim.ParseFromIstream(&input) ) {
		cerr << "FAIL" << endl;
		return -1;
	}



//	std::tr1::mt19937 mt(5432);
//	std::tr1::uniform_real<double> dist(-.5,.5);
	//ofstream output;
	//output.open("out.dat",ios::out|ios::trunc);

	Sim * sim = new Sim();
	fstream soutput;

	if(saveSim.system_size() > 0 ){
		readSaveSim(sim, saveSim);
		start_step = saveSim.system_size();
	}
	else{
		for(int i=0; i<10; i++){
			for(int j=0; j<10; j++){
				sim->addPolymer(2*j,2*i,1,20,100*i+j);
			}
		}

	}

	sim->initSys();
	sim->sol->SetStepSize(.003);
	cout << "Going for " << numsteps << " steps(" << start_step << "-"<<start_step+numsteps<<")"<< endl;
	//output << "[";
	for(int steps=start_step; steps < start_step+numsteps; steps++){
		cout<<"Starting steps..."<<endl;
		sim->takeSteps(100);
		//outputPolys(sim->sys, output);
		//output << ",";
		cout << steps << endl;
		cout<< "Saving progress, do not interupt!"<<endl;
		savePolys(sim->sys, saveSim.add_system());
		soutput.open(argv[1], ios::out | ios::trunc | ios::binary);
		if (!saveSim.SerializeToOstream(&soutput)) {
			cout << "FAIL OUTPUT" << endl;
			return -1;
		}
		soutput.close();
		cout<<"Save complete."<<endl;
	}
	//output.seekp(-1,ios::cur);
	//output << "]";
	//output.close();
	return 0;
}

void outputPolys(vector<Polymer*> sys, ofstream& file){
	file << "[";
	for(unsigned int i=0; i< sys.size(); i++){
		file << "[";
		for(int j=0; j< sys[i]->Length; j++){
			file << sys[i]->Loc[j];
			file << ",";
		}
		file.seekp(-1,ios::cur);
		file << "],";
	}
	file.seekp(-1,ios::cur);
	file << "]";
}
void savePolys(vector<Polymer*> sys, polysim::SSystem* save){

	for(unsigned int i=0; i< sys.size(); i++){
		polysim::SPolymer * poly = save->add_poly();
		for(int j=0; j< sys[i]->Length; j++){
			poly->add_x(sys[i]->Loc[j].xcomp() );
			poly->add_y(sys[i]->Loc[j].ycomp() );
			poly->add_z(sys[i]->Loc[j].zcomp() );
		}

	}
}
void readSaveSim(Sim* sim, polysim::SSim& save){
	cout<<"reading from file..."<<endl;
	const polysim::SSystem savesys = save.system(save.system_size()-1);
	sim->sk = save.settings().sk();
	sim->pk = save.settings().pk();
	sim->stiffk = save.settings().stiffk();
	sim->oseenk = save.settings().oseenk();
	sim->shiftk = save.settings().shiftk();
	sim->numpin = save.settings().numpin();
	Polymer * poly;
	for(int i=0; i < savesys.poly_size() ; i++){
		poly = new Polymer(0);
		const polysim::SPolymer savepoly = savesys.poly(i);
		for(int j=0; j < savepoly.x_size() ; j++){
			poly->pushMonomer(savepoly.x(j),savepoly.y(j),savepoly.z(j));
		}
		sim->addPolymer(poly);
	}
}
