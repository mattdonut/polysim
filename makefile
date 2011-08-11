CC = c++
DEBUG = -g
LIBS = protobuf protobuf-lite protoc
CFLAGS = -Wall -c -O3 -static `pkg-config --cflags --libs protobuf`
LFLAGS = -Wall -O3 -static `pkg-config --cflags --libs protobuf`
OBJS = Polymer.o Modifier.o Solver.o Sim.o polysim.pb.o main.o

polysim : $(OBJS) main.cpp
	pkg-config --cflags protobuf
	$(CC) $(LFLAGS) $(OBJS) -o polysim `pkg-config --cflags --libs protobuf`

main.o : main.cpp Polymer.h Vect3d.h Modifier.h
	$(CC) $(CFLAGS) main.cpp
	
Polymer.o : Polymer.h Polymer.cpp Vect3d.h
	$(CC) $(CFLAGS) Polymer.cpp
	
Modifier.o : Modifier.h Modifier.cpp Polymer.h Vect3d.h
	$(CC) $(CFLAGS) Modifier.cpp
	
Solver.o : Solver.h Solver.cpp Polymer.h Vect3d.h Modifier.h
	$(CC) $(CFLAGS) Solver.cpp
	
Sim.o : Sim.h Sim.cpp Polymer.h Vect3d.h Solver.h
	$(CC) $(CFLAGS) Sim.cpp
	
polysim.pb.o : polysim.pb.h polysim.pb.cc
	pkg-config --cflags protobuf
	$(CC) $(CFLAGS) polysim.pb.cc `pkg-config --cflags --libs protobuf`
