#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Net Chg Prev Day
class NetChgPrevDay {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    NetChgPrevDay() = default;
    NetChgPrevDay(std::int8_t net_chg_prev_day_exponent, std::int32_t net_chg_prev_day_mantissa);

    // Net Chg Prev Day Exponent: Net change of last sale price relative to previous close
    // price. Sign of this value implies direction of change.
    std::int8_t net_chg_prev_day_exponent() const;
    void set_net_chg_prev_day_exponent(std::int8_t value);

    // Net Chg Prev Day Mantissa: Net change of last sale price relative to previous close
    // price. Sign of this value implies direction of change.
    std::int32_t net_chg_prev_day_mantissa() const;
    void set_net_chg_prev_day_mantissa(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const NetChgPrevDay& other) const;
    bool operator!=(const NetChgPrevDay& other) const;

  private:
    std::int8_t net_chg_prev_day_exponent_{};
    std::int32_t net_chg_prev_day_mantissa_{};
};

std::ostream& operator<<(std::ostream& out, const NetChgPrevDay& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
