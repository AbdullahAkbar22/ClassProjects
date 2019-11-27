import numpy as np

fileNo = input()
#numberNodes = np.random.randint(1, 1025)

numberNodes = 1024

sourceNode = np.random.randint(1, numberNodes + 1)


indices = np.arange(1, numberNodes + 1)

np.random.shuffle(indices)


f = open("input"+fileNo+".txt", "a")
f.write(str(numberNodes) + " " + str(sourceNode) + "\n")


connectedEs = []
print(len(indices))
for i in range(len(indices)):
	if(len(connectedEs) == 0):
		randConnect = np.random.randint(0, len(indices))
		while(randConnect == i):
			randConnect = np.random.randint(0, len(indices))
		randEdge = np.random.randint(1, 201)
		f.write(str(indices[i]) + " " + str(indices[randConnect]) + " "+str(randEdge)+"\n")
		connectedEs.append(indices[i])
		connectedEs.append(indices[randConnect])
	else:
		randConnect = np.random.randint(0, len(connectedEs))
		while(indices[i] == connectedEs[randConnect]):
			randConnect = np.random.randint(0, len(connectedEs))
		randEdge = np.random.randint(1, 201)
		f.write(str(indices[i]) + " " + str(connectedEs[randConnect]) + " "+str(randEdge)+"\n")
		connectedEs.append(indices[i])
	#print("On i: " + str(i))

f.write("0 0 0\n")
f.close()