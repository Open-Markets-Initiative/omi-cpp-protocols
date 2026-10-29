#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class MaxStrikePrice {
  public:
    static constexpr const char* name = "MaxStrikePrice";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MaxStrikePrice(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MaxStrikePrice has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    std::int8_t max_strike_price_exponent() const { return wire::read_i8(at(0)); }

    std::int32_t max_strike_price_mantissa() const { return wire::read_i32_be(at(1)); }

    void print(std::ostream& out) const {
        out << "MaxStrikePrice{";
        out << "max_strike_price_exponent=";
        out << static_cast<int>(max_strike_price_exponent());
        out << ", max_strike_price_mantissa=";
        out << max_strike_price_mantissa();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MaxStrikePrice& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
