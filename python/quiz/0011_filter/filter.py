def filter(l):
	words=input('输入文字')
	for i in l:
		if i in words:
			return 'Freedom'
	return 'Human Rights'

if __name__=='__main__':
	with open('filtered_words.txt','r') as f:
		l=f.read().split('\n')
		while 1:
			print(filter(l))
