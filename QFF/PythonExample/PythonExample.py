import pyqff

print(pyqff.black_scholes_formula(100, 90, 0.98, 1, 0.2, "put"))
print(pyqff.black_scholes_formula(100, 90, 0.98, 1, 0.2, "call"))
print(pyqff.black_76_formula(100, 90, 0.98, 1, 0.2, "put"))
print(pyqff.black_76_formula(100, 90, 0.98, 1, 0.2, "call"))
print(pyqff.Actual360())
