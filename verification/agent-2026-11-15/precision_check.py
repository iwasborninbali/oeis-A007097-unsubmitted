"""Independently re-evaluate the C++ log normalizations with Decimal (60 digits)."""
from decimal import Decimal, localcontext
from pathlib import Path
import re

text = Path(__file__).with_name("output.log").read_text(encoding="utf-8")
pattern = re.compile(r"^n=(\d+) a=(\d+)(?: P_over_a=([0-9.]+) normalized=([0-9.]+))?$", re.M)
rows = [m.groups() for m in pattern.finditer(text)]
assert [int(row[0]) for row in rows] == list(range(15))
with localcontext() as ctx:
    ctx.prec = 60
    logs_of_product = Decimal(0)
    maximum_difference = Decimal(0)
    for n_s, a_s, ratio_s, norm_s in rows[1:]:
        n = int(n_s)
        a = Decimal(a_s)
        logs_of_product += a.ln().ln()
        if n < 2:
            continue
        ratio = (logs_of_product - a.ln()).exp()
        normalized = ratio / a.ln().ln()
        for calculated, recorded in ((ratio, Decimal(ratio_s)), (normalized, Decimal(norm_s))):
            difference = abs(calculated - recorded)
            if difference > maximum_difference:
                maximum_difference = difference
            assert difference <= Decimal("0.0000000000005"), (n, difference)
    print("rows_checked=13 (n=2..14)")
    print("decimal_precision=60")
    print("maximum_absolute_difference=" + str(maximum_difference))
    print("decimal_ratio_n14=" + str(ratio))
    print("decimal_normalized_n14=" + str(normalized))
    print("PASS: all rounded 12-decimal C++ values verified")
