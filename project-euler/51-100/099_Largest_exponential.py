import math

max_value = 0
best = -1
with open('p099_base_exp.txt') as f:
  for i, line in enumerate(f): # read rest of lines
    base, exponent = [int(x) for x in line.split(",")]
    # print (i, base, exponent)
    val = math.log10(base)*exponent
    if val > max_value:
      max_value = val
      best = i

print(best+1)