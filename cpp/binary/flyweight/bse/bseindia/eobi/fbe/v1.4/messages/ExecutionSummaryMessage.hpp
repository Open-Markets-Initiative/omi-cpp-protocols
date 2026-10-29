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

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published whenever an incoming order is executed, carrying information on the execution of
// that incoming order.
class ExecutionSummaryMessage {
  public:
    static constexpr const char* name = "ExecutionSummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ExecutionSummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ExecutionSummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    std::optional<std::chrono::nanoseconds> aggressor_timestamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::chrono::nanoseconds exec_id() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(16)))); }

    std::int64_t last_qty() const { return wire::read_i64_le(at(24)); }

    AggressorSide aggressor_side() const { return static_cast<AggressorSide>(wire::read_u8(at(32))); }

    std::optional<TradeCondition> trade_condition() const { return wire::nullable_enum<TradeCondition>(wire::read_u8(at(33)), static_cast<std::uint8_t>(255ULL)); }

    std::span<const std::byte, 6> pad_6() const { return bytes_.subspan(34).template first<6>(); }

    Decimal last_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(40))), -6); }

    std::optional<std::int64_t> resting_hidden_qty() const { return wire::nullable(wire::read_i64_le(at(48)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    void print(std::ostream& out) const {
        out << "ExecutionSummaryMessage{";
        out << "security_id=";
        out << security_id();
        out << ", aggressor_timestamp=";
        print::optional_duration(out, aggressor_timestamp());
        out << ", exec_id=";
        out << exec_id().count();
        out << ", last_qty=";
        out << last_qty();
        out << ", aggressor_side=";
        out << aggressor_side();
        out << ", trade_condition=";
        print::optional(out, trade_condition());
        out << ", pad_6=";
        print::hex(out, pad_6().data(), pad_6().size());
        out << ", last_px=";
        out << last_px();
        out << ", resting_hidden_qty=";
        print::optional(out, resting_hidden_qty());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ExecutionSummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
