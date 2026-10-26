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
#include "../enums/AlgorithmicTradeIndicator.hpp"
#include "../enums/HhiIndicator.hpp"
#include "../common/Decimal.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class PartialOrderExecution {
  public:
    static constexpr const char* name = "PartialOrderExecution";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PartialOrderExecution(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PartialOrderExecution has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::optional<Side> side() const { return wire::nullable_enum<Side>(wire::read_u8(at(0)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<OrdType> ord_type() const { return wire::nullable_enum<OrdType>(wire::read_u8(at(1)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<AlgorithmicTradeIndicator> algorithmic_trade_indicator() const { return wire::nullable_enum<AlgorithmicTradeIndicator>(wire::read_u8(at(2)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<HhiIndicator> hhi_indicator() const { return wire::nullable_enum<HhiIndicator>(wire::read_i8(at(3)), static_cast<std::int8_t>(0x80LL)); }

    std::optional<std::uint32_t> trd_match_id() const { return wire::nullable(wire::read_u32_le(at(4)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<Decimal> price() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_priority() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<Decimal> last_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(32)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(40)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    void print(std::ostream& out) const {
        out << "PartialOrderExecution{";
        out << "side=";
        print::optional(out, side());
        out << ", ord_type=";
        print::optional(out, ord_type());
        out << ", algorithmic_trade_indicator=";
        print::optional(out, algorithmic_trade_indicator());
        out << ", hhi_indicator=";
        print::optional(out, hhi_indicator());
        out << ", trd_match_id=";
        print::optional(out, trd_match_id());
        out << ", price=";
        print::optional(out, price());
        out << ", trd_reg_ts_time_priority=";
        print::optional_duration(out, trd_reg_ts_time_priority());
        out << ", security_id=";
        print::optional(out, security_id());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", last_px=";
        print::optional(out, last_px());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PartialOrderExecution& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
