import argparse

parser = argparse.ArgumentParser(
	description="factorial or fibonacci")

parser.add_argument("--task",type=str, choices=["factorial","fibonacci"],
	default="fibonacci", help="which task to perform")
parser.add_argument("--n", type=int, default=0, help="the function argument n")

args = parser.parse_args()

def factorial(n):
	if n in [0,1]:
		return n 
	else:
		return n*factorial(n-1)

def fibonacci(n):
	fibs = [0, 1]
	for i in range(n-1):
		fibs.append(fibs[-1] + fibs[-2])
	return fibs[n]

if __name__ == '__main__':
	if args.task == "factorial":
		print("factorial({}) = {}".format(args.n, factorial(args.n)))
	elif args.task == "fibonacci":
		print("fibonacci({}) = {}".format(args.n, fibonacci(args.n)))