#!/usr/bin/env python3

import sys, os
from random import *

def Gen(caseid, n, m, k):
    n -= randint(0, 5)
    m -= randint(0, 5)
    assert m >= n
    chainlen = n // 2

    outp = "%d %d %d\n" % (n, m, k)
    for i in range(1, chainlen):
        outp += "%d %d\n" % (randint(max(1, i - 2), i), i + 1)
    for i in range(chainlen, n):
        outp += "%d %d\n" % (randint(chainlen, i), i + 1)
    for i in range(n, m + 1):
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        outp += "%d %d\n" % (u, v)

    fname = "xmasdag%s" % (caseid)
    print(outp, file=open("%s.in" % (fname), "w"))
    os.system("time ./std < %s.in > %s.out" % (fname, fname))
    if os.system("timeout 2s ./bf <%s.in > bf.out" % (fname)) == 0 and os.system("diff %s.out bf.out -b" % (fname)) != 0:
        os.abort()

Gen(0, 1000, 5000, 100 - randint(0, 5))
Gen(1, 2000, 5000, 500 - randint(0, 5))
Gen(2, 100000, 200000, 1)
Gen(3, 50000, 200000, 20)
Gen(4, 100000, 200000, 30)
Gen(5, 50000, 200000, 100 - randint(0, 5))
Gen(6, 50000, 200000, 200 - randint(0, 5))
Gen(7, 50000, 200000, 500 - randint(0, 5))
Gen(8, 100000, 200000, 500 - randint(0, 5))
Gen(9, 100000, 200000, 500)
