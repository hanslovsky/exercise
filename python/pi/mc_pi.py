#!/usr/bin/python

import numpy as np

def estimate_pi(N):
    rand = 2.0*np.random.rand(2, N) - 1.0
    dist = rand[0,:]*rand[0,:] + rand[1,:]*rand[1,:]
    return np.sum(dist <= 1)*4.0/N

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--n-samples', '-n', dest='N', default=1000, type=int)
    args=vars(parser.parse_args())
    N = args['N']
    pi = estimate_pi(N)
    print "Calculating pi using %d random samples" % (N,)
    print "pi =", pi
    print "derivation from numpy.pi = ", abs(pi-np.pi)/np.pi
    
    
