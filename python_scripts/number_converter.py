import sys
from PIL import Image

# take 32x24 black and white image, and puts it into [[x, y], [x1,y1], ...] format

input_file = sys.argv[1]

img = Image.open(input_file).convert("1") # load as black and white
pixels = img.load()

out_str = "{"
count = 0

for x in range(0,24):
    for y in range(0,32):
        if pixels[x, y] == 0:
            out_str += "{" + str(x) +"," +str(y)+"},"
            count+=1

out_str += "}    " + str(count) 
with open("out_numb.txt", "w") as out_file:
    out_file.write(out_str)