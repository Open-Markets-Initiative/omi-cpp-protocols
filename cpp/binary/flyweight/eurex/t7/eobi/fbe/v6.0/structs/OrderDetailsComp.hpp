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
#include "../enums/Side.hpp"
#include "../enums/OrdType.hpp"
#include "../common/Decimal.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class OrderDetailsComp {
  public:
    static constexpr const char* name = "OrderDetailsComp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDetailsComp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDetailsComp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::int32_t> display_qty() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<Side> side() const { return wire::nullable_enum<Side>(wire::read_u8(at(12)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<OrdType> ord_type() const { return wire::nullable_enum<OrdType>(wire::read_u8(at(13)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 2> pad2() const { return bytes_.subspan(14).template first<2>(); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    void print(std::ostream& out) const {
        out << "OrderDetailsComp{";
        out << "trd_reg_ts_time_priority=";
        print::optional_duration(out, trd_reg_ts_time_priority());
        out << ", display_qty=";
        print::optional(out, display_qty());
        out << ", side=";
        print::optional(out, side());
        out << ", ord_type=";
        print::optional(out, ord_type());
        out << ", pad2=";
        print::hex(out, pad2().data(), pad2().size());
        out << ", price=";
        print::optional(out, price());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderDetailsComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
