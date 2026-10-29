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
#include "../enums/AggressorSide.hpp"
#include "../enums/TradeCondition.hpp"
#include "../common/Decimal.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class ExecutionSummary {
  public:
    static constexpr const char* name = "ExecutionSummary";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionSummary(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionSummary has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> aggressor_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::chrono::nanoseconds> request_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::chrono::nanoseconds> exec_id() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::int32_t> last_qty() const { return wire::nullable(wire::read_i32_le(at(32)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<AggressorSide> aggressor_side() const { return wire::nullable_enum<AggressorSide>(wire::read_u8(at(36)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<TradeCondition> trade_condition() const { return wire::nullable_enum<TradeCondition>(wire::read_u8(at(37)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 2> pad2() const { return bytes_.subspan(38).template first<2>(); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(40)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::int32_t> resting_hidden_qty() const { return wire::nullable(wire::read_i32_le(at(48)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<std::int32_t> resting_cxl_qty() const { return wire::nullable(wire::read_i32_le(at(52)), static_cast<std::int32_t>(0x80000000LL)); }

    void print(std::ostream& out) const {
        out << "ExecutionSummary{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", aggressor_time=";
        print::optional_duration(out, aggressor_time());
        out << ", request_time=";
        print::optional_duration(out, request_time());
        out << ", exec_id=";
        print::optional_duration(out, exec_id());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", aggressor_side=";
        print::optional(out, aggressor_side());
        out << ", trade_condition=";
        print::optional(out, trade_condition());
        out << ", pad2=";
        print::hex(out, pad2().data(), pad2().size());
        out << ", last_px=";
        print::optional(out, last_px());
        out << ", resting_hidden_qty=";
        print::optional(out, resting_hidden_qty());
        out << ", resting_cxl_qty=";
        print::optional(out, resting_cxl_qty());
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

} // namespace eurex::t7::eobi::fbe::v6_0
