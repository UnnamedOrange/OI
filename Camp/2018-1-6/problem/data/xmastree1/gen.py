#!/usr/bin/env python3

import sys, os
from random import *

def Gen(caseid, n, q, o, typelim):
    n -= randint(0, 5)
    q -= randint(0, 5)
    id = [0, n - 1] + sample([i + 1 for i in range(n - 2)], n - 2)
    chainlen = n // 2

    outp0 = "%d %d 0\n" % (n, q)
    outp1 = ""
    outp2 = ""
    for i in range(n):
        outp1 += "%d " % (randint(1, n))
    outp1 += "\n"
    for i in range(1, chainlen):
        outp1 += "%d %d\n" % (id[i] + 1, id[randint(max(1, i - 2), i) - 1] + 1)
    for i in range(chainlen, n):
        outp1 += "%d %d\n" % (id[i] + 1, id[randint(chainlen, i) - 1] + 1)
    for i in range(q):
        tp = randint(1, typelim)
        if tp == 1:
            u = id[min(n - 1, int(expovariate(1.0 / chainlen)))] + 1
            len = max(1, n - int(expovariate(1.0 / (n // 2))))
            l = randint(1, n - len + 1)
            r = l + len - 1
            outp2 += "1 %d %d %d\n" % (u, l, r)
        else:
            u = randint(1, n)
            c = randint(1, n)
            outp2 += "2 %d %d\n" % (u, c)

    fname = "xmastree%s" % (caseid)
    print(outp0 + outp1 + outp2, file=open("%s.in" % (fname), "w"))
    os.system("time ./std < %s.in > %s.out" % (fname, fname))
    if os.system("timeout 2s ./bf <%s.in > bf.out" % (fname)) == 0 and os.system("diff %s.out bf.out -b" % (fname)) != 0:
        os.abort()

    if o:
        anslist = list(map(int, open("%s.out" % (fname), "r").read().split()))
        outp0 = "%d %d 1\n" % (n, q)
        outp2_ = ""
        lastans = 0
        pos = 0
        for line in outp2.splitlines():
            outp2_ += line[0:2] + ' '.join(str(int(s) ^ lastans) for s in line[2:].split()) + '\n'
            if line[0] == '1':
                lastans = anslist[pos]
                pos += 1
        print(outp0 + outp1 + outp2_, file=open("%s.in" % (fname), "w"))

Gen(0, 500, 500, 0, 2)
Gen(1, 5000, 5000, 1, 2)
Gen(2, 50000, 50000, 1, 2)
Gen(3, 50000, 50000, 1, 2)
Gen(4, 100000, 100000, 1, 1)
Gen(5, 100000, 100000, 1, 1)
Gen(6, 100000, 100000, 0, 2)
Gen(7, 100000, 100000, 0, 2)
Gen(8, 100000, 100000, 1, 2)
Gen(9, 100000, 100000, 1, 2)
