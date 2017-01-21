'''
Created on 06.11.2013
@author: Esir Pavel
'''
import csv
import numpy as np
import matplotlib.pyplot as pl


#pl.ion()
f = open("./rastr0.csv", "r")
rdr = csv.reader(f,delimiter=";")
times = []
neurons = []
for l in rdr:
    times.append(l[0])
    neurons.append(l[1])
f.close()
    
times = np.array(times, dtype="float")
neurons = np.array(neurons, dtype="int")
pl.figure()
ax00 = pl.subplot(211)
ax10 = pl.subplot(212, sharex = ax00)
ax00.plot(times, neurons, ".k")
ax00.set_ylim([0, max(neurons)])
ax00.set_title(u"raster of activity")
ax00.set_ylabel(u"neur number")
ax00.set_xlim([0., times[-1]])
ax00.grid()
hi = ax10.hist(times, bins = int(times[-1]), histtype='step', color = 'b')
ax10.set_ylim(0., max(hi[0]))
ax10.set_ylabel(u"number of spikes in 1 ms")
ax10.set_xlabel(u"time, ms")
ax10.grid()
pl.savefig('rastr.png') 
pl.show() 