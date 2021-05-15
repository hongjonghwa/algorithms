import os
import subprocess
from random import randint

REPEAT = 2
INPUT_FILE_NAME = "7469-input.txt"

def make_test_data():
    N = 100000
    M = 5000

    with open(INPUT_FILE_NAME, "w") as f:
        print(f"{N} {M}", file=f)
        for y in range(N):
            print(f"{randint(-1e9,1e9)} ", end='', file=f)
        print(file=f)
        for x in range(M):
            i = randint(1,N)
            j = randint(1,N)
            if (i>j):
                i,j = j,i
            k = randint(1, j-i+1)
            print(f"{i} {j} {k}", end='\n', file=f)


def test():
    print("### run 1 ###")
    result = subprocess.run(['g', '7469-k번째수_ver1_slow.cpp', INPUT_FILE_NAME], stdout=subprocess.PIPE)
    ret1 = result.stdout

    print("### run 2 ###")
    result = subprocess.run(['g', '7469-k번째수_ver2_mergetree.cpp', INPUT_FILE_NAME], stdout=subprocess.PIPE)
    ret2 = result.stdout

    if ret1!=ret2:
        print("### Outputs are not matched! ###")

    return ret1 == ret2

if REPEAT == 1:
    test()
else:        
    for i in range(REPEAT):
        make_test_data()
        r = test()
        if (r == False):
            break
