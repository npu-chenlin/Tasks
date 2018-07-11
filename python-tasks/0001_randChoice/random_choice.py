import random,string

def random_choice(num=200,length=6):
	f=open('code.txt','a')
	for i in range(num):
		t=string.ascii_lowercase+string.ascii_uppercase+string.digits
		s=[random.choice(t) for i in range(length)]
		f.write('{0}\n'.format(''.join(s)))

	f.close()

if __name__ == '__main__':
	random_choice()