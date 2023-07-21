from PIL import Image
import numpy as np
import sys

np.set_printoptions(threshold=sys.maxsize)

img = Image.open(r'Crosshair.bmp')
img = img.resize(16, 16);
bmpdata = np.array(img)
strbmp = repr(bmpdata)
strbmp = strbmp.replace("[", "{")
strbmp = strbmp.replace("]", "}")
print(strbmp)
with open('CrosshairRGB.txt', 'w') as f:
    f.write(strbmp)