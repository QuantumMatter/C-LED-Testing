import sys
import os
from time import sleep
from math import cos, sin, pi

sys.path.append(os.path.abspath('/home/pi/scoreboard/scoreboard'))
from rgbmatrix import RGBMatrix, RGBMatrixOptions, graphics

from samplebase import SampleBase

class test_class:#(SampleBase):
    def __init__(self, *args, **kwargs):
        o = RGBMatrixOptions()
        o.rows = 16
        o.cols = 32
        o.chain_length = 3
        o.parallel = 3
        o.multiplexing = 8
        o.row_address_type = 0
        o.pwm_lsb_nanoseconds = 100
        o.brightness = 25
        self.matrix = RGBMatrix(options=o)
        # super(test_class, self).__init__(*args, **kwargs)

    def run(self):
        print "Running Test!"

        canvas = self.matrix.CreateFrameCanvas()
        for y in range(self.matrix.height):
            for x in range(self.matrix.width):
                canvas.SetPixel(x,y,255,255,255)
                print "(%i, %i)" % (x, y)
                canvas = self.matrix.SwapOnVSync(canvas)

if __name__ == "__main__":
    test = test_class()
    test.run()
    # if not test.process():
    #     test.print_help()
