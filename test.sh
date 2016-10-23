#!/bin/bash
function test {
	echo "$1" > /proc/first
	echo "$2" > /proc/operand
	echo "$3" > /proc/second
	res=`sudo cat /dev/result`
	echo "$1$2$3=${res}"
	if [ "${res}" == "$4" ]; then
		echo "CORRECT"
	else 
		echo "NOT CORRECT"
	fi
}

test 15 + 6 21
test 13 + 2 15
test -4 + 10 6
test -1 + -1 -2
test 5 / 2 2
test 34 / -17 -2
test -6 / -3 2
test 10 '*' 10 100
test 10 '*' -1 -10
test -25 '*' -25 625
test 0 - 20 -20
test 50 - -6 56
test 55 - 155 -100
test 7 - 7 0
test 5 / 0 Error'!'
