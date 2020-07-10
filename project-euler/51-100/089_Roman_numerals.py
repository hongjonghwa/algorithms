import re

rows = open("p089_roman.txt", "r").read()
answer = 0
for r in rows.split():
  ori_len = len(r);
  min_len = len(re.sub("DCCCC|LXXXX|VIIII|CCCC|XXXX|IIII", '__', r))
  shorten = len(r) - len(re.sub("DCCCC|LXXXX|VIIII|CCCC|XXXX|IIII", '__', r))
  answer += ori_len - min_len
  print(r, ori_len, min_len , sep='\t')
print("Answer is", answer)