#!/usr/bin/env python

from matplotlib import pyplot
import numpy
import sys

def main():
    pyplot.ion()

    fig = pyplot.figure()
    sp = fig.add_subplot(111)
    sp.grid(True)

    frameskip = 10
    t = 0

    while True:
        data = sys.stdin.readline()
        if data == '':
            break
        t += 1
        data = data.split(" ")
        t = float(data[0])
        x = int(data[1])
        y = int(data[2])
        disp = float(data[3])
        sp.set_title("t=%d, disp=%f" % (t, disp))
        sp.scatter(x, y, c='k')
        if t % frameskip == 0:
            pyplot.draw()

if __name__ == '__main__':
    sys.exit(main())
