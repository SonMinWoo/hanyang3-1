import sys
'''
Simple FIFO page replacement algorithm
'''
def FIFO(size, pages):
    SIZE = size
    memory = []
    faults = 0
    for page in pages:
        if memory.count(page) == 0 and len(memory) < SIZE: 
            memory.append(page)
            faults += 1
        elif memory.count(page) == 0 and len(memory) == SIZE:
            memory.pop(0)
            memory.append(page)
            faults += 1
    return faults
 
''' 
LRU algorithm
'''
def LRU(size, pages):
    SIZE = size
    memory = []
    faults = 0
    for page in pages:
        if memory.count(page) == 0 and len(memory) < SIZE: 
            memory.append(page)
            faults += 1
        elif memory.count(page) == 0 and len(memory) == SIZE:
            memory.pop(0) 
            memory.append(page) 
            faults += 1
        elif memory.count(page) > 0:
            memory.remove(page)
            memory.append(page)
    return faults
 
'''
Optimal algorithm
'''
def OPT(size,pages):
	faults = 0
	'''
	TODO
	'''
	return faults
def main():
    pages = (7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1)
    size = 3
    print 'reference string\n',pages
    print 'FIFO\n', FIFO(size,pages), 'page faults.'
    print 'LRU\n', LRU(size,pages), 'page faults.'
    print 'OPT', OPT(size,pages), 'page faults.'
 
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print 'Usage: python paging.py [number of pages]'
    else:
        main()