def fib(n=20):
    fibs=[0,1]
    if n<2:
        return fibs[:n]
    for i in range(n-2):
        fibs.append(fibs[-1] + fibs[-2])
    return fibs