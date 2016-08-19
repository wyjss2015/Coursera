#! -*- coding:utf8 -*-

hashTable = set([]);
def createHashTable():
	with open('2sum.txt', 'r') as f:
		for line in f.readlines():
			hashTable.add(int(line.strip()))

def count():
	cnt = 0
	L = list(hashTable)
	for t in xrange(-10000, 10001, 1):
		for x in L:
			y = t-x
			if y != x and y in hashTable:
				cnt += 1
				print '第%d个数,%d = %d + %d'%(cnt, t, x, y)
				break
	return cnt

if __name__ == '__main__':
	createHashTable()
	print count()
