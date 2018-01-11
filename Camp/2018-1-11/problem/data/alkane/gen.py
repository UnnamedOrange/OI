import os
from random import randint

problem_name = "alkane"

def gen(lb, ub=None):
    ret = ""
    ret += "1\n"
    if ub == None:
        ub = lb
    ret += "%d\n" % (randint(lb, ub))
    return ret

def gen2(T):
    ret = ""
    ret += "%d\n" % (T)
    for t in range(T):
        ret += "%d\n" % (t + 1)
    return ret

def Gen(id):
    print("Generating testcase #%d:" % (id))
    f = open(problem_name + "%d.in" % (id), "w")
    outp = ""

    if id ==  0: outp = gen(8)
    if id ==  1: outp = gen(100, 200)
    if id ==  2: outp = gen(150, 200)
    if id ==  3: outp = gen(1000, 2000)
    if id ==  4: outp = gen(1500, 2000)
    if id ==  5: outp = gen(1500, 2000)
    if id ==  6: outp = gen(66666)
    if id ==  7: outp = gen(23333)
    if id ==  8: outp = gen(90000, 100000)
    if id ==  9: outp = gen(95000, 100000)
    if id == 10: outp = gen(99500, 100000)
    if id == 11: outp = gen(99950, 100000)
    if id == 12: outp = gen2(100000)

    print(outp, file=f, end="")
    f.close()
    os.system("time ./" + problem_name + " < " + problem_name + "%d.in > " % (id) + problem_name + "%d.out" % (id))
    # os.system("cat " + problem_name + "%d.out" % (id))

for id in range(6, 8):
    Gen(id)
