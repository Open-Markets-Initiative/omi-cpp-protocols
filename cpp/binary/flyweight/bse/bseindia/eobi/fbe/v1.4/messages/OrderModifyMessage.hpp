#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published if an existing order in the book is modified, whereby the new parameters might
// cause a change in time priority.
class OrderModifyMessage {
  public:
    static constexpr const char* name = "OrderModifyMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderModifyMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderModifyMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 72;
    static constexpr std::size_t fixed_size = 72;
    std::size_t encoded_size() const { return 72; }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::chrono::nanoseconds trd_reg_ts_prev_time_priority() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    Decimal prev_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(16))), -6); }

    std::int64_t prev_display_qty() const { return wire::read_i64_le(at(24)); }

    std::int64_t security_id() const { return wire::read_i64_le(at(32)); }

    OrderDetails order_details() const { return OrderDetails{ bytes_.subspan(40) }; }

    void print(std::ostream& out) const {
        out << "OrderModifyMessage{";
        out << "trd_reg_ts_time_in=";
        print::optional_duration(out, trd_reg_ts_time_in());
        out << ", trd_reg_ts_prev_time_priority=";
        out << trd_reg_ts_prev_time_priority().count();
        out << ", prev_price=";
        out << prev_price();
        out << ", prev_display_qty=";
        out << prev_display_qty();
        out << ", security_id=";
        out << security_id();
        out << ", order_details=";
        order_details().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderModifyMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
