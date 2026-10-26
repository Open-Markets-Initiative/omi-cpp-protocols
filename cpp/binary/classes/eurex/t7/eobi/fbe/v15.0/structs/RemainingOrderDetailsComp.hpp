#pragma once

#include <chrono>
#include <cstddef>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// Remaining Order Details Comp
class RemainingOrderDetailsComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    RemainingOrderDetailsComp() = default;
    RemainingOrderDetailsComp(std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority, std::optional<Decimal> display_qty, std::optional<Decimal> price);

    // Trd Reg Ts Prev Time Priority:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority() const;
    void set_trd_reg_ts_prev_time_priority(std::optional<std::chrono::nanoseconds> value);

    // Display Qty:
    std::optional<Decimal> display_qty() const;
    void set_display_qty(std::optional<Decimal> value);

    // Price:
    std::optional<Decimal> price() const;
    void set_price(std::optional<Decimal> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RemainingOrderDetailsComp& other) const;
    bool operator!=(const RemainingOrderDetailsComp& other) const;

  private:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority_{};
    std::optional<Decimal> display_qty_{};
    std::optional<Decimal> price_{};
};

std::ostream& operator<<(std::ostream& out, const RemainingOrderDetailsComp& value);

} // namespace eurex::t7::eobi::fbe::v15_0
