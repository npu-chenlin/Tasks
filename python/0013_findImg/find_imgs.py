import requests,re
from PIL import Image
def find_img_links(html):
	pat=re.compile('src="(.+?.jpg)" bdwater=')
	links=re.findall(pat,html)
	return links

if __name__=='__main__':
	html=requests.get('http://tieba.baidu.com/p/2166231880')
	html=html.text
	links=find_img_links(html)
	print(links)
	count=0
	for i in links:
		img=requests.get(i)
		with open(str(count)+'.jpg','wb') as f:
			f.write(img.content)
		count+=1

