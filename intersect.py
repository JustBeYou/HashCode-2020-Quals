from sys import argv

name = argv[1]
f = open(name,'r').read()
f = [x.split(' ') for x in f.split('\n') if x != '']

bookTotal, libTotal, dayTotal = map(int, f[0:3])
bookScores = map(int, f[3:3+bookTotal])