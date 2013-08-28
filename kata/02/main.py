#!/usr/bin/python

# http://codekata.pragprog.com/2007/01/kata_two_karate.html
# write five different chop functions


def chop1(comparison, array):
    print chop1_impl(comparison, array, 0)
    return chop1_impl(comparison, array, 0)

def chop1_impl(comparison, array, index=0):
    arr_size = len(array)
    if arr_size == 0:
        return False
    elif arr_size == 1:
        if comparison == array[0]:
            return index
        else:
            return False
    elif array[arr_size/2] > comparison:
        return chop1_impl(comparison, array[:arr_size/2], index)
    elif array[arr_size/2] < comparison:
        return chop1_impl(comparison, array[arr_size/2:], index + arr_size/2 + 1)
    else:
        return index


def test_chop(chop_function):
    print "Testing chop function", chop_function.__name__, "......."
    arr1 = []
    arr2 = [1,3,5]
    arr3 = [1,3,5,7]

    assert chop_function(-1, arr1) == False

    assert chop_function(-1, arr2) == False
    assert chop_function(0, arr2) == False
    assert chop_function(1, arr2) == 0
    assert chop_function(4, arr2) == False
    assert chop_function(5, arr2) == 2

    assert chop_function(-1, arr3) == False
    assert chop_function(0, arr3) == False
    assert chop_function(1, arr3) == 0
    assert chop_function(4, arr3) == False
    assert chop_function(5, arr3) == 2
    assert chop_function(7, arr3) == 3

    print "Test success!"


if __name__ == "__main__":
    test_chop(chop1)

