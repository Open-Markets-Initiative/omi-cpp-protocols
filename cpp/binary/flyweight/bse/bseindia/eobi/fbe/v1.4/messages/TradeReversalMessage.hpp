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
#include "../groups/MdTradeEntryGrp.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published when a trade is reversed.
class TradeReversalMessage {
  public:
    static constexpr const char* name = "TradeReversalMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeReversalMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeReversalMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 416;
    static constexpr std::size_t fixed_size = 416;
    std::size_t encoded_size() const { return 416; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    std::uint32_t trd_match_id() const { return wire::read_u32_le(at(16)); }

    std::span<const std::byte, 4> pad_4() const { return bytes_.subspan(20).template first<4>(); }

    std::int64_t last_qty() const { return wire::read_i64_le(at(24)); }

    Decimal last_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(32))), -6); }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(40)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::uint8_t no_md_entries() const { return wire::read_u8(at(48)); }

    std::span<const std::byte, 7> pad_7() const { return bytes_.subspan(49).template first<7>(); }

    view::entries<MdTradeEntryGrp> md_trade_entry_grp() const { return view::entries<MdTradeEntryGrp>{ bytes_.subspan(56), 15 }; }

    void print(std::ostream& out) const {
        out << "TradeReversalMessage{";
        out << "security_id=";
        out << security_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", trd_match_id=";
        out << trd_match_id();
        out << ", pad_4=";
        print::hex(out, pad_4().data(), pad_4().size());
        out << ", last_qty=";
        out << last_qty();
        out << ", last_px=";
        out << last_px();
        out << ", trd_reg_ts_execution_time=";
        print::optional_duration(out, trd_reg_ts_execution_time());
        out << ", no_md_entries=";
        out << static_cast<int>(no_md_entries());
        out << ", pad_7=";
        print::hex(out, pad_7().data(), pad_7().size());
        out << ", md_trade_entry_grp=";
        print::sequence(out, md_trade_entry_grp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeReversalMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
