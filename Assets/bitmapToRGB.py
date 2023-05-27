from PIL import Image
import numpy as np

img = Image.open(r'Assets\Rocket64.bmp')
bmpdata = np.array(img)

strbmp = repr(bmpdata)
strbmp = strbmp.replace("[", "{")
strbmp = strbmp.replace("]", "}")

with open('rocketRGB.h', 'w') as f:
    f.write(strbmp)