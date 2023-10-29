from PIL import Image
import numpy as np
import sys

np.set_printoptions(threshold=sys.maxsize)

# We run this, imported or not!
if len(sys.argv) <= 1:
   print("bitmapToRGB requires the first commandline argument to be the name of the file to convert")
   exit()

if __name__ == "__main__":
    #Open the bmp with the corresponding name
    name = str(sys.argv[1])
    try:
        img = Image.open(f'{name}.bmp')
    except FileNotFoundError as e:
        print(f"{name}.bmp is not found in the local directory \r\n" + str(e))

    #Pull the data out of the bmp
    bmpdata = np.array(img)
    #Make a string
    strbmp = repr(bmpdata)
    #Bit of string wrangle to make it a c++ var
    strbmp = strbmp.replace("[", "{").replace("]", "}")
    strbmp = f"byte {name}Data[{img.size[0]}][{img.size[1]}][3] = \r\n\t" + strbmp.lstrip("array(")
    strbmp = strbmp.rstrip(", dtype=uint8)") + ";"

    #Let's see it.
    print(strbmp)
    #Let's write it to a txt file.
    with open(f"{name}.txt", 'w') as f:
        f.write(strbmp)