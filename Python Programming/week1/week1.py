import os
import sys

os.chdir(sys.path[0])
f = open("output.txt", "w")
print("I love python\n"*99, file=f)
f.close()
