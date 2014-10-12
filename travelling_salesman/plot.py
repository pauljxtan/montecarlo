#!/usr/bin/env python

from matplotlib import pyplot
import sys

def main():
    pyplot.ion()

    fig = pyplot.figure()
    sp = fig.add_subplot(111)
    t = 0

    while True:
        data = sys.stdin.readline()
        if data == '':
            break
        t += 1
        data = data.split(" ")
        dist = float(data[0])
        data = data[1:]
        data = map(int, data)
        x = []
        y = []
        i = 0
        while i < len(data):
            x.append(data[i])
            y.append(data[i + 1])
            i += 2
        sp.clear()
        sp.set_title("t=%d, dist=%f" % (t, dist))
        sp.plot(x, y, 'ko-')
        pyplot.draw()

if __name__ == '__main__':
    sys.exit(main())
