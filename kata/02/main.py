#!/usr/bin/python

# http://codekata.pragprog.com/2007/01/kata_two_karate.html
# write five different chop functions


def chop1(comparison, array):
    arr_size = len(array)
    if arr_size == 0:
        return False
    elif arr_size == 1:
        return comparison == array[0]
    elif array[arr_size/2] > comparison:
        return chop1(comparison, array[:arr_size/2])
    elif array[arr_size/2] < comparison:
        return chop1(comparison, array[arr_size/2:])
    else:
        return True


def test_chop(chop_function):
    print "Testing chop function", chop_function.__name__, "......."
    arr1 = []
    arr2 = [1,3,5]
    arr3 = [1,3,5,7]

    assert chop_function(-1, arr1) == False

    assert chop_function(-1, arr2) == False
    assert chop_function(0, arr2) == False
    assert chop_function(1, arr2) == True
    assert chop_function(4, arr2) == False
    assert chop_function(5, arr2) == True

    assert chop_function(-1, arr3) == False
    assert chop_function(0, arr3) == False
    assert chop_function(1, arr3) == True
    assert chop_function(4, arr3) == False
    assert chop_function(5, arr3) == True
    assert chop_function(7, arr3) == True

    print "Test success!"


if __name__ == "__main__":
    test_chop(chop1)

