# OEIS A007097: logarithmic product asymptotic (not yet submitted)

<!-- oeis-status:begin -->
**OEIS status: not submitted** (lab registry, 15 Nov 2026).

- [A007097](https://oeis.org/A007097), conjecture of Mar 26 2015 false; corrected asymptotic: **verified** (2026-11-15: certificate complete: guide's proof reading, referee to n = 14, prior art (MO 357765 unresolved)). Certificate: complete.

Rules and the full registry: [athanor-oeis](https://github.com/iwasborninbali/athanor-oeis/blob/main/REGISTRY.md).
<!-- oeis-status:end -->

## Definition

Let a(0)=1 and a(n+1) be the a(n)-th prime, primes indexed from 1; the offset is 0. Let P(n)=∏_{k=1}^n log(a(k)), with natural logarithms and empty product P(0)=1. The snapshot `context/A007097.seq` and the live [entry](https://oeis.org/A007097), read 2026-11-13, attribute to Thomas Ordowski, March 26, 2015: “Conjecture: log(a(1))*log(a(2))*...*log(a(n)) ~ a(n).” The live entry still records this conjecture.

## Terms / result

The conjecture is false: for a positive finite constant C, P(n)=C a(n) log log a(n) (1+O(1/log a(n))). Thus P(n)/a(n) tends to infinity.

| n | a(n) | P(n)/a(n), approximate |
|---:|---:|---:|
| 5 | 31 | 0.325545226 |
| 8 | 5381 | 0.512288897 |
| 9 | 52711 | 0.568603161 |
| 10 | 648391 | 0.618589665 |

## How it was obtained

The classical nth-prime expansion yields a one-step product ratio. After normalization by log log a(n), the remaining logarithmic errors form a summable series. See [proof.md](proof.md).

## Verification

Separate sieve and trial-division implementations reproduce finite recurrence values and floating-point normalizations through n=9. These numerical checks do not prove the limit or determine C. The proof is human-checkable, not formally machine-checked. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

Ordowski stated the conjecture. ChatGPT supplied the deduction from Cipolla's nth-prime expansion and Claude Code reviewed it. A previous MathOverflow argument was withdrawn; see [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Run `python3 programs/compute.py` and `python3 verification/check.py`, together under one second on the recorded machine. Both print `9 52711 0.568603161 0.238283750`; the checker ends `PASS: recurrence through n=9`. Logs are in `verification/logs/`.

## Provenance

Source `projects/science/athanor-oeis`, commit `7662d9a678c6d414685a899a631c63ac320f6840`, paths `tasks/2026-11-12-A007097-primeth-log-product/answers/2026-11-12-chatgpt.md`, `context/A007097.seq`, and `TASK.md`. Guide review is recorded in `tasks/README.md`.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
