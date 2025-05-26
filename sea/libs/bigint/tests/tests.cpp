#include <BigInt.hpp>
#include <optional>
#include <tuple>
#include <vector>

#include <catch2/catch_test_macros.hpp>

typedef std::tuple<std::string, std::string, std::string> string_triple;

TEST_CASE("Powers of ten") {

  CHECK(BigInt::Int("10").is_powerof10());
  CHECK(BigInt::Int("1000").is_powerof10());
  CHECK_FALSE(BigInt::Int("10101").is_powerof10());
}

TEST_CASE("Raise ten") {

  CHECK(BigInt::Int("1").pow10(1) == BigInt::Int("10"));
  CHECK(BigInt::Int("123").pow10(0) == BigInt::Int("1"));
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
      {"12345678900987654321", "12345678900987654321", "24691357801975308642"}};

  for (auto triple : cases) {
    BigInt::Int a = BigInt::Int(get<0>(triple));
    BigInt::Int b = BigInt::Int(get<1>(triple));
    BigInt::Int c = BigInt::Int(get<2>(triple));
    CHECK(BigInt::add(a, b) == c);
  }
}

TEST_CASE("Subtraction") {
  std::vector<string_triple> cases = {
      {"99", "100", "-1"},  {"128", "256", "-128"}, {"256", "6", "250"},
      {"6", "256", "-250"}, {"0", "256", "-256"},   {"256", "256", "0"},
  };

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
      {"1463865525", "1416096094", "2072974252093759350"}};

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

    CHECK(BigInt::leq(a, b));
    CHECK_FALSE(BigInt::leq(b, a));
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

  SECTION("Simple") {
    auto [high, low] = BigInt::Int("12345").split(3);

    CHECK(high == BigInt::Int("12"));
    CHECK(low == BigInt::Int("345"));
  }

  SECTION("Eats") {
    auto [high, low] = BigInt::Int("12345").split(5);

    CHECK(high == BigInt::Int("0"));
    CHECK(low == BigInt::Int("12345"));
  }
}
