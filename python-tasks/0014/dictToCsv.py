import json,csv

def dictToCsv(filename,dict1):
	with open(filename,'w',newline='') as f:
		csvWriter=csv.writer(f)
		for k,v in dict1.items():
			csvWriter.writerow([k,v[0],v[1],v[2]])


if __name__=='__main__':
	with open('students.txt','r') as f:
		content=f.read()
		content=content.replace('\n\t','').replace('\n','')
		j=json.loads(content)
		dictToCsv('1.csv',j)