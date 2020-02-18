import pyqff

print(pyqff.black_scholes_formula(100, 90, 0.98, 1, 0.2, "put"))
print(pyqff.black_scholes_formula(100, 90, 0.98, 1, 0.2, "call"))
print(pyqff.black_76_formula(100, 90, 0.98, 1, 0.2, "put"))
print(pyqff.black_76_formula(100, 90, 0.98, 1, 0.2, "call"))

act360 = pyqff.Actual360()
act365 = pyqff.Actual365()
print(act360)

d1 = pyqff.as_boost_date("2018-02-10")
d2 = pyqff.as_boost_date("2018-12-30")
print(d1)
print(pyqff.boost_date_to_string(d1))

print(act360.CalculateYearFraction(d1,d2))
print(act365.CalculateYearFraction(d1,d2))

london = pyqff.LondonCalendar()
print(london)
print(london.IsHoliday(d1))
print(london.IsWeekend(d1))
print(london.IsBusinessDay(d1))

following = pyqff.Following();
print(pyqff.boost_date_to_string(following.Adjust(d1,london)))
