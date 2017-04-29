#!/usr/bin/python3

import random
import sys

argv = sys.argv

if(len(argv) != 6):
	print("Usage generate policy N numFrames virtualAddressSpaceSize outputFileName")

policy, N, numFrames, virtualAddressSpaceSize = [int(x) for x in argv[1:5]]
outputFileName = argv[5]

assert(virtualAddressSpaceSize > N);
assert(pow(2, virtualAddressSpaceSize) > numFrames * pow(2,N))

with open(outputFileName, "w") as f:
	f.write("\n".join([str(x) for x in [policy, N, numFrames, virtualAddressSpaceSize]]))
	f.write("\n")
	for i in range(100):
		f.write("%d\n" % (random.randint(0, 2**virtualAddressSpaceSize - 1)))
