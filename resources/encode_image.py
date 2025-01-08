#!/usr/bin/python
import sys
import os
from PIL import Image

# colour-runs encoded as 0bnnnnnnpp, nnnnnn is the length, pp is palette idx

#bmp = Image.open("btn_up.bmp")
bmp = Image.open("btn_down.bmp")
pal = bmp.getpalette()
my_pal = ((0,0,0), # black
          (255,0,0), #red
          (255,255,255) # white
          )
#print(pal)
prev_pal_idx = -1
run_len = 0
sys.stdout.write('{\n')
for row in range(bmp.height):
    sys.stdout.write('  ')
    for col in range(bmp.width):
        idx = 3*bmp.getpixel((col, row))
        rgb = (pal[idx], pal[idx+1], pal[idx+2])
        if rgb in my_pal:
            this_pal_idx = my_pal.index(rgb)
            if this_pal_idx == prev_pal_idx:
                run_len = run_len + 1
            else:
                if run_len > 0:
                    sys.stdout.write('0x' + hex(256 + run_len*4 + prev_pal_idx)[3:].upper())
                    sys.stdout.write(", ")
                run_len = 1
                prev_pal_idx = this_pal_idx
        else:
            print("*** NOT IN PALETTE ***")
    if run_len > 0:
        sys.stdout.write('0x' + hex(256 + run_len*4 + prev_pal_idx)[3:].upper())
        sys.stdout.write(", ")
    prev_pal_idx = -1
    run_len = 0        
    sys.stdout.write("\n")
sys.stdout.write('  0x00\n')
sys.stdout.write('};\n')
