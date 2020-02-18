import pyqff

print(pyqff.black_scholes_formula(100, 90, 0.98, 1, 0.2, "put"))
print(pyqff.black_scholes_formula(100, 90, 0.98, 1, 0.2, "call"))
print(pyqff.black_76_formula(100, 90, 0.98, 1, 0.2, "put"))
print(pyqff.black_76_formula(100, 90, 0.98, 1, 0.2, "call"))
day_counter = pyqff.Actual360()
print(day_counter)
d1 = pyqff.as_boost_date("2018-2-10")
d2 = pyqff.as_boost_date("2018-12-30")
print(d1)
print(day_counter.CalculateYearFraction(d1,d2))
