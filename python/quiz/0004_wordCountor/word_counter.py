import re

with open('harry potter.txt','r') as f:
	str1=f.read()
	count=open('count.txt','w')
	pat=re.compile("[a-zA-Z]+")
	words=pat.findall(str1)
	l=[(i,str(words.count(i))) for i in set(words)]
	l=sorted(l,key=lambda i:i[1],reverse=1)
	l=[' '.join(i) for i in l]
	count.write('\n'.join(l))
	count.close()