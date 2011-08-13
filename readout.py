import polysim_pb2
import sys
import os
file = open(sys.argv[1],"rb")
if sys.argv[1] == "jsonify.py":
	raise Exception()
sim = polysim_pb2.SSim()
sim.ParseFromString(file.read())
print("Settings")
print(sim.settings)
print("number of frames: ")
print(len(sim.system))