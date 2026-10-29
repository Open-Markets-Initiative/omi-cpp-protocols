#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// OrderDetails
class OrderDetails {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    OrderDetails() = default;
    OrderDetails(std::chrono::nanoseconds trd_reg_ts_time_priority, std::int64_t display_qty, Side side, const std::array<std::byte, 7>& pad_7, Decimal price);

    // Trd Reg Ts Time Priority: Priority timestamp.
    std::chrono::nanoseconds trd_reg_ts_time_priority() const;
    void set_trd_reg_ts_time_priority(std::chrono::nanoseconds value);

    // Display Qty: Quantity.
    std::int64_t display_qty() const;
    void set_display_qty(std::int64_t value);

    // Side: Side of the order.
    Side side() const;
    void set_side(Side value);

    // Pad 7: not used
    const std::array<std::byte, 7>& pad_7() const;
    std::array<std::byte, 7>& pad_7();
    void set_pad_7(const std::array<std::byte, 7>& value);

    // Price: Reserved for future use.
    Decimal price() const;
    void set_price(Decimal value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const OrderDetails& other) const;
    bool operator!=(const OrderDetails& other) const;

  private:
    std::chrono::nanoseconds trd_reg_ts_time_priority_{};
    std::int64_t display_qty_{};
    Side side_{};
    std::array<std::byte, 7> pad_7_{};
    Decimal price_{ 0, -6 };
};

std::ostream& operator<<(std::ostream& out, const OrderDetails& value);

} // namespace bse::bseindia::eobi::fbe::v1_4
