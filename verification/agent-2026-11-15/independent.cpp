// Independent check of the primeth recurrence A007097.
// Written afresh for this audit, 2026-11-15.
// Computes p_m by counting primes in disjoint odd-number segments;
// unlike the repository's global sieve and trial-division implementations.
// Only the classical Eratosthenes marking rule is used, with no OEIS table.
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using u64 = std::uint64_t;

static std::vector<std::uint32_t> small_primes(u64 limit) {
    std::vector<std::uint8_t> composite(limit + 1, 0);
    std::vector<std::uint32_t> result;
    for (u64 d = 2; d <= limit; ++d) {
        if (!composite[d]) {
            result.push_back(static_cast<std::uint32_t>(d));
            if (d <= limit / d)
                for (u64 k = d * d; k <= limit; k += d) composite[k] = 1;
        }
    }
    return result;
}

// A numeric upper limit is a heuristic only. The function checks that it
// actually found the requested prime; if it has not, the limit is doubled.
static u64 find_nth_prime(u64 rank) {
    if (rank == 1) return 2;
    long double r = static_cast<long double>(rank);
    long double estimate = r < 6 ? 128.L : 1.12L * r * (logl(r) + logl(logl(r))) + 1024.L;
    if (estimate >= static_cast<long double>(std::numeric_limits<u64>::max() / 2))
        throw std::runtime_error("rank exceeds supported range");
    u64 upper = static_cast<u64>(ceill(estimate));
    constexpr u64 SEG_ODDS = 1ULL << 19; // at most 524288 odd values in memory
    for (;;) {
        u64 root = static_cast<u64>(sqrtl(static_cast<long double>(upper))) + 1;
        const auto base = small_primes(root);
        u64 found = 1; // the even prime 2
        for (u64 low = 3; low <= upper; ) {
            u64 hi = std::min(upper, low + 2 * (SEG_ODDS - 1));
            if ((hi & 1) == 0) --hi;
            const u64 length = (hi - low) / 2 + 1;
            std::vector<std::uint8_t> composite(length, 0);
            for (std::uint32_t p32 : base) {
                u64 p = p32;
                if (p == 2) continue;
                if (p > hi / p) break;
                u64 first = (low + p - 1) / p * p;
                if (first < p * p) first = p * p;
                if ((first & 1) == 0) first += p;
                for (u64 j = first; j <= hi; j += 2 * p)
                    composite[(j - low) / 2] = 1;
            }
            for (u64 i = 0; i < length; ++i) {
                if (!composite[i] && ++found == rank) return low + 2 * i;
            }
            if (hi >= upper - 1) break;
            low = hi + 2;
        }
        if (upper > std::numeric_limits<u64>::max() / 2)
            throw std::runtime_error("search limit overflow");
        upper *= 2;
    }
}

int main() {
    const auto begin = std::chrono::steady_clock::now();
    const std::clock_t cpu_start = std::clock();
    constexpr unsigned N = 14;
    u64 a = 1;
    long double log_product = 0;
    std::cout << "method=odd-only segmented Eratosthenes; primes counted by rank; no external sequence data\n";
    std::cout << "target_n=" << N << "\n";
    std::cout << "n=0 a=1\n";
    std::cout << std::fixed << std::setprecision(12);
    for (unsigned n = 1; n <= N; ++n) {
        a = find_nth_prime(a);
        long double t = logl(static_cast<long double>(a));
        log_product += logl(t);
        std::cout << "n=" << n << " a=" << a;
        if (n >= 2) {
            long double ratio = expl(log_product - t);
            long double normalized = ratio / logl(t);
            std::cout << " P_over_a=" << ratio << " normalized=" << normalized;
        }
        std::cout << '\n' << std::flush;
    }
    const auto elapsed = std::chrono::duration<double>(std::chrono::steady_clock::now()-begin).count();
    const double cpu = double(std::clock() - cpu_start) / CLOCKS_PER_SEC;
    std::cout << "elapsed_wall_seconds=" << std::setprecision(3) << elapsed << '\n';
    std::cout << "elapsed_cpu_seconds=" << std::setprecision(3) << cpu << '\n';
    return 0;
}
