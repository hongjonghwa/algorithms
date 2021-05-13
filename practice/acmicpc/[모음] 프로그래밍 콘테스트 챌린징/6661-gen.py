import os
import subprocess
from random import randint

REPEAT = 1
INPUT_FILE_NAME = "6661-input.txt"

def make_test_data():
    N = 10000
    C = 10000

    with open(INPUT_FILE_NAME, "w") as f:
        print(f"{N} {C}", file=f)
        for y in range(N):
            print(f"{randint(1,100)} ", end='', file=f)
        print(file=f)
        for x in range(C):
            print(f"{randint(1,99)} {randint(0,359)}", end='\n', file=f)


def test():
    print("### run 1 ###")
    result = subprocess.run(['g', '6661-크레인.cpp', INPUT_FILE_NAME], stdout=subprocess.PIPE)
    ret1 = result.stdout

    print("### run 2 ###")
    result = subprocess.run(['g', '6661-크레인_ver1.cpp', INPUT_FILE_NAME], stdout=subprocess.PIPE)
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
