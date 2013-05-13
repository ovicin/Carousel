import sys
import re

fit = open('performance_inefable.EDL')
inputLines = fit.readlines()
fit.close()

for line in inputLines:
    if re.search('      1     1',line)>=0:
		print line.split(' ')
		break