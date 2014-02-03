"""Modified version of the example code from Janert,
Feedback Control For Computer Systems

This modified version requires pandas, numpy, and matplotlib.

If you use apt:

sudo apt-get install python-pandas python-numpy python-matplotlib
"""

import numpy as np
import pandas as pd
import random
import matplotlib.pyplot as pyplot

class Buffer:
    def __init__( self, max_wip, max_flow ):
        """Initializes the buffer:

        max_wip: maximum work in progress
        max_flow: maximum work completed per time step
        """
        self.queued = 0
        self.wip = 0             # work-in-progress ("ready pool")

        self.max_wip = max_wip
        self.max_flow = max_flow # avg outflow is max_flow/2

    def work( self, u ):
        # Add to ready pool
        u = max( 0, int(round(u)) )
        u = min( u, self.max_wip )
        self.wip += u

        # Transfer from ready pool to queue
        r = int( round( random.uniform( 0, self.wip ) ) )
        self.wip -= r
        self.queued += r

        # Release from queue to downstream process
        r = int( round( random.uniform( 0, self.max_flow ) ) )
        r = min( r, self.queued )
        self.queued -= r

        return self.queued

class Controller:
    def __init__( self, kp, ki, kd ):
        """Initializes the controller.

        kp: proportional gain
        ki: integral gain
        kd: derivative gain
        """
        self.kp, self.ki, self.kd = kp, ki, kd
        self.i = 0       # Cumulative error ("integral")
        self.past_error = 0

    def work( self, e ):
        """Computes the number of jobs to be added to the ready queue.

        e: error

        returns: float number of jobs
        """
        self.i += e
        self.delta = e - self.past_error
        self.past_error = e

        return self.kp*e + self.ki*self.i + self.kd*self.delta

# ============================================================

def closed_loop( c, p, tm=5000 ):
    """Simulates a closed loop control system.

    c: Controller object
    p: Buffer object
    tm: number of time steps

    returns: tuple of sequences (times, targets, errors)
    """
    def setpoint( t ):
        return t*.02
    
    y = 0
    res = []
    for t in range( tm ):
        r = setpoint(t)
        e = r - y
        u = c.work(e)
        y = p.work(u)

        #print t, r, e, u, y
        res.append((t, r, e, u, y))

    return zip(*res)

# ============================================================


# best performance at kd ~= 1.1
kds = np.linspace(0, 3, 31)
average_errors = []
for kd in kds:
    errors = []
    for i in range(1000):
        c = Controller( 1.25, 0.01, kd)
        p = Buffer( 50, 10 )

        # run the simulation
        ts, rs, es, us, ys = closed_loop( c, p, 1000 )

        rms_error = np.sqrt(np.mean(np.array(es)**2))
        errors.append(rms_error)

        # # generate the smoothed curve using a rolling mean
        # # (I think the curves in the book use loess)
        # ys_smooth = pandas.rolling_mean(numpy.array(ys), 20)

        # # make the plot
        # pyplot.plot(ts, rs, color='green', label='target')
        # pyplot.plot(ts, ys, color='red', label='queue length')
        # pyplot.plot(ts, ys_smooth, color='blue', label='trend')
        # pyplot.show()

    average_error = sum(errors)/len(errors)
    average_errors.append(average_error)

print kds, average_errors
pyplot.plot(kds, average_errors)
pyplot.ylim(ymin=5)
pyplot.show()




