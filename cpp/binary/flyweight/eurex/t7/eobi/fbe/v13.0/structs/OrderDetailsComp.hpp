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
#include "../enums/Side.hpp"
#include "../enums/OrdType.hpp"
#include "../enums/HhiIndicator.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class OrderDetailsComp {
  public:
    static constexpr const char* name = "OrderDetailsComp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDetailsComp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDetailsComp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<Decimal> display_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<Side> side() const { return wire::nullable_enum<Side>(wire::read_u8(at(16)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<OrdType> ord_type() const { return wire::nullable_enum<OrdType>(wire::read_u8(at(17)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<HhiIndicator> hhi_indicator() const { return wire::nullable_enum<HhiIndicator>(wire::read_i8(at(18)), static_cast<std::int8_t>(0x80LL)); }

    std::span<const std::byte, 5> pad5() const { return bytes_.subspan(19).template first<5>(); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

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
        out << ", hhi_indicator=";
        print::optional(out, hhi_indicator());
        out << ", pad5=";
        print::hex(out, pad5().data(), pad5().size());
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

} // namespace eurex::t7::eobi::fbe::v13_0
