#!/bin/bash

set -e
tl=3s
dir=$1
g++ $dir/xmasset.cpp -o $dir/xmasset -O2 -std=c++11
timeout $tl $dir/xmasset < xmasset.in1 > xmasset.ou1
./jury_helper xmasset.txt xmasset.ou1 xmasset.in2 xmasset.res
timeout $tl $dir/xmasset < xmasset.in2 > xmasset.ou2
diff -Bbq xmasset.ou2 xmasset.ans

# f=1
# cnt=0
# while read -u 10 a; do
#     ((++cnt))
#     if [ $(($cnt%1000)) == 0 ]; then
#         echo $cnt
#     fi
#     if [ $f ]; then
#         f=0
#         echo -e "2\n$a" > /tmp/_xmasset.in2
#         > /tmp/_xmasset.ans
#     else
#         read -u 11 b
#         arr=($a)
#         t=$(($RANDOM%2))
#         echo "${arr[$t]} $b" >> /tmp/_xmasset.in2
#         echo $([ $t ] && "yes" || "no") >> /tmp/_xmasset.ans
#     fi
# done 10<"$inp" 11</tmp/_xmasset.ou1
