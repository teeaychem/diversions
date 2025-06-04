#include <cmath>
#include <iostream>


void digit_cancelling_fractions() {

  float_t product_n{1};
  float_t product_d{1};

  for (float_t c{1}; c < 10; ++c) {
    for (float_t d{1}; d < 10; ++d) {
      for (float_t n{1}; n < 10; ++n) {
        float_t base = d / n;

        if (1 <= base) {
          continue;
        }

        float_t d_a = c * 10 + d;
        float_t d_b = d * 10 + c;

        float_t n_a = c * 10 + n;
        float_t n_b = n * 10 + c;

        auto process = [&product_n, &product_d](float_t d, float_t n, float_t dx,
                                                float_t nx) {
          if ((d / n) == (dx / nx)) {
            std::cout << d << " / " << n << " & " << dx << " / " << nx << " - "
                      << "\n";
            product_d *= d;
            product_n *= n;
          }
        };

        process(d, n, d_a, n_a);
        process(d, n, d_b, n_a);
        process(d, n, d_a, n_b);
        process(d, n, d_b, n_b);
      }
    }
  }

  std::cout << product_d << " / " << product_n << "\n";
}
