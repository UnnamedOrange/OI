#!/usr/bin/env python3

import sys, os
from random import *

def Gen(n, t):
    outp0 = "%d %d\n" % (n, t)
    outp_in1 = "1\n%d %d\n" % (n, t)
    outp_ans = ""
    for i in range(t):
        a = sample(range(1, n), 2)
        t = randint(0, 1)
        outp0 += "%d %d %d\n" % (a[0], a[1], a[t])
        outp_in1 += "%d %d\n" % (a[0], a[1])
        outp_ans += ["yes", "no"][t] + "\n"
    print(outp0, file=open("xmasset.txt", "w"))
    print(outp_in1, file=open("xmasset.in1", "w"))
    print(outp_ans, file=open("xmasset.ans", "w"))

Gen(920, 2000000)
