#!/usr/bin/python

import vigra
import numpy as np


# read video (in form of image stack)

def readVideoImageStack(filenameBase):
    sequence = np.transpose(vigra.impex.readVolume(filenameBase, dtype = 'FLOAT'), (2,0,1,3))
    sequence.axistags[0] = vigra.AxisInfo('t', typeFlags=vigra.AxisType.Time)
    return sequence

# build Pyramid
def buildPyramid(imageSequence, nLevels):
    '''Build Pyramid for each timestep. Return np.array that holds the timeseries of the pyramids'''
    assert len(imageSequence.shape) == 4, 'not a 4-channel image: ' + str(imageSequence.shape)
    assert imageSequence.axistags[0] == vigra.AxisInfo('t', typeFlags=vigra.AxisType.Time), 'first dimension is not time:\n' + str(imageSequence.axistags)
    axistags = imageSequence.axistags
    timesteps = imageSequence.shape[0]
    pyramidSequence = []
    pyr = vigra.sampling.ImagePyramid(imageSequence[0,...],
                                      copyImageToLevel=0,
                                      lowestLevel=0,
                                      highestLevel=nLevels-1)
    pyr.reduceLaplacian(srcLevel = pyr.lowestLevel,
                        destLevel = pyr.highestLevel)
    for level in range(nLevels):
        pyramidSequence.append(pyr[level][np.newaxis,...])
    for t in range (1, timesteps):
        # see vigranumpy documentation for information on the pyramid
        pyr = vigra.sampling.ImagePyramid(imageSequence[t,...],
                                          copyImageToLevel=0,
                                          lowestLevel=0,
                                          highestLevel=nLevels-1)
        pyr.reduceLaplacian(srcLevel = pyr.lowestLevel,
                            destLevel = pyr.highestLevel)
        for level in range(nLevels):
            pyramidSequence[level] = vigra.VigraArray(np.append(pyramidSequence[level], pyr[level][np.newaxis,...], axis = 0), axistags = axistags)
    return pyramidSequence
    
# filter each timeseries

def filterTimeSeries(pyramidSequence, kernel, weights):
    nLevels = len(pyramidSequence)
    ts = pyramidSequence[0].shape[0]
    zeroKernel = vigra.filters.Kernel1D()
    zeroKernel.initExplicitly(left=0, right=0, contents=np.array([1.0]))
    lvl = 0
    sumPyrSequence = []
    for scale in pyramidSequence:
        sumPyrSequence.append((1.0-weights[lvl])*scale)
        # sumPyrSequence[lvl] += weights[lvl]*vigra.filters.convolve(scale, (kernel, zeroKernel, zeroKernel))
        sumPyrSequence[lvl] += weights[lvl]*vigra.filters.convolveOneDimension(scale, 0, kernel)
        lvl += 1
    for t in range(sumPyrSequence[0].shape[0]):
        lvl = len(sumPyrSequence)-1
        while lvl > 0:
        # loop could be avoided if vigra would allow for resize in arbitrary dimensions
            sumPyrSequence[lvl-1][t,...] += vigra.sampling.resize(sumPyrSequence[lvl][t,...], shape = sumPyrSequence[lvl-1][t,...].shape[:2])
            lvl -= 1
    return sumPyrSequence[0]
    
def writeSequence(sequence, fn_base, ext = '.png'):
    nT = sequence.shape[0]
    '''vigra.impex.writeVolume(volume = np.transpose(sequence, (1,2,0,3)),
                            filename_base = fn_base,
                            filename_ext = ext)'''
    for ts in range(nT):
        vigra.impex.writeImage(sequence[ts,...], fn_base + '%02d' % ts + ext)

    
    


if __name__ == '__main__':
    import argparse
    from time import clock, time
    parser = argparse.ArgumentParser(description='Movement Magnficiation')
    parser.add_argument('-f', '--filename_base', dest = 'fn', required=True)
    parser.add_argument('-o', '--out_base', dest = 'out', required=True)
    parser.add_argument('-n', '--pyramid_levels', dest='nLevels', required=False, type=int, default=4)
    args = vars(parser.parse_args())
    fn = args['fn']
    nLevels = args['nLevels']
    out = args['out']

    t0 = clock()
    print "loading sequence from " + fn, '...'
    sequence = readVideoImageStack(fn)
    t1 = clock()
    print "[%s]: %s  -  done" % (t1-t0, t1-t0)
    print "building pyramid with %d levels ..." % nLevels
    pyramidSequence = buildPyramid(sequence, nLevels)
    t2 = clock()
    print "[%s]: %s  -  done" % (t2-t0, t2-t1)
    print "applying kernels in temporal domain ..."
    kernel = vigra.filters.Kernel1D()
    # kernel.initBinomial(radius=1)
    kernel.initExplicitly(left=-2, right=2, contents=np.array([0.25, 0.5, 0, -0.5, -0.25]))
    weights = np.zeros(nLevels) + 0.1
    # for i in range(nLevels):
    #     weights[i] = 1.0 - 1.0/(i+2)**2
    '''weights[nLevels-6] = 0.3
    weights[nLevels-5] = 0.2
    weights[nLevels-4] = 0.1
    weights[nLevels-3] = 0.5
    weights[nLevels-2] = 0.5
    weights[nLevels-1] = 0.7'''
    weights[...] = 0.3
    weights[nLevels-1] = 0.01
    
    reconstructedSequence = filterTimeSeries(pyramidSequence, kernel, weights)
    t3 = clock()
    print "[%s]: %s  -  done" % (t3-t0, t3-t2)

    '''scale = 0
    for el in pyramidSequence:
        t = 0
        for ts in range(el.shape[0]):
            vigra.impex.writeImage(el[ts,...], 'out/pyr_%s_%s.png' % (t, scale))
            t += 1
        scale += 1'''
    print "writing sequence to " + out
    writeSequence(reconstructedSequence, out, '.jpg')
