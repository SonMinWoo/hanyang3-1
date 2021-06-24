'''
Optimal algorithm
'''
import sys

pages = (7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1)
size = 3

def search(now, pages):
    distance = 0
    switch = True
    
    for i in pages:
        if i == now:
            break
        distance += 1
    
    return distance


def OPT(size,pages):
    SIZE = size
    memory = []
    faults = 0
    time = 0
    for page in pages:
        if memory.count(page) == 0 and len(memory) < SIZE: 
            memory.append(page)
            faults += 1
            for i in memory:
                print("{}".format(i), end=" ")
            print("")
        elif memory.count(page) == 0 and len(memory) == SIZE:
            distance = []
            for i in memory:
                distance.append(search(i, pages[time:]))
            m = distance.index(max(distance))
            target = memory[m]
            idx = memory.index(target)
            memory.remove(target)
            memory.insert(idx, page)
            faults += 1
            for i in memory:
                print("{}".format(i), end=" ")
            print("")            
        time += 1
   
    return faults

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print ('Usage: python paging.py [number of pages]')
    else:
        OPT(size, pages)

