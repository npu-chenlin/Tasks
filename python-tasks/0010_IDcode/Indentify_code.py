from PIL import Image,ImageDraw,ImageFont
import random,string


def rndLetters(n=4):
	letters=string.ascii_letters
	l=random.choice(letters)
	return l

def rndColor():
	return (random.randint(64, 255), random.randint(64, 255), random.randint(64, 255))

def rndColor2():
	return (random.randint(32, 127), random.randint(32, 127), random.randint(32, 127))

width=60*4
height=60
image = Image.new('RGB', (width, height))
font=ImageFont.truetype("C:\\WINDOWS\\Fonts\\SIMYOU.TTF", 60)
draw = ImageDraw.Draw(image)
for x in range(width):
	for y in range(height):
		draw.point((x, y), fill=rndColor())

for t in range(4):
	draw.text((60 * t + 10, 10), rndLetters(), font=font, fill=rndColor2())

image.save('code.jpg')