"""Sieve recurrence and floating normalizations; OpenAI Codex, 2026-11-13."""
from math import log, isqrt
L=1_000_000
s=bytearray(b'\1')*(L+1); s[:2]=b'\0\0'
for p in range(2,isqrt(L)+1):
    if s[p]: s[p*p::p]=b'\0'*(((L-p*p)//p)+1)
primes=[p for p in range(2,L+1) if s[p]]
a=[1]
while a[-1]<=len(primes):
    a.append(primes[a[-1]-1])
P=1.0
for n in range(1,len(a)):
    P*=log(a[n])
    if n>=3:
        print(n,a[n],f'{P/a[n]:.9f}',f'{P/(a[n]*log(log(a[n]))):.9f}')
print('last n:',len(a)-1)
