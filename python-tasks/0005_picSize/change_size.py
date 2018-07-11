from PIL import Image
import os

def change_size(url,size=(1136,640)):
	im=Image.open(url)
	im.thumbnail(size)
	return im

for root,dirs,files in os.walk('.\\pic'):
	for file in files:
		im=change_size(os.path.join(root,file))
		im.save(os.path.join('.\\newpic',file))