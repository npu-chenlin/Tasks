from bs4 import BeautifulSoup as bs
import requests

def find_links(html):
	links=[]
	c=bs(html,'lxml')
	l=c.find_all('a')
	root='https://github.com'
	for link in l:
		if link['href'] and link['href'][0]=='/':
			links.append(root+link['href'])
		else:
			links.append(link['href'])
	return links


if __name__=='__main__':
	html=requests.get('https://github.com/Yixiaohan/show-me-the-code')
	html=html.text
	content=find_links(html)
	with open('links.txt','w',encoding='utf-8') as f:
		f.write('\n'.join(content))

