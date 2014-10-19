#!/usr/bin/python

import matplotlib.cm as cm
import matplotlib.pyplot as plt
import numpy
import sys

infile = sys.argv[1]
data = numpy.loadtxt(infile, dtype="int")

plt.imshow(data, cmap=cm.Greys_r)
plt.show()
