import pyqff

print(pyqff.black_scholes_formula(100, 90, 1, 1, 0.2, "put"))
print(pyqff.black_scholes_formula(100, 90, 1, 1, 0.2, "call"))
