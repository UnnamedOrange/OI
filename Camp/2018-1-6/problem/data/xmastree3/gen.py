#!/usr/bin/env python3

import sys, os
from random import *

def Gen(caseid, n, k):
    outp = "%d %d\n" % (n, k)
    id = sample([i for i in range(n)], n)
    for i in range(1, n):
        outp += "%d %d\n" % (id[randint(0, i - 1)] + 1, id[i] + 1)

    fname = "xmastree%s" % (caseid)
    print(outp, file=open("%s.in" % (fname), "w"))
    os.system("time ./std < %s.in > %s.out" % (fname, fname))

Gen(0, 4, 4)
Gen(1, 6, 7)
Gen(2, 7, 7)
Gen(3, 10, 8)
Gen(4, 39, 8)
Gen(5, 49, 8)
Gen(6, 48, 14)
Gen(7, 47, 15)
Gen(8, 49, 15)
Gen(9, 50, 15)
