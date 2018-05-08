import PIL
from PIL import Image

mywidth = 170
palce = ["index", "middle", "ring", "thumb", "pinky"]
status = ["active", "disconnected"];
sensor = ["touch", "bend"]

for iter1 in sensor:
	for iter2 in status:
		for iter3 in palce:
			name = "finger" + "_" + iter3 + "_" + iter1 + "_" + iter2 + ".png"
			img = Image.open(name)
			wpercent = (mywidth/float(img.size[0]))
			hsize = int((float(img.size[1])*float(wpercent)))
			img = img.resize((mywidth,hsize), PIL.Image.ANTIALIAS)
			img.save(name)

name = "hand.png"
img = Image.open(name)
wpercent = (mywidth/float(img.size[0]))
hsize = int((float(img.size[1])*float(wpercent)))
img = img.resize((mywidth,hsize), PIL.Image.ANTIALIAS)
img.save(name)


