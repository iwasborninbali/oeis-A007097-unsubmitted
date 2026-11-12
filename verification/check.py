"""Trial-division recurrence and log sums; OpenAI Codex, 2026-11-13."""
from math import isqrt,log,exp
primes=[]
k=2
while len(primes)<5381:
    if all(k%p for p in primes if p<=isqrt(k)):
        primes.append(k)
    k+=1
a=1
log_p=0.0
for n in range(1,10):
    a=primes[a-1]
    log_p+=log(log(a))
    if n>=3:
        print(n,a,f'{exp(log_p-log(a)):.9f}',f'{exp(log_p-log(a)-log(log(log(a)))):.9f}')
assert a==52711
print('PASS: recurrence through n=9')
