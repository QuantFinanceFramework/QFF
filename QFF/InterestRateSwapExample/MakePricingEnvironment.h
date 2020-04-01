#pragma once
#include <Actual365.h>
#include <CurveInterpolator.h>
#include <Interpolation.h>
#include <PricingEnvironment.h>

#include <ZeroRateCurve.h>

#include <memory>
#include <vector>

using namespace aad;
using namespace qff_a;
using boost::gregorian::date;
using std::map;
using std::string;
using std::unique_ptr;
using std::vector;

inline unique_ptr<PricingEnvironment<a_double>> MakePricingEnvironment() {
  const date pricing_date{2020, 1, 31};

  auto interpolator = CurveInterpolator<a_double>{
      &ProductLinearInterpol<a_double>, &ProductLinearExtrapol<a_double>};
  const Actual365 day_counter{};

  vector ff_pillars{
      date(2020, 2, 3), date(2020, 2, 13), date(2020, 2, 20), date(2020, 3, 6),
      date(2020, 4, 8), date(2020, 5, 6),  date(2020, 6, 8),  date(2020, 7, 8),
      date(2020, 8, 6), date(2020, 11, 6), date(2021, 2, 8),  date(2021, 8, 4),
      date(2022, 2, 4), date(2023, 2, 6),  date(2024, 2, 5),  date(2025, 2, 4),
      date(2026, 2, 4), date(2027, 2, 4),  date(2028, 2, 4),  date(2029, 2, 5),
      date(2030, 2, 4), date(2032, 2, 4),  date(2035, 2, 5),  date(2040, 2, 6),
      date(2045, 2, 6), date(2050, 2, 4),  date(2060, 2, 4)};

  vector ff_zeros{0.0157142629201847, 0.0160406863209875, 0.0160824439348794,
                  0.0161134455264112, 0.0160416235621084, 0.0159570512563784,
                  0.0158228733810686, 0.0156275866647933, 0.0154711858102748,
                  0.0148764481371773, 0.0142306690193869, 0.0132755841877428,
                  0.0126999728943875, 0.0121777751396347, 0.0120243963064879,
                  0.012061471498624,  0.0122453808443152, 0.0124577010089707,
                  0.0127362002510347, 0.0130122544457647, 0.0133075208792979,
                  0.0138503783924619, 0.0144669449582222, 0.0150971255186208,
                  0.0153189459232633, 0.0153272725963219, 0.0152905184676551};

  std::vector<a_double> ff_zeros_a(size(ff_zeros));
  convert_collection(ff_zeros.begin(), ff_zeros.end(), ff_zeros_a.begin());

  auto ff_curve = std::make_unique<ZeroRateCurve<a_double>>(
      pricing_date, "USD_FF", day_counter, interpolator, std::move(ff_pillars),
      ff_zeros_a);

  vector libor3m_pillars{
      date(2020, 5, 4),   date(2020, 6, 18),  date(2020, 9, 17),
      date(2020, 12, 16), date(2021, 3, 16),  date(2021, 6, 17),
      date(2021, 9, 16),  date(2021, 12, 15), date(2022, 3, 15),
      date(2022, 6, 16),  date(2022, 9, 15),  date(2022, 12, 21),
      date(2023, 3, 21),  date(2024, 2, 6),   date(2025, 2, 4),
      date(2026, 2, 4),   date(2027, 2, 4),   date(2028, 2, 4),
      date(2029, 2, 6),   date(2030, 2, 5),   date(2032, 2, 4),
      date(2035, 2, 6),   date(2040, 2, 6),   date(2045, 2, 6),
      date(2050, 2, 4),   date(2060, 2, 4)};

  vector libor3m_zeros{
      0.0178381083493583, 0.0173969812276502, 0.0168642145140453,
      0.016289592662108,  0.0158679325431119, 0.0153823991234107,
      0.0150126372200794, 0.0147145816665658, 0.0145246258808826,
      0.0143506404390577, 0.0142273222259718, 0.0141323537142728,
      0.0140837805673723, 0.0139972646586653, 0.0140599580931725,
      0.0142562020820564, 0.0144740641410424, 0.0147642468871795,
      0.0150532567844303, 0.0153470803109129, 0.0158999075443918,
      0.0165137979181888, 0.0171474776654111, 0.0173679270402262,
      0.0173759527633301, 0.017339032984036};

  std::vector<a_double> libor3m_zeros_a(size(libor3m_zeros));
  convert_collection(libor3m_zeros.begin(), libor3m_zeros.end(),
                     libor3m_zeros_a.begin());

  auto libor3m_curve = std::make_unique<ZeroRateCurve<a_double>>(
      pricing_date, "USD_LIBOR_3M", day_counter, interpolator,
      std::move(libor3m_pillars), libor3m_zeros_a);

  vector sofr_pillars{
      date(2020, 2, 3), date(2020, 2, 13), date(2020, 2, 20), date(2020, 3, 6),
      date(2020, 4, 8), date(2020, 5, 6),  date(2020, 6, 8),  date(2020, 7, 8),
      date(2020, 8, 6), date(2020, 11, 6), date(2021, 2, 8),  date(2021, 8, 6),
      date(2022, 2, 8), date(2023, 2, 8),  date(2024, 2, 7),  date(2025, 2, 6),
      date(2026, 2, 6), date(2027, 2, 8),  date(2028, 2, 8),  date(2029, 2, 7),
      date(2030, 2, 6), date(2032, 2, 6),  date(2035, 2, 7),  date(2040, 2, 8),
      date(2045, 2, 8), date(2050, 2, 8),  date(2060, 2, 6)};

  vector sofr_zeros{0.0155115111621324, 0.0159627105145181, 0.016007651918168,
                    0.0160889508973192, 0.0160450382715921, 0.0159760969280487,
                    0.0158517967194372, 0.0156838471034493, 0.0155392748400634,
                    0.0149713491734572, 0.0143452211370029, 0.0133421615063197,
                    0.0127703101289814, 0.0122320136003192, 0.0120743776924345,
                    0.012086480928962,  0.0122580732564621, 0.0124248966495594,
                    0.0126903888461651, 0.012951533342499,  0.0132193237827014,
                    0.0137198768700395, 0.0142521157256569, 0.0148329746749559,
                    0.014997059129347,  0.0149464758441065, 0.0146574226546979};

  std::vector<a_double> sofr_zeros_a(size(sofr_zeros));
  convert_collection(sofr_zeros.begin(), sofr_zeros.end(),
                     sofr_zeros_a.begin());

  auto sofr_curve = std::make_unique<ZeroRateCurve<a_double>>(
      pricing_date, "USD_SOFR", day_counter, interpolator,
      std::move(sofr_pillars), sofr_zeros_a);

  map<string, unique_ptr<IInterestRateCurve<a_double>>> curve_set;
  curve_set.emplace(std::make_pair("USD_FF", std::move(ff_curve)));
  curve_set.emplace(std::make_pair("USD_LIBOR_3M", std::move(libor3m_curve)));
  curve_set.emplace(std::make_pair("USD_SOFR", std::move(sofr_curve)));

  map<string, unique_ptr<ICreditCurve<a_double>>> credit_curve_set;

  map<string, map<date, double>> past_fixing_set{
      std::make_pair("USD_FF", map{std::make_pair(date(2019, 9, 3), 0.0213),
                                   std::make_pair(date(2019, 9, 4), 0.0213),
                                   std::make_pair(date(2019, 9, 5), 0.0213),
                                   std::make_pair(date(2019, 9, 6), 0.0212),
                                   std::make_pair(date(2019, 9, 9), 0.0213),
                                   std::make_pair(date(2019, 9, 10), 0.0213),
                                   std::make_pair(date(2019, 9, 11), 0.0213),
                                   std::make_pair(date(2019, 9, 12), 0.0213),
                                   std::make_pair(date(2019, 9, 13), 0.0214),
                                   std::make_pair(date(2019, 9, 16), 0.0225),
                                   std::make_pair(date(2019, 9, 17), 0.023),
                                   std::make_pair(date(2019, 9, 18), 0.0225),
                                   std::make_pair(date(2019, 9, 19), 0.019),
                                   std::make_pair(date(2019, 9, 20), 0.019),
                                   std::make_pair(date(2019, 9, 23), 0.019),
                                   std::make_pair(date(2019, 9, 24), 0.019),
                                   std::make_pair(date(2019, 9, 25), 0.019),
                                   std::make_pair(date(2019, 9, 26), 0.0185),
                                   std::make_pair(date(2019, 9, 27), 0.0183),
                                   std::make_pair(date(2019, 9, 30), 0.019),
                                   std::make_pair(date(2019, 10, 1), 0.0188),
                                   std::make_pair(date(2019, 10, 2), 0.0185),
                                   std::make_pair(date(2019, 10, 3), 0.0183),
                                   std::make_pair(date(2019, 10, 4), 0.0182),
                                   std::make_pair(date(2019, 10, 7), 0.0182),
                                   std::make_pair(date(2019, 10, 8), 0.0182),
                                   std::make_pair(date(2019, 10, 9), 0.0182),
                                   std::make_pair(date(2019, 10, 10), 0.0182),
                                   std::make_pair(date(2019, 10, 11), 0.0182),
                                   std::make_pair(date(2019, 10, 15), 0.019),
                                   std::make_pair(date(2019, 10, 16), 0.019),
                                   std::make_pair(date(2019, 10, 17), 0.0185),
                                   std::make_pair(date(2019, 10, 18), 0.0185),
                                   std::make_pair(date(2019, 10, 21), 0.0185),
                                   std::make_pair(date(2019, 10, 22), 0.0185),
                                   std::make_pair(date(2019, 10, 23), 0.0185),
                                   std::make_pair(date(2019, 10, 24), 0.0185),
                                   std::make_pair(date(2019, 10, 25), 0.0183),
                                   std::make_pair(date(2019, 10, 28), 0.0183),
                                   std::make_pair(date(2019, 10, 29), 0.0182),
                                   std::make_pair(date(2019, 10, 30), 0.0182),
                                   std::make_pair(date(2019, 10, 31), 0.0158),
                                   std::make_pair(date(2019, 11, 1), 0.0157),
                                   std::make_pair(date(2019, 11, 4), 0.0156),
                                   std::make_pair(date(2019, 11, 5), 0.0156),
                                   std::make_pair(date(2019, 11, 6), 0.0155),
                                   std::make_pair(date(2019, 11, 7), 0.0155),
                                   std::make_pair(date(2019, 11, 8), 0.0155),
                                   std::make_pair(date(2019, 11, 12), 0.0155),
                                   std::make_pair(date(2019, 11, 13), 0.0155),
                                   std::make_pair(date(2019, 11, 14), 0.0155),
                                   std::make_pair(date(2019, 11, 15), 0.0155),
                                   std::make_pair(date(2019, 11, 18), 0.0155),
                                   std::make_pair(date(2019, 11, 19), 0.0155),
                                   std::make_pair(date(2019, 11, 20), 0.0155),
                                   std::make_pair(date(2019, 11, 21), 0.0155),
                                   std::make_pair(date(2019, 11, 22), 0.0155),
                                   std::make_pair(date(2019, 11, 25), 0.0155),
                                   std::make_pair(date(2019, 11, 26), 0.0155),
                                   std::make_pair(date(2019, 11, 27), 0.0155),
                                   std::make_pair(date(2019, 11, 29), 0.0156),
                                   std::make_pair(date(2019, 12, 2), 0.0156),
                                   std::make_pair(date(2019, 12, 3), 0.0155),
                                   std::make_pair(date(2019, 12, 4), 0.0155),
                                   std::make_pair(date(2019, 12, 5), 0.0155),
                                   std::make_pair(date(2019, 12, 6), 0.0155),
                                   std::make_pair(date(2019, 12, 9), 0.0155),
                                   std::make_pair(date(2019, 12, 10), 0.0155),
                                   std::make_pair(date(2019, 12, 11), 0.0155),
                                   std::make_pair(date(2019, 12, 12), 0.0155),
                                   std::make_pair(date(2019, 12, 13), 0.0155),
                                   std::make_pair(date(2019, 12, 16), 0.0156),
                                   std::make_pair(date(2019, 12, 17), 0.0155),
                                   std::make_pair(date(2019, 12, 18), 0.0155),
                                   std::make_pair(date(2019, 12, 19), 0.0155),
                                   std::make_pair(date(2019, 12, 20), 0.0155),
                                   std::make_pair(date(2019, 12, 23), 0.0155),
                                   std::make_pair(date(2019, 12, 24), 0.0155),
                                   std::make_pair(date(2019, 12, 26), 0.0155),
                                   std::make_pair(date(2019, 12, 27), 0.0155),
                                   std::make_pair(date(2019, 12, 30), 0.0155),
                                   std::make_pair(date(2019, 12, 31), 0.0155),
                                   std::make_pair(date(2020, 1, 2), 0.0155),
                                   std::make_pair(date(2020, 1, 3), 0.0155),
                                   std::make_pair(date(2020, 1, 6), 0.0155),
                                   std::make_pair(date(2020, 1, 7), 0.0155),
                                   std::make_pair(date(2020, 1, 8), 0.0155),
                                   std::make_pair(date(2020, 1, 9), 0.0155),
                                   std::make_pair(date(2020, 1, 10), 0.0154),
                                   std::make_pair(date(2020, 1, 13), 0.0154),
                                   std::make_pair(date(2020, 1, 14), 0.0154),
                                   std::make_pair(date(2020, 1, 15), 0.0154),
                                   std::make_pair(date(2020, 1, 16), 0.0154),
                                   std::make_pair(date(2020, 1, 17), 0.0155),
                                   std::make_pair(date(2020, 1, 21), 0.0155),
                                   std::make_pair(date(2020, 1, 22), 0.0155),
                                   std::make_pair(date(2020, 1, 23), 0.0155),
                                   std::make_pair(date(2020, 1, 24), 0.0155),
                                   std::make_pair(date(2020, 1, 27), 0.0155),
                                   std::make_pair(date(2020, 1, 28), 0.0155),
                                   std::make_pair(date(2020, 1, 29), 0.0155),
                                   std::make_pair(date(2020, 1, 30), 0.016)}),
      std::make_pair("USD_LIBOR_3M",
                     map{std::make_pair(date(2019, 9, 2), 0.0213275),
                         std::make_pair(date(2019, 9, 3), 0.0212663),
                         std::make_pair(date(2019, 9, 4), 0.0211238),
                         std::make_pair(date(2019, 9, 5), 0.0210213),
                         std::make_pair(date(2019, 9, 6), 0.0213413),
                         std::make_pair(date(2019, 9, 9), 0.0213838),
                         std::make_pair(date(2019, 9, 10), 0.0213163),
                         std::make_pair(date(2019, 9, 11), 0.0212725),
                         std::make_pair(date(2019, 9, 12), 0.021185),
                         std::make_pair(date(2019, 9, 13), 0.0213938),
                         std::make_pair(date(2019, 9, 16), 0.0214513),
                         std::make_pair(date(2019, 9, 17), 0.0216413),
                         std::make_pair(date(2019, 9, 18), 0.0215588),
                         std::make_pair(date(2019, 9, 19), 0.0215888),
                         std::make_pair(date(2019, 9, 20), 0.0213463),
                         std::make_pair(date(2019, 9, 23), 0.0210625),
                         std::make_pair(date(2019, 9, 24), 0.02113),
                         std::make_pair(date(2019, 9, 25), 0.0209963),
                         std::make_pair(date(2019, 9, 26), 0.0210438),
                         std::make_pair(date(2019, 9, 27), 0.0209863),
                         std::make_pair(date(2019, 9, 30), 0.0208513),
                         std::make_pair(date(2019, 10, 1), 0.0208863),
                         std::make_pair(date(2019, 10, 2), 0.0205638),
                         std::make_pair(date(2019, 10, 3), 0.0204313),
                         std::make_pair(date(2019, 10, 4), 0.02027),
                         std::make_pair(date(2019, 10, 7), 0.02012),
                         std::make_pair(date(2019, 10, 8), 0.020095),
                         std::make_pair(date(2019, 10, 9), 0.0198425),
                         std::make_pair(date(2019, 10, 10), 0.0198613),
                         std::make_pair(date(2019, 10, 11), 0.0200088),
                         std::make_pair(date(2019, 10, 14), 0.0200088),
                         std::make_pair(date(2019, 10, 15), 0.0200213),
                         std::make_pair(date(2019, 10, 16), 0.0200325),
                         std::make_pair(date(2019, 10, 17), 0.0196588),
                         std::make_pair(date(2019, 10, 18), 0.0195325),
                         std::make_pair(date(2019, 10, 21), 0.01934),
                         std::make_pair(date(2019, 10, 22), 0.01936),
                         std::make_pair(date(2019, 10, 23), 0.0193963),
                         std::make_pair(date(2019, 10, 24), 0.0193563),
                         std::make_pair(date(2019, 10, 25), 0.0192813),
                         std::make_pair(date(2019, 10, 28), 0.019355),
                         std::make_pair(date(2019, 10, 29), 0.0192713),
                         std::make_pair(date(2019, 10, 30), 0.0190913),
                         std::make_pair(date(2019, 10, 31), 0.0190225),
                         std::make_pair(date(2019, 11, 1), 0.018905),
                         std::make_pair(date(2019, 11, 4), 0.0190825),
                         std::make_pair(date(2019, 11, 5), 0.018935),
                         std::make_pair(date(2019, 11, 6), 0.0190425),
                         std::make_pair(date(2019, 11, 7), 0.0190138),
                         std::make_pair(date(2019, 11, 8), 0.0190063),
                         std::make_pair(date(2019, 11, 11), 0.0190463),
                         std::make_pair(date(2019, 11, 12), 0.0190925),
                         std::make_pair(date(2019, 11, 13), 0.0190988),
                         std::make_pair(date(2019, 11, 14), 0.0190413),
                         std::make_pair(date(2019, 11, 15), 0.0190263),
                         std::make_pair(date(2019, 11, 18), 0.018985),
                         std::make_pair(date(2019, 11, 19), 0.0189463),
                         std::make_pair(date(2019, 11, 20), 0.0189875),
                         std::make_pair(date(2019, 11, 21), 0.019095),
                         std::make_pair(date(2019, 11, 22), 0.0191725),
                         std::make_pair(date(2019, 11, 25), 0.0191863),
                         std::make_pair(date(2019, 11, 26), 0.0190863),
                         std::make_pair(date(2019, 11, 27), 0.0191375),
                         std::make_pair(date(2019, 11, 28), 0.0190688),
                         std::make_pair(date(2019, 11, 29), 0.019055),
                         std::make_pair(date(2019, 12, 2), 0.0190013),
                         std::make_pair(date(2019, 12, 3), 0.018915),
                         std::make_pair(date(2019, 12, 4), 0.0188713),
                         std::make_pair(date(2019, 12, 5), 0.01885),
                         std::make_pair(date(2019, 12, 6), 0.018905),
                         std::make_pair(date(2019, 12, 9), 0.0188838),
                         std::make_pair(date(2019, 12, 10), 0.0188725),
                         std::make_pair(date(2019, 12, 11), 0.0188738),
                         std::make_pair(date(2019, 12, 12), 0.0189363),
                         std::make_pair(date(2019, 12, 13), 0.0189963),
                         std::make_pair(date(2019, 12, 16), 0.018985),
                         std::make_pair(date(2019, 12, 17), 0.019025),
                         std::make_pair(date(2019, 12, 18), 0.01908),
                         std::make_pair(date(2019, 12, 19), 0.0192775),
                         std::make_pair(date(2019, 12, 20), 0.0193475),
                         std::make_pair(date(2019, 12, 23), 0.0194663),
                         std::make_pair(date(2019, 12, 24), 0.019605),
                         std::make_pair(date(2019, 12, 25), 0.019605),
                         std::make_pair(date(2019, 12, 26), 0.019605),
                         std::make_pair(date(2019, 12, 27), 0.0194463),
                         std::make_pair(date(2019, 12, 30), 0.0190938),
                         std::make_pair(date(2019, 12, 31), 0.0190838),
                         std::make_pair(date(2020, 1, 2), 0.0190025),
                         std::make_pair(date(2020, 1, 3), 0.0187388),
                         std::make_pair(date(2020, 1, 6), 0.0187225),
                         std::make_pair(date(2020, 1, 7), 0.01878),
                         std::make_pair(date(2020, 1, 8), 0.01834),
                         std::make_pair(date(2020, 1, 9), 0.0184788),
                         std::make_pair(date(2020, 1, 10), 0.0183775),
                         std::make_pair(date(2020, 1, 13), 0.0183125),
                         std::make_pair(date(2020, 1, 14), 0.0184263),
                         std::make_pair(date(2020, 1, 15), 0.0183613),
                         std::make_pair(date(2020, 1, 16), 0.0182663),
                         std::make_pair(date(2020, 1, 17), 0.0181913),
                         std::make_pair(date(2020, 1, 20), 0.0180213),
                         std::make_pair(date(2020, 1, 21), 0.0180625),
                         std::make_pair(date(2020, 1, 22), 0.0180088),
                         std::make_pair(date(2020, 1, 23), 0.0179413),
                         std::make_pair(date(2020, 1, 24), 0.0179538),
                         std::make_pair(date(2020, 1, 27), 0.017745),
                         std::make_pair(date(2020, 1, 28), 0.017695),
                         std::make_pair(date(2020, 1, 29), 0.0177713),
                         std::make_pair(date(2020, 1, 30), 0.0176325),
                         std::make_pair(date(2020, 1, 31), 0.0175113)}),
      std::make_pair("USD_SOFR",
                     map{std::make_pair(date(2019, 9, 2), 0.0216),
                         std::make_pair(date(2019, 9, 3), 0.0217),
                         std::make_pair(date(2019, 9, 4), 0.0221),
                         std::make_pair(date(2019, 9, 5), 0.0221),
                         std::make_pair(date(2019, 9, 6), 0.0215),
                         std::make_pair(date(2019, 9, 9), 0.0212),
                         std::make_pair(date(2019, 9, 10), 0.0214),
                         std::make_pair(date(2019, 9, 11), 0.0215),
                         std::make_pair(date(2019, 9, 12), 0.022),
                         std::make_pair(date(2019, 9, 13), 0.022),
                         std::make_pair(date(2019, 9, 16), 0.0243),
                         std::make_pair(date(2019, 9, 17), 0.0525),
                         std::make_pair(date(2019, 9, 18), 0.0255),
                         std::make_pair(date(2019, 9, 19), 0.0195),
                         std::make_pair(date(2019, 9, 20), 0.0186),
                         std::make_pair(date(2019, 9, 23), 0.0185),
                         std::make_pair(date(2019, 9, 24), 0.0196),
                         std::make_pair(date(2019, 9, 25), 0.0201),
                         std::make_pair(date(2019, 9, 26), 0.0185),
                         std::make_pair(date(2019, 9, 27), 0.0182),
                         std::make_pair(date(2019, 9, 30), 0.0235),
                         std::make_pair(date(2019, 10, 1), 0.0188),
                         std::make_pair(date(2019, 10, 2), 0.0185),
                         std::make_pair(date(2019, 10, 3), 0.0184),
                         std::make_pair(date(2019, 10, 4), 0.0182),
                         std::make_pair(date(2019, 10, 7), 0.0183),
                         std::make_pair(date(2019, 10, 8), 0.0185),
                         std::make_pair(date(2019, 10, 9), 0.0185),
                         std::make_pair(date(2019, 10, 10), 0.0185),
                         std::make_pair(date(2019, 10, 11), 0.0185),
                         std::make_pair(date(2019, 10, 14), 0.0185),
                         std::make_pair(date(2019, 10, 15), 0.02),
                         std::make_pair(date(2019, 10, 16), 0.0205),
                         std::make_pair(date(2019, 10, 17), 0.0195),
                         std::make_pair(date(2019, 10, 18), 0.0188),
                         std::make_pair(date(2019, 10, 21), 0.0186),
                         std::make_pair(date(2019, 10, 22), 0.0187),
                         std::make_pair(date(2019, 10, 23), 0.0187),
                         std::make_pair(date(2019, 10, 24), 0.0186),
                         std::make_pair(date(2019, 10, 25), 0.0184),
                         std::make_pair(date(2019, 10, 28), 0.0182),
                         std::make_pair(date(2019, 10, 29), 0.0181),
                         std::make_pair(date(2019, 10, 30), 0.0182),
                         std::make_pair(date(2019, 10, 31), 0.0176),
                         std::make_pair(date(2019, 11, 1), 0.0158),
                         std::make_pair(date(2019, 11, 4), 0.0156),
                         std::make_pair(date(2019, 11, 5), 0.0158),
                         std::make_pair(date(2019, 11, 6), 0.0157),
                         std::make_pair(date(2019, 11, 7), 0.0156),
                         std::make_pair(date(2019, 11, 8), 0.0156),
                         std::make_pair(date(2019, 11, 11), 0.0156),
                         std::make_pair(date(2019, 11, 12), 0.0157),
                         std::make_pair(date(2019, 11, 13), 0.0157),
                         std::make_pair(date(2019, 11, 14), 0.0158),
                         std::make_pair(date(2019, 11, 15), 0.0159),
                         std::make_pair(date(2019, 11, 18), 0.0156),
                         std::make_pair(date(2019, 11, 19), 0.0157),
                         std::make_pair(date(2019, 11, 20), 0.0157),
                         std::make_pair(date(2019, 11, 21), 0.0158),
                         std::make_pair(date(2019, 11, 22), 0.0158),
                         std::make_pair(date(2019, 11, 25), 0.0156),
                         std::make_pair(date(2019, 11, 26), 0.0154),
                         std::make_pair(date(2019, 11, 27), 0.0154),
                         std::make_pair(date(2019, 11, 28), 0.0155),
                         std::make_pair(date(2019, 11, 29), 0.0165),
                         std::make_pair(date(2019, 12, 2), 0.0163),
                         std::make_pair(date(2019, 12, 3), 0.0155),
                         std::make_pair(date(2019, 12, 4), 0.0154),
                         std::make_pair(date(2019, 12, 5), 0.0155),
                         std::make_pair(date(2019, 12, 6), 0.0155),
                         std::make_pair(date(2019, 12, 9), 0.0156),
                         std::make_pair(date(2019, 12, 10), 0.0155),
                         std::make_pair(date(2019, 12, 11), 0.0154),
                         std::make_pair(date(2019, 12, 12), 0.0153),
                         std::make_pair(date(2019, 12, 13), 0.0154),
                         std::make_pair(date(2019, 12, 16), 0.0162),
                         std::make_pair(date(2019, 12, 17), 0.0154),
                         std::make_pair(date(2019, 12, 18), 0.0153),
                         std::make_pair(date(2019, 12, 19), 0.0153),
                         std::make_pair(date(2019, 12, 20), 0.0153),
                         std::make_pair(date(2019, 12, 23), 0.0152),
                         std::make_pair(date(2019, 12, 24), 0.0152),
                         std::make_pair(date(2019, 12, 25), 0.0152),
                         std::make_pair(date(2019, 12, 26), 0.0152),
                         std::make_pair(date(2019, 12, 27), 0.0153),
                         std::make_pair(date(2019, 12, 30), 0.0154),
                         std::make_pair(date(2019, 12, 31), 0.0155),
                         std::make_pair(date(2020, 1, 1), 0.0155),
                         std::make_pair(date(2020, 1, 2), 0.0154),
                         std::make_pair(date(2020, 1, 3), 0.0155),
                         std::make_pair(date(2020, 1, 6), 0.0155),
                         std::make_pair(date(2020, 1, 7), 0.0156),
                         std::make_pair(date(2020, 1, 8), 0.0155),
                         std::make_pair(date(2020, 1, 9), 0.0155),
                         std::make_pair(date(2020, 1, 10), 0.0155),
                         std::make_pair(date(2020, 1, 13), 0.0154),
                         std::make_pair(date(2020, 1, 14), 0.0155),
                         std::make_pair(date(2020, 1, 15), 0.0156),
                         std::make_pair(date(2020, 1, 16), 0.0155),
                         std::make_pair(date(2020, 1, 17), 0.0154),
                         std::make_pair(date(2020, 1, 20), 0.0154),
                         std::make_pair(date(2020, 1, 21), 0.0154),
                         std::make_pair(date(2020, 1, 22), 0.0154),
                         std::make_pair(date(2020, 1, 23), 0.0154),
                         std::make_pair(date(2020, 1, 24), 0.0153),
                         std::make_pair(date(2020, 1, 27), 0.0153),
                         std::make_pair(date(2020, 1, 28), 0.0153),
                         std::make_pair(date(2020, 1, 29), 0.0153),
                         std::make_pair(date(2020, 1, 30), 0.0158)})};

  map<string, a_double> fx_today_map;
  fx_today_map.emplace(std::make_pair("EURUSD", a_double(1.102231639)));

  return std::make_unique<PricingEnvironment<a_double>>(
      pricing_date, std::move(curve_set), std::move(past_fixing_set),
      std::move(credit_curve_set), std::move(fx_today_map));
}