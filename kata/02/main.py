#!/usr/bin/python

# http://codekata.pragprog.com/2007/01/kata_two_karate.html
# write five different chop functions

class NotInArrayException(Exception):
    pass

def chop1(comparison, array):
    try:
        return chop1_impl(comparison, array)
    except NotInArrayException:
        return False

def chop1_impl(comparison, array):
    arr_size = len(array)
    if arr_size == 0:
        raise NotInArrayException("Not in Array!")
    elif arr_size == 1:
        if comparison == array[0]:
            return 0
        else:
            raise NotInArrayException("Not in Array!")
    elif array[arr_size/2] > comparison:
        return chop1_impl(comparison, array[:arr_size/2])
    elif array[arr_size/2] <= comparison:
        return chop1_impl(comparison, array[arr_size/2:]) + arr_size/2


def chop2(comparison, array):
    arr_size = len(array)
    if arr_size == 0:
        return False

    tmp_array = array
    index = 0
    while arr_size > 1:
        if comparison >= tmp_array[arr_size/2]:
            tmp_array = tmp_array[arr_size/2:]
            index += arr_size/2
        else:
            tmp_array = tmp_array[:arr_size/2]
        arr_size = len(tmp_array)

    if tmp_array[0] == comparison:
        return index
    return False



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
    assert chop_function(3, arr2) == 1

    assert chop_function(-1, arr3) == False
    assert chop_function(0, arr3) == False
    assert chop_function(1, arr3) == 0
    assert chop_function(4, arr3) == False
    assert chop_function(5, arr3) == 2
    assert chop_function(7, arr3) == 3
    assert chop_function(3, arr3) == 1

    print "Test success!"


if __name__ == "__main__":
    test_chop(chop1)
    print
    test_chop(chop2)
    print

