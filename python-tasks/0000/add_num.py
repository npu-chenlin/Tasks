from PIL import Image, ImageDraw,ImageFont
import os
def add_num(name):
	font=ImageFont.truetype("C:\\WINDOWS\\Fonts\\SIMYOU.TTF", 120)
	img=Image.open(name)
	draw=ImageDraw.Draw(img)
	w,h=img.size
	draw.text([0.8*w,0.2*h],'4',"red",font=font)
	img.save('num_pic.jpg')

if __name__ == '__main__':
	name='pic.jpg'
	add_num(name)
