# Proof

Let a₀=1, aₙ₊₁=p_{aₙ}, and Pₙ=∏_{k=1}^n log aₖ. All logarithms are natural. We use the classical nth-prime expansion, as cited in Christian Axler, *New estimates for the nth prime number*, arXiv:1706.03651, introduction:

    p_m/m = log m + log log m - 1 + O((log log m)/log m).

Since p_m>m, aₙ increases without bound. Write tₙ=log aₙ and qₙ=aₙ₊₁/aₙ. Applying the expansion at m=aₙ gives

    qₙ = tₙ + log tₙ - 1 + O(log tₙ/tₙ),
    log qₙ = log tₙ + O(log tₙ/tₙ).

The exact recurrence tₙ₊₁=tₙ+log qₙ then gives tₙ₊₁-qₙ=1+O(log tₙ/tₙ). Since qₙ/tₙ→1, Taylor expansion yields

    log(tₙ₊₁/qₙ) = 1/tₙ + O(log tₙ/tₙ²).                 (1)

Also tₙ₊₁-tₙ=log tₙ+O(log tₙ/tₙ). Applying log(1+u)=u+O(u²) twice gives

    log(log tₙ₊₁ / log tₙ) = 1/tₙ + O(log tₙ/tₙ²).      (2)

For sufficiently large n put Dₙ=Pₙ/(aₙ log tₙ). Since Pₙ₊₁=Pₙ tₙ₊₁ and aₙ₊₁=aₙqₙ, equations (1) and (2) imply

    log Dₙ₊₁-log Dₙ = O(log tₙ/tₙ²).

For large n, (log tₙ)/2 <= tₙ₊₁-tₙ <= 2 log tₙ and tₙ₊₁<=2tₙ. Therefore

    log tₙ/tₙ² <= 2(tₙ₊₁-tₙ)/tₙ²
                  <= 4(1/tₙ-1/tₙ₊₁).

The tail of the error series is O(1/tₙ), by telescoping. Thus log Dₙ tends to a finite limit L with error O(1/tₙ). Setting C=eᴸ>0 and exponentiating gives

    Pₙ = C aₙ log log aₙ (1+O(1/log aₙ)).

Since log log aₙ→∞, Pₙ/aₙ→∞, contradicting the conjectured limit 1. The argument depends on the cited nth-prime expansion and is human-checkable, not formally machine-checked.
