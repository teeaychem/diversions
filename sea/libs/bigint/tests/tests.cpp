#include <BigInt.hpp>
#include <cstdint>
#include <optional>
#include <ranges>
#include <tuple>
#include <vector>

#include <catch2/catch_test_macros.hpp>

typedef std::tuple<std::string, std::string, std::string> string_triple;

TEST_CASE("From_64") {

  CHECK(BigInt::Int(64) == 64);
  CHECK(BigInt::Int(-64) == -64);
  CHECK(BigInt::Int(INT64_MAX) == INT64_MAX);
  CHECK(BigInt::Int(-INT64_MAX) == -INT64_MAX);
}

TEST_CASE("Powers of ten") {

  CHECK(BigInt::Int("10").is_powerof10());
  CHECK(BigInt::Int("1000").is_powerof10());
  CHECK_FALSE(BigInt::Int("10101").is_powerof10());
}

TEST_CASE("Raise ten") {

  CHECK(BigInt::Int("1").pow10(1) == BigInt::Int("10"));
  CHECK(BigInt::Int("123").pow10(0) == BigInt::Int("1"));
  CHECK(BigInt::Int("123").pow10(5) == BigInt::Int("12300000"));
  CHECK(BigInt::Int("123").pow10(10) == BigInt::Int("1230000000000"));

  // CHECK(BigInt::Int("1000").is_powerof10());
  // CHECK_FALSE(BigInt::Int("10101").is_powerof10());
}

TEST_CASE("Construction") {
  std::vector<std::string> check_strings = {"-1", "123"};

  for (auto check_string : check_strings) {
    REQUIRE(BigInt::Int(check_string).to_istring() == check_string);
  }

  CHECK_THROWS_AS(BigInt::Int(""), std::invalid_argument);
}

TEST_CASE("Addition") {
  std::vector<string_triple> cases = {
      {"1", "2", "3"},
      {"14160", "96094", "110254"},
      {"12345678900987654321", "12345678900987654321", "24691357801975308642"},
      {"3991", "6800", "10791"}};

  for (auto triple : cases) {
    BigInt::Int a = BigInt::Int(get<0>(triple));
    BigInt::Int b = BigInt::Int(get<1>(triple));
    BigInt::Int c = BigInt::Int(get<2>(triple));
    CHECK(BigInt::add(a, b) == c);
  }
}

TEST_CASE("Subtraction") {
  std::vector<string_triple> cases = {
      {"99", "100", "-1"},
      {"100", "99", "1"},
      {"128", "256", "-128"},
      {"256", "6", "250"},
      {"6", "256", "-250"},
      {"0", "256", "-256"},
      {"256", "256", "0"},
      {"2432828661", "423360000", "2009468661"},
      {
          "423360000",
          "2432828661",
          "-2009468661",
      },
      {"815915283247897734345611269596115894272000000000",
       "43253789432794798342",
       "815915283247897734345611269552862104839205201658"},
      {"43253789432794798342",
       "815915283247897734345611269596115894272000000000",
       "-815915283247897734345611269552862104839205201658"}};

  for (auto triple : cases) {
    BigInt::Int a = BigInt::Int(get<0>(triple));
    BigInt::Int b = BigInt::Int(get<1>(triple));
    BigInt::Int c = BigInt::Int(get<2>(triple));

    CHECK(BigInt::subtract(a, b) == c);
  }
}

TEST_CASE("Multiplication") {
  std::vector<string_triple> cases = {
      {"1", "2", "2"},
      {"123456789", "0", "0"},
      {"1234567890", "1234567890", "1524157875019052100"},
      {"1234567890", "-1234567890", "-1524157875019052100"},
      {"-1234567890", "-1234567890", "1524157875019052100"},
      {"1463865525", "1416096094", "2072974252093759350"},
      {"13", "6227020800", "80951270400"}};

  for (auto triple : cases) {
    BigInt::Int a = BigInt::Int(get<0>(triple));
    BigInt::Int b = BigInt::Int(get<1>(triple));
    BigInt::Int c = BigInt::Int(get<2>(triple));
    CHECK(BigInt::multiply(a, b) == c);
  }
}

TEST_CASE("LEQ") {
  std::vector<std::tuple<std::string, std::string>> cases = {
      {"99", "100"},
      {"128", "256"},
      {"8", "256"},
  };

  for (auto triple : cases) {
    BigInt::Int a = BigInt::Int(get<0>(triple));
    BigInt::Int b = BigInt::Int(get<1>(triple));

    CHECK(BigInt::abs_lt(a, b));
    CHECK_FALSE(BigInt::abs_lt(b, a));
  }
}

TEST_CASE("try_int64") {

  CHECK(BigInt::Int("0").try_int64() == 0);
  CHECK(BigInt::Int("1").try_int64() == 1);
  CHECK(BigInt::Int("-1").try_int64() == -1);
  CHECK(BigInt::Int("123456789").try_int64() == 123456789);
  CHECK(BigInt::Int("9223372036854775807").try_int64() == 9223372036854775807);

  CHECK(BigInt::Int("-9223372036854775807").try_int64() ==
        -9223372036854775807);

  CHECK(BigInt::Int("9223372036854775808").try_int64() == std::nullopt);
  CHECK(BigInt::Int("-9223372036854775808").try_int64() == std::nullopt);
}

TEST_CASE("Splits") {
  SECTION("Single 0") {
    auto [high, low] = BigInt::Int("1").abs_split(0);

    CHECK(high == BigInt::Int("1"));
    CHECK_FALSE(low.has_value());
  }

  SECTION("Single 1") {
    auto [high, low] = BigInt::Int("1").abs_split(1);

    CHECK_FALSE(high.has_value());
    CHECK(low == BigInt::Int("1"));
  }

  SECTION("Double") {
    auto [high, low] = BigInt::Int("13").abs_split(5);

    CHECK_FALSE(high.has_value());
    CHECK(low == BigInt::Int("13"));
  }

  SECTION("Simple") {
    auto [high, low] = BigInt::Int("12345").abs_split(3);

    CHECK(high == BigInt::Int("12"));
    CHECK(low == BigInt::Int("345"));
  }

  SECTION("Eats") {
    auto [high, low] = BigInt::Int("12345").abs_split(5);

    CHECK_FALSE(high.has_value());
    CHECK(low == BigInt::Int("12345"));
  }
}

TEST_CASE("Factorial") {

  SECTION("Sequence") {
    std::vector<std::string> factorials = {"1",
                                           "1",
                                           "2",
                                           "6",
                                           "24",
                                           "120",
                                           "720",
                                           "5040",
                                           "40320",
                                           "362880",
                                           "3628800",
                                           "39916800",
                                           "479001600",
                                           "6227020800",
                                           "87178291200",
                                           "1307674368000",
                                           "20922789888000",
                                           "355687428096000",
                                           "6402373705728000",
                                           "121645100408832000",
                                           "2432902008176640000",
                                           "51090942171709440000",
                                           "1124000727777607680000"};

    BigInt::Int factorial = BigInt::Int(1);

    for (int64_t i = 1; i < factorials.size() - 1; ++i) {

      REQUIRE(BigInt::Int(i) * BigInt::Int(factorials[i - 1]) ==
              BigInt::Int(factorials[i]));
    }
  }
}
