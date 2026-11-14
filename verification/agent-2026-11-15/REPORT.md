# Independent verification — OEIS A007097 (2026-11-15)

Source: [iwasborninbali/oeis-A007097-unsubmitted](https://github.com/iwasborninbali/oeis-A007097-unsubmitted), exact audited commit [`af9dc3e78227d0f9b8223eb33123065eb7c51323`](https://github.com/iwasborninbali/oeis-A007097-unsubmitted/commit/af9dc3e78227d0f9b8223eb33123065eb7c51323). The supplied archive was unpacked; `README.md`, `CERTIFICATE.md`, `PRIOR-ART.md`, `proof.md`, both existing programs and both logged runs were inspected. This report and the programs below are newly authored independent work. No existing repository file is changed.

## Claim

**Exact certificate claim:** With `a(0)=1`, `a(n+1)=p_{a(n)}` (1-indexed primes), and `P(n)=prod_{k=1}^n log(a(k))`, there is `C>0` for which **`P(n)=C*a(n)*log(log(a(n)))*(1+O(1/log(a(n))))`**, and consequently `P(n)/a(n) -> +infinity`.

This **disproves the original 2015 OEIS conjecture** `P(n) ~ a(n)`. Neither the existence proof nor any finite computation gives a numerical determination of `C`.

## Proof check

**Mathematical verdict: correct; no fatal gap and no unproved conjecture.** The externally cited nth-prime asymptotic is unconditional. There are several *fixable presentation omissions*, identified here, but their missing algebra works out. Here `t=t_n`, `t'=t_{n+1}`, `q=q_n`, and `Delta=t'-t`.

| `proof.md` lines | Referee assessment and any necessary repair | Severity |
|---|---|---|
| 3–5 | Definitions are correct. The cited classical Cipolla expansion, `p_m/m=log m+log log m-1+O(log log m/log m)`, is a theorem, **not** an assumption or conjecture: see Axler (2019), introduction (1.2). This external theorem is not reproved in the repository, appropriately for a cited input. | No gap; published unconditional input. |
| 7 | `p_m>m` implies strict growth and divergence of integer `a(n)`. `log t_n` and `log(log t_n)` **must only be used for sufficiently large `n`**; `t_0=0` is outside their domain. The eventual-`n` qualification at line 20 is sufficient for an asymptotic, but should be made explicit before line 9. In fact `log t_n>0` at `n>=2`. | Fixable domain clarification; not fatal. |
| 9–10 | Substitution `m=a(n)` and `log q=log t+O(log t/t)` follow from line 5 and `q=t(1+O(log t/t))` for large `n`. | Correct. |
| 12–14 | The cancellation producing `t'-q=1+O(log t/t)` is not displayed. Repair: `t'=t+log q`, so `t'-q=1+[log q-log t]+O(log t/t)=1+O(log t/t)`. Since `q=t(1+O(log t/t))`, `log(t'/q)=log(1+(t'-q)/q)=1/t+O(log t/t^2)`. | Fixable omitted algebra; not fatal. |
| 16–18 | The two Taylor applications are terse. Repair: `Delta=log q=log t+O(log t/t)`; then `log t'-log t=log(1+Delta/t)=log t/t+O((log t)^2/t^2)`. Divide by `log t>0` to obtain `log t'/log t=1+1/t+O(log t/t^2)`; its logarithm is exactly (2). All Taylor arguments tend to zero. | Fixable omitted error check; not fatal. |
| 20–22 | `D_n` is positive for large `n`, and `D_{n+1}/D_n=(t'/q)*(log t/log t')` holds **exactly**. The leading `1/t` from (1) cancels that from (2). | Correct. |
| 24–27 | `Delta~log t`, `t'~t` establish both eventually stated bounds. Since `t'<=2t`, `2 Delta/t^2 <=4 Delta/(t*t')=4(1/t-1/t')`. All quantities are positive. | Correct. |
| 29 | The error terms are bounded in absolute value by a constant multiple of the telescoping differences; therefore `sum_{k>=n}|log D_{k+1}-log D_k|=O(1/t_n)` and `log D_n=L+O(1/t_n)` for finite `L`. One could state *absolute* convergence explicitly. | Fixable explanatory omission; not fatal. |
| 30–33 | Exponentiation yields `D_n=e^L(1+O(1/t_n))` with `C=e^L>0`; `t_n=log a(n)`. As `log t_n -> infinity`, `P(n)/a(n) -> infinity`. | Correct. |

The argument crucially uses the **`-1` term** in the nth-prime expansion; only `p_m ~ m log m` would be insufficient for the stated normalization. It does **not** assume the Riemann hypothesis. The result is a mathematical proof subject to conventional checking, not a machine-checked formalization.

## Independent computation

Method: fresh C++17 **odd-only segmented Eratosthenes** counting primes until the requested 1-indexed rank is reached, repeatedly starting at `a(0)=1`. It stores at most 524,288 odd candidates per segment and separately sieves small divisors through `sqrt(upper)`. A heuristic search limit is *validated* by locating the requested prime, and doubles if too small. It uses **no OEIS term table and no imported repository program or data**. This method differs from the repository's full-range sieve and trial division. Accumulate `sum log(log(a(k)))` in `long double` and exponentiate to get `P/a` and `P/[a log log a]` (when defined).

Reproduce within this directory: `g++ -O3 -std=c++17 -Wall -Wextra -pedantic independent.cpp -o independent && ./independent > output.log`; then `python3 precision_check.py > precision.log`. The second fresh script recalculates all 13 finite decimal normalizations at 60-digit Decimal precision using the ranks emitted by the C++ program; it does not rely on the C++ floating-point calculations.

**Range:** `n=0..14` (all recurrence steps), compared with the repository's original independent range `n=0..9` and producer range `n=0..10`. Outputs for all `n` are in `output.log`. Significant late rows:

| n | a(n) | P(n)/a(n) | P(n)/[a(n) log log a(n)] |
|---:|---:|---:|---:|
| 9 | 52711 | 0.568603161231 | 0.238283749641 |
| 10 | 648391 | 0.618589665106 | 0.238475930296 |
| 11 | 9737333 | 0.662819911526 | 0.238571192470 |
| 12 | 174440041 | 0.702132447462 | 0.238558264061 |
| 13 | 3657500101 | 0.737393140036 | 0.238487807074 |
| 14 | 88362852307 | 0.769299672706 | 0.238392389161 |

**Result:** The independently computed integer sequence agrees term by term with [OEIS A007097's table](https://oeis.org/A007097/list) through `n=14`, the repository values through `n=10`, and the independent check through `n=9`. All original printed floating values agree to their nine shown decimals. The 60-digit checker passed every 12-decimal figure, maximum difference `4.6360043554670706e-13` due to rounding. This is a finite test, **not** proof of the asymptotic or a certified evaluation of `C`.

**Measured time:** `172.863` process CPU seconds and `172.975` wall seconds for C++ `n=0..14` (the external `time` measurement: `172.79` user CPU + `0.06` system CPU seconds; peak RSS `2668 KiB`). GNU g++ 14.2.0, optimized release build, Linux x86-64 container. Decimal validation took negligible additional time.

**SHA-256 (local verification artifacts):**

| file | SHA-256 |
|---|---|
| `independent.cpp` | `408e094ccbcd70d5b764317b89b338e2ee7bc81dcaa5df3064122398174c09f6` |
| `output.log` | `eb7c108d9f6a4f8600ebef2fd333bd2e7bdc8e226ba5ab0162b238664cc66961` |
| `precision_check.py` | `be1040167a7f5fc212d8b8e14fa9ba50f7cae510f5e4bd88b194d45a632e3606` |
| `precision.log` | `1cf1a5ebf4720a0eb5acbbb7bdf7ba93b82641f6a624fb17a1113a01105a3aa2` |

## Prior art

Search performed on **2026-11-15**; the following distinguishes a **published input, a related result, a withdrawn claim, and an exact prior proof**.

1. [OEIS A007097](https://oeis.org/A007097), [internal text](https://oeis.org/A007097/internal), [full table](https://oeis.org/A007097/list): the comment by **Thomas Ordowski dated 2015-03-26** still states `prod log a(k) ~ a(n)` as a *conjecture*, not the corrected formula; the internal record's latest header in the accessible result is `#212 Feb 07 2026`. OEIS's history URLs were attempted (`/A007097/history` and `/history?seq=A007097`), but the revision interface was not accessible through the research tool; **a complete revision-by-revision history audit is not claimed**.
2. [MathOverflow question 357765, asked 2020-04-17](https://mathoverflow.net/questions/357765/thomas-ordowski-conjecture-at-oeis-sequence-a007097): directly asks for proof or disproof of the *same original conjecture*. In a **2020-12-09** comment, GH from MO explicitly admits the earlier disproof was wrong; on **2020-12-10** the questioner confirms removing the corresponding OEIS assertion. No surviving solution establishing this corrected asymptotic appeared on that question. An earlier **withdrawn disproof is not prior art proving the present result**.
3. [Axler, *New Estimates for the nth Prime Number*](https://cs.uwaterloo.ca/journals/JIS/VOL22/Axler/axler17.html), *Journal of Integer Sequences* **22 (2019), Article 19.4.2**, [arXiv:1706.03651](https://arxiv.org/abs/1706.03651): introduction, formula (1.2), cites **Cipolla (1902)** and establishes exactly the classical nth-prime asymptotic input the repository uses. **Does not give this A007097 log-product deduction.** [Dusart, arXiv:1002.0442](https://arxiv.org/abs/1002.0442) provides related nth-prime estimates, likewise not this deduction.
4. [Broughan and Barnett, *On the Subsequence of Primes Having Prime Subscripts*](https://cs.uwaterloo.ca/journals/JIS/VOL12/Broughan/broughan16.html), *Journal of Integer Sequences* **12 (2009), Article 09.2.3**: prime-indexed-prime counting and growth; mentions higher iterates but does not analyze this product. [Bayless, Klyve, Oliveira e Silva, *New Bounds and Computations on Prime-Indexed Primes*](https://digitalcommons.cwu.edu/math/16/), *Integers* **13 (2013), A43**, [paper](https://www.kurims.kyoto-u.ac.jp/EMIS/journals/INTEGERS/papers/n43/n43.pdf): explicit bounds and asymptotics for **fixed-order prime iterates**, not `prod_{k=1}^n log a(k)` along the growing chain. [Czarnecki and Giddings, *Arithmetic Functions of Higher-Order Primes*](https://doi.org/10.2140/involve.2020.13.181), *Involve* **13 (2020), pp. 181–191**, similarly concerns higher-order prime sets and related functions. These are closely related journal prior art, **not identified as an exact proof**.
5. [Batchko, arXiv:1405.2900 (2014)](https://arxiv.org/abs/1405.2900): empirical fractal patterns in finite-differenced prime-indexed iterates, **not** the log-product asymptotic. [Alexandrov, arXiv:math/9811096 (1998)](https://arxiv.org/abs/math/9811096): Eratosthenes progressions / prime distribution. [Manchon, arXiv:2602.03150 (2026)](https://arxiv.org/abs/2602.03150): Matula arborification, Möbius and Liouville functions. No exact result was found in their accessible descriptions.
6. Relevant OEIS cross-references checked: [A131842](https://oeis.org/A131842) (first differences), [A283460](https://oeis.org/A283460) (sum of primes to `a(n)`), [A114537](https://oeis.org/A114537) (prime dispersion), [A057451](https://oeis.org/A057451) (a related primeth trajectory), and [A321132](https://oeis.org/A321132) (iterated prime-counting inverse). None of the reviewed entry material asserts the exact corrected product formula.
7. Searched **Math StackExchange**, **MathOverflow**, **arXiv**, journal indexes, and **zbMATH Open** via indexed web searches for combinations of `A007097`, `Ordowski`, `primeth`, `iterated prime`, `product`, `log log` and `asymptotic`. No *additional exact result* was located. A direct indexed `zbmath.org` match was not obtained; [MaRDI's zbMATH-derived metadata for the 2013 journal paper](https://portal.mardi4nfdi.de/wiki/New_bounds_and_computations_on_prime-indexed-primes) and [the 2020 paper](https://portal.mardi4nfdi.de/wiki/Arithmetic_functions_of_higher-order_primes) was inspected instead. This is **not an exhaustive zbMATH or journal search**, nor proof of global novelty.

## Verdict

**PARTIAL (novelty not established).** The **mathematical claim is correct**: I checked every line, the key published prime asymptotic, and the proof's summable error; there is no fatal defect and no conjectural hypothesis. The **finite computational evidence is independently reproduced and extended through `n=14`** with a second, higher-precision floating-point check. The original Ordowski conjecture is false. However, **the priority/novelty claim is not established**: the OEIS revision interface was not independently audited in full, zbMATH coverage is incomplete, and absence from searched materials is not exhaustive evidence of originality. `C` is proved to exist, but not numerically certified; no finite test can replace the asymptotic proof. Thus the correction is mathematically verified, **not certified as new**.

GitHub read-back of these newly pushed files and SHA-256 comparison against local copies must be completed separately after publishing; this audit does not rely on the repository certificate's self-attestation.
