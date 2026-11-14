# Verification certificate

## Claim

P(n)=C a(n) log log a(n)(1+O(1/log a(n))) for some C>0, hence P(n)/a(n)→∞.

## Evidence

| What | Program | Author and date | Coverage | Result |
|---|---|---|---|---|
| Human-checkable proof | `proof.md` | Adapted by OpenAI Codex from ChatGPT, 2026-11-12 | Universal asymptotic, using the classical nth-prime expansion | Not machine-checked |
| Producer | `programs/compute.py` | OpenAI Codex, 2026-11-13 | Sieve recurrence through n=10 and floating normalizations | Passed |
| Independent check | `verification/check.py` | OpenAI Codex, 2026-11-13 | Trial-division recurrence through n=9, log-sum normalizations | Passed |
| Independent referee and check | `verification/agent-2026-11-15/` (REPORT.md, independent.cpp, precision_check.py) | ChatGPT agent, 2026-11-15; own code, no repository code | Segmented-sieve recurrence through n=14 (a(13) = 3,657,500,101); normalizations at high precision; proof read line by line | Passed; proof correct, presentation gaps only |

The programs share no code or data tables; floating results are approximate. Guide review is recorded in `athanor-oeis/tasks/README.md`.

## Replayed for this repository

2026-11-13, Darwin arm64, Python 3.14.6: `python3 programs/compute.py` and `python3 verification/check.py` agreed through n=9; both give normalized value 0.238283750 there. The checker reports `PASS`. Full output is in `verification/logs/`.

2026-11-15, Darwin arm64 (Apple clang `-O3`), by the guide: `./independent && python3 precision_check.py` in
`verification/agent-2026-11-15/` finished in 163 s with `PASS: all rounded 12-decimal C++ values verified`; the
normalized ratio at n = 14 is 0.23839..., consistent with C ~ 0.238.

## Not covered

Finite computations cannot prove an asymptotic or determine C. The proof is not machine-checked and invokes the cited nth-prime expansion. The guide's numerical computations through n=23 were not replayed. The independent recurrence check stops one term before the producer.

## Guide's independent check

15 November 2026: the guide read `proof.md` line by line. With q_n = a(n+1)/a(n) = t_n + log t_n - 1 + O(log t_n/t_n)
and t(n+1) = t_n + log q_n, the leading terms 1/t_n of (1) and (2) cancel in log D(n+1) - log D(n), leaving
O(log t_n/t_n^2); the bound log t_n/t_n^2 <= 4(1/t_n - 1/t(n+1)) holds for large n (it uses log t_n <= 2(t(n+1) - t_n)
and t(n+1) <= 2 t_n) and telescopes, so log D_n converges with error O(1/t_n). The only input is the classical expansion
of the nth prime (Cipolla 1902, as cited by Axler 2019). Verdict: correct. The referee's presentation remarks (domain of
log t_n for small n, the omitted cancellation, the Taylor bookkeeping) are noted and do not affect the result.

## Verdict

complete — the asymptotic is proved (read independently by the guide and by a separate referee) from the classical
nth-prime expansion; the numbers are reproduced by two programs that share no code (through n = 10 and n = 14).
Not covered: no formal proof; the value of C is computed numerically, not in closed form.
