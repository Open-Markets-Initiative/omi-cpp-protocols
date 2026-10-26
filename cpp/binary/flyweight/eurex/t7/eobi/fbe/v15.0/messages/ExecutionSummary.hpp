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
#include "../enums/AggressorSide.hpp"
#include "../enums/TradeCondition.hpp"
#include "../structs/RemainingOrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class ExecutionSummary {
  public:
    static constexpr const char* name = "ExecutionSummary";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionSummary(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionSummary has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 96;
    static constexpr std::size_t fixed_size = 96;
    std::size_t encoded_size() const { return 96; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> request_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::chrono::nanoseconds> exec_id() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<Decimal> last_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<AggressorSide> aggressor_side() const { return wire::nullable_enum<AggressorSide>(wire::read_u8(at(32)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 1> pad1() const { return bytes_.subspan(33).template first<1>(); }

    std::optional<TradeCondition> trade_condition() const { return wire::nullable_enum<TradeCondition>(wire::read_u16_le(at(34)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<std::uint8_t> trading_hhi_indicator() const { return wire::nullable(wire::read_u8(at(36)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 3> pad3() const { return bytes_.subspan(37).template first<3>(); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(40)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    RemainingOrderDetailsComp remaining_order_details_comp() const { return RemainingOrderDetailsComp{ bytes_.subspan(48) }; }

    std::optional<Decimal> resting_hidden_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(72)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<Decimal> resting_cxl_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(80)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<std::chrono::nanoseconds> aggressor_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(88)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    void print(std::ostream& out) const {
        out << "ExecutionSummary{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", request_time=";
        print::optional_duration(out, request_time());
        out << ", exec_id=";
        print::optional_duration(out, exec_id());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", aggressor_side=";
        print::optional(out, aggressor_side());
        out << ", pad1=";
        print::hex(out, pad1().data(), pad1().size());
        out << ", trade_condition=";
        print::optional(out, trade_condition());
        out << ", trading_hhi_indicator=";
        print::optional(out, trading_hhi_indicator());
        out << ", pad3=";
        print::hex(out, pad3().data(), pad3().size());
        out << ", last_px=";
        print::optional(out, last_px());
        out << ", remaining_order_details_comp=";
        remaining_order_details_comp().print(out);
        out << ", resting_hidden_qty=";
        print::optional(out, resting_hidden_qty());
        out << ", resting_cxl_qty=";
        print::optional(out, resting_cxl_qty());
        out << ", aggressor_time=";
        print::optional_duration(out, aggressor_time());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionSummary& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
