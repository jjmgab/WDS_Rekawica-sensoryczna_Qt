import PIL
from PIL import Image

mywidth = 150

name = "hand.png"
img = Image.open(name)
wpercent = (mywidth/float(img.size[0]))
hsize = int((float(img.size[1])*float(wpercent)))
img = img.resize((mywidth,hsize), PIL.Image.ANTIALIAS)
img.save(name)


