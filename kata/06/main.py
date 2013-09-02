#!/usr/bin/env python

from collections import defaultdict
import argparse
import sets

def hash_word(word):
    return ''.join(sorted(word.lower()))

def hash_dict(word_list):
    result = defaultdict(sets.Set)
    for el in word_list:
        k = hash_word(el)
        result[k].add(el.lower())
    return result

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--wordlist', '-w', required=True)
    parser.add_argument('--dictionary', '-d', required=True)
    args = vars(parser.parse_args())
    with open(args['dictionary']) as f:
        hashed_dict = hash_dict(f.read().splitlines())
    with open(args['wordlist']) as f:
        words = f.read().splitlines()
        for word in words:
            hashed_word = hash_word(word)
            hashed_dict[hashed_word].add(word)
            print word, len(hashed_dict[hashed_word]), hashed_dict[hashed_word]

