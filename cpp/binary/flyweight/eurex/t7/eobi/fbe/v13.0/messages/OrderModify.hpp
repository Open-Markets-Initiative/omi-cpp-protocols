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
#include "../structs/OrderDetailsComp.hpp"
#include "../enums/PrevPriceHhiIndicator.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class OrderModify {
  public:
    static constexpr const char* name = "OrderModify";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderModify(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderModify has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 80;
    static constexpr std::size_t fixed_size = 80;
    std::size_t encoded_size() const { return 80; }

    std::optional<std::chrono::nanoseconds> request_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_prev_time_priority() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<Decimal> prev_price() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<Decimal> prev_display_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(32)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    OrderDetailsComp order_details_comp() const { return OrderDetailsComp{ bytes_.subspan(40) }; }

    std::optional<PrevPriceHhiIndicator> prev_price_hhi_indicator() const { return wire::nullable_enum<PrevPriceHhiIndicator>(wire::read_i8(at(72)), static_cast<std::int8_t>(0x80LL)); }

    std::span<const std::byte, 7> pad7() const { return bytes_.subspan(73).template first<7>(); }

    void print(std::ostream& out) const {
        out << "OrderModify{";
        out << "request_time=";
        print::optional_duration(out, request_time());
        out << ", trd_reg_ts_prev_time_priority=";
        print::optional_duration(out, trd_reg_ts_prev_time_priority());
        out << ", prev_price=";
        print::optional(out, prev_price());
        out << ", prev_display_qty=";
        print::optional(out, prev_display_qty());
        out << ", security_id=";
        print::optional(out, security_id());
        out << ", order_details_comp=";
        order_details_comp().print(out);
        out << ", prev_price_hhi_indicator=";
        print::optional(out, prev_price_hhi_indicator());
        out << ", pad7=";
        print::hex(out, pad7().data(), pad7().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderModify& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
