import sys
import os
from time import sleep
from math import cos, sin, pi

sys.path.append(os.path.abspath('/home/pi/scoreboard/scoreboard'))
from rgbmatrix import RGBMatrix, RGBMatrixOptions, graphics

from samplebase import SampleBase

def draw(canvas):
    c.Fill(0, 0, 255)

    center_x = canvas.width // 2
    center_y = canvas.height // 2
    
    radius_max = canvas.width / 2.0
    angle_step = 1 / 360.0

    a = 0
    r = 0
    while r < center_y:
        dot_x = cos(a * 2 * pi) * r
        dot_y = sin(a * 2 * pi) * r

        canvas.SetPixel(center_x + dot_x, center_y + dot_y, 255, 0, 0)
        
        sleep(0.001)
        a += angle_step
        r += angle_step

class test_class(SampleBase):
    def __init__(self, *args, **kwargs):
        super(test_class, self).__init__(*args, **kwargs)

    def run(self):
        print "Running Test!"
        center_x = self.matrix.width // 2
        center_y = self.matrix.height // 2

        canvas = self.matrix.CreateFrameCanvas()
        canvas.Fill(0, 0, 255)
        
        radius_max = canvas.width / 2.0
        angle_step = 1 / 360.0

        a = 0
        r = 0
        while r < center_y:
            dot_x = cos(a * 2 * pi) * r
            dot_y = sin(a * 2 * pi) * r

            canvas.SetPixel(center_x + dot_x, center_y + dot_y, 255, 0, 0)
            
            canvas = self.matrix.SwapOnVSync(canvas)

            print "x: %i; y: %i" % (center_x + dot_x, center_y + dot_y)

            # sleep(0.1)
            a += angle_step
            r += angle_step

        while True:
            pass

# o = RGBMatrixOptions()
# o.rows = 16
# o.cols = 32
# o.chain_length = 3
# o.parallel = 3
# o.multiplexing = 8
# o.row_address_type = 0
# o.gpio_slowdown = 2
# o.pwm_lsb_nanoseconds = 90



# m = RGBMatrix(options=o)

# c = m.CreateFrameCanvas()
# c.Clear()

# draw(c)

if __name__ == "__main__":
    test = test_class()
    if not test.process():
        test.print_help()
