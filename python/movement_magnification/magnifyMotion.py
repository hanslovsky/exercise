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
            pyramidSequence[level] = np.append(pyramidSequence[level], pyr[level][np.newaxis,...], axis = 0)
    return pyramidSequence
    
# get timeseries at each level
def getTimeSeries():
    pass
# filter each timeseries
# rebuild video


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description='Movement Magnficiation')
    parser.add_argument('-f', '--filename_base', dest = 'fn', required=True)
    parser.add_argument('-n', '--pyramid_levels', dest='nLevels', required=False, type=int, default=4)
    args = vars(parser.parse_args())
    fn = args['fn']
    nLevels = args['nLevels']
    
    sequence = readVideoImageStack(fn)
    pyramidSequence = buildPyramid(sequence, nLevels)
    scale = 0
    for el in pyramidSequence:
        t = 0
        for ts in range(el.shape[0]):
            vigra.impex.writeImage(el[ts,...], 'out/pyr_%s_%s.png' % (t, scale))
            t += 1
        scale += 1
            
