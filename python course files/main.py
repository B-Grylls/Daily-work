from utils import fib
import sys

if __name__ == '__main__':
	print(sys.argv)
	n = int(sys.argv[1])
	print(fib(n=n))