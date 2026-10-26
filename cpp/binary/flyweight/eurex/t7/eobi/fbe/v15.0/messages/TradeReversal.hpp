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
#include "../enums/TradeCondition.hpp"
#include "../enums/MdOriginType.hpp"
#include "../groups/MdTradeEntryGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class TradeReversal {
  public:
    static constexpr const char* name = "TradeReversal";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeReversal(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeReversal has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 480;
    static constexpr std::size_t fixed_size = 480;
    std::size_t encoded_size() const { return 480; }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<Decimal> last_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -4); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(24)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(32)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::uint32_t> trd_match_id() const { return wire::nullable(wire::read_u32_le(at(40)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::optional<TradeCondition> trade_condition() const { return wire::nullable_enum<TradeCondition>(wire::read_u16_le(at(44)), static_cast<std::uint16_t>(0xFFFFULL)); }

    std::optional<MdOriginType> md_origin_type() const { return wire::nullable_enum<MdOriginType>(wire::read_u8(at(46)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<std::uint8_t> no_md_entries() const { return wire::nullable(wire::read_u8(at(47)), static_cast<std::uint8_t>(0xFFULL)); }

    view::entries<MdTradeEntryGrpComp> md_trade_entry_grp_comp() const { return view::entries<MdTradeEntryGrpComp>{ bytes_.subspan(48), 18 }; }

    void print(std::ostream& out) const {
        out << "TradeReversal{";
        out << "security_id=";
        print::optional(out, security_id());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", last_px=";
        print::optional(out, last_px());
        out << ", trd_reg_ts_execution_time=";
        print::optional_duration(out, trd_reg_ts_execution_time());
        out << ", trd_match_id=";
        print::optional(out, trd_match_id());
        out << ", trade_condition=";
        print::optional(out, trade_condition());
        out << ", md_origin_type=";
        print::optional(out, md_origin_type());
        out << ", no_md_entries=";
        print::optional(out, no_md_entries());
        out << ", md_trade_entry_grp_comp=";
        print::sequence(out, md_trade_entry_grp_comp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeReversal& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
