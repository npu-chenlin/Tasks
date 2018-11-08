from bs4 import BeautifulSoup as bs
import requests

def find_content(html):
	c=bs(html,'lxml')
	string=c.article.get_text().strip('\n')
	return string


if __name__=='__main__':
	html=requests.get('https://github.com/Yixiaohan/show-me-the-code')
	html=html.text
	content=find_content(html)
	with open('content.txt','w',encoding='utf-8') as f:
		f.write(content)

