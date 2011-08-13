import polysim_pb2
import sys
import os
import numpy as np

outfile = open('gen.dat',"wb")
sim = polysim_pb2.SSim()

sim.settings.sk = 100
sim.settings.pk = 100
sim.settings.stiffk = 10
sim.settings.oseenk = .1
sim.settings.shiftk = 1
sim.settings.numpin = 1

sys = sim.system.add()



for i in range(4):
    for j in range(4):
        poly = sys.poly.add()
        current = np.array([i,j,1])
        for n in range(20):
            poly.x.append(current[0])
            poly.y.append(current[1])
            poly.z.append(current[2])
            
            temp = np.random.rand(3) - np.array([.5,.5,0])
            temp = temp/np.linalg.norm(temp)
            current = current + temp
print(sim)
output = sim.SerializeToString()
outfile.write(output)
