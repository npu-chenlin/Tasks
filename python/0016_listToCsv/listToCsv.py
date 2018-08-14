import json,csv

def dictToCsv(filename,list1):
	with open(filename,'w',newline='') as f:
		csvWriter=csv.writer(f)
		for i in list1:
			csvWriter.writerow([i[0],i[1],i[2]])


if __name__=='__main__':
	with open('numbers.txt','r') as f:
		content=f.read()
		content=content.replace('\n\t','').replace('\n','')
		j=json.loads(content)
		dictToCsv('1.csv',j)