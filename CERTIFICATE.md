# Verification certificate

## Claim

P(n)=C a(n) log log a(n)(1+O(1/log a(n))) for some C>0, hence P(n)/a(n)→∞.

## Evidence

| What | Program | Author and date | Coverage | Result |
|---|---|---|---|---|
| Human-checkable proof | `proof.md` | Adapted by OpenAI Codex from ChatGPT, 2026-11-12 | Universal asymptotic, using the classical nth-prime expansion | Not machine-checked |
| Producer | `programs/compute.py` | OpenAI Codex, 2026-11-13 | Sieve recurrence through n=10 and floating normalizations | Passed |
| Independent check | `verification/check.py` | OpenAI Codex, 2026-11-13 | Trial-division recurrence through n=9, log-sum normalizations | Passed |

The programs share no code or data tables; floating results are approximate. Guide review is recorded in `athanor-oeis/tasks/README.md`.

## Replayed for this repository

2026-11-13, Darwin arm64, Python 3.14.6: `python3 programs/compute.py` and `python3 verification/check.py` agreed through n=9; both give normalized value 0.238283750 there. The checker reports `PASS`. Full output is in `verification/logs/`.

## Not covered

Finite computations cannot prove an asymptotic or determine C. The proof is not machine-checked and invokes the cited nth-prime expansion. The guide's numerical computations through n=23 were not replayed. The independent recurrence check stops one term before the producer.

## Guide's independent check

12 November 2026: the guide reviewed the answer this repository is built from and recorded the verdict in
[athanor-oeis tasks/README.md](https://github.com/iwasborninbali/athanor-oeis/blob/main/tasks/README.md): REFUTED, with a corrected asymptotic; the guide checked the proof.
The write-up in this repository (`proof.md` and the programs, prepared by a Codex core on 13 November 2026) has not yet been
re-read by the guide; until it is, this record stays a candidate.

## Verdict

partial — the finite independent replay covers n<=9 rather than the producer's n<=10, and the asymptotic proof is human-checkable only.
