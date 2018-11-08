def filter(l):
	words=input('输入文字')
	for i in l:
		if i in words:
			return words.replace(i,'*'*len(i))
	return words

if __name__=='__main__':
	with open('filtered_words.txt','r') as f:
		l=f.read().split('\n')
		while 1:
			print(filter(l))
