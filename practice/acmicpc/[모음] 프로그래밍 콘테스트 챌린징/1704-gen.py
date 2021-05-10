import os
import subprocess
from random import randint

def test():    
    M = randint(1,1)
    N = randint(1,5)

    with open("1704-gen-input.txt", "w") as f:
        print(f"{M} {N}", file=f)
        for y in range(M):
            for x in range(N):
                print(f"{randint(0,1)} ", end='', file=f)
            print(file=f)

    # result = subprocess.run(['./1704-test1'], input="1704-gen-input.txt", stdout=subprocess.PIPE)
    result = subprocess.run(['g', '1704-붕어빵타이쿤.cpp', '1704-gen-input.txt'], stdout=subprocess.PIPE)
    ret1 = result.stdout


    result = subprocess.run(['g', '1704-ver2.cpp', '1704-gen-input.txt'], stdout=subprocess.PIPE)
    ret2 = result.stdout

    if ret1!=ret2:
        print(ret1)
        print(ret2)

    return ret1 == ret2

for i in range(100):
    r = test()
    if (r == False):
        break