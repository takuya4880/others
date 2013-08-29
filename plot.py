#!/bin/env python

from numpy import *
import pylab as plt

x=linspace(-pi,pi,100)
y=sin(x)

plt.plot(x,y,color="b", linestyle="steps")
plt.show()
