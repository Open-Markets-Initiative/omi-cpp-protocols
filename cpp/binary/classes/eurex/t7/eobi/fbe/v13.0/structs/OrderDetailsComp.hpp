#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/HhiIndicator.hpp"
#include "../enums/OrdType.hpp"
#include "../enums/Side.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// Order Details Comp
class OrderDetailsComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    OrderDetailsComp() = default;
    OrderDetailsComp(std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority, std::optional<Decimal> display_qty, std::optional<Side> side, std::optional<OrdType> ord_type, std::optional<HhiIndicator> hhi_indicator, const std::array<std::byte, 5>& pad5, std::optional<Decimal> price);

    // Trd Reg Ts Time Priority:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority() const;
    void set_trd_reg_ts_time_priority(std::optional<std::chrono::nanoseconds> value);

    // Display Qty:
    std::optional<Decimal> display_qty() const;
    void set_display_qty(std::optional<Decimal> value);

    // Side:
    std::optional<Side> side() const;
    void set_side(std::optional<Side> value);

    // Ord Type:
    std::optional<OrdType> ord_type() const;
    void set_ord_type(std::optional<OrdType> value);

    // Hhi Indicator:
    std::optional<HhiIndicator> hhi_indicator() const;
    void set_hhi_indicator(std::optional<HhiIndicator> value);

    // Pad5:
    const std::array<std::byte, 5>& pad5() const;
    std::array<std::byte, 5>& pad5();
    void set_pad5(const std::array<std::byte, 5>& value);

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

    bool operator==(const OrderDetailsComp& other) const;
    bool operator!=(const OrderDetailsComp& other) const;

  private:
    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority_{};
    std::optional<Decimal> display_qty_{};
    std::optional<Side> side_{};
    std::optional<OrdType> ord_type_{};
    std::optional<HhiIndicator> hhi_indicator_{};
    std::array<std::byte, 5> pad5_{};
    std::optional<Decimal> price_{};
};

std::ostream& operator<<(std::ostream& out, const OrderDetailsComp& value);

} // namespace eurex::t7::eobi::fbe::v13_0
