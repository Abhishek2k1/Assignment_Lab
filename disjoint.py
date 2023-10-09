n=8
parent=[[]]*n
rank=[[]]*n

def makeSet():
    for i in range(1,n):
        parent[i]=i
        rank[i]=0

def findpath(node):
    if node == parent[node]:
        return node
    parent[node] = findpath(parent[node])
    return parent[node]

def union(u,v):
    u=findpath(u)
    v=findpath(v)
    if rank[u]<rank[v]:
        parent[u]=v
    elif rank[v]<rank[u]:
        parent[v]=u
    else:
        parent[v]=u
        rank[u]=rank[u]+1


makeSet()
adj=[[1,2],[2,3],[4,5],[6,7],[5,6],[3,7]]

for u,v in adj:
    union(u,v)
print(parent)
print(rank)
