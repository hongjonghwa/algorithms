import os
import subprocess
from random import randint

def test():    
    N = 10000
    C = 100

    
    with open("6661-gen-input.txt", "w") as f:
        print(f"{N} {C}", file=f)
        for y in range(N):
            print(f"{randint(1,100)} ", end='', file=f)
        print(file=f)
        for x in range(C):
            print(f"{randint(1,99)} {randint(0,359)}", end='\n', file=f)

    print("### run 1 ###")
    result = subprocess.run(['g', '6661-크레인.cpp', '6661-gen-input.txt'], stdout=subprocess.PIPE)
    ret1 = result.stdout

    print("### run 2 ###")
    result = subprocess.run(['g', '6661-크레인.cpp', '6661-gen-input.txt'], stdout=subprocess.PIPE)
    ret2 = result.stdout

    if ret1!=ret2:
        print(ret1)
        print(ret2)

    return ret1 == ret2

for i in range(1):
    r = test()
    if (r == False):
        print("Outputs are not matched")
        break