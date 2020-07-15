import os

GCC = "gcc"
MICRO_PAINT = "micro_paint.c"

# 내가 만든 파일 컴파일
os.system("{} {}".format(GCC, MICRO_PAINT))

PATH = "./examples/"
test_list = os.listdir(PATH)

DIFF = "diff"
A_OUT = "./a.out"
ORIGIN = "./origin"
MY_TXT = "my.txt"
ORIGIN_TXT = "origin.txt"

for i in test_list:
    print(i)
    os.system("{} {}{} > {}".format(A_OUT, PATH, i, MY_TXT))
    os.system("{} {}{} > {}".format(ORIGIN, PATH, i, ORIGIN_TXT))
    os.system("diff {} {}".format(MY_TXT, ORIGIN_TXT))