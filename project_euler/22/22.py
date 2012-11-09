#!/usr/bin/python

import numpy as np

def scoreOnWord(word):
    wordScore = 0
    for c in word:
        tmp = ord(c) - 64
        wordScore += tmp
    return wordScore

if __name__ == "__main__":
    names = sorted(open("names.txt").read().replace('"', '').replace("'","").split(','))
    score = 0
    for i in xrange(len(names)):
        score += (i+1)*scoreOnWord(names[i])

    print score

