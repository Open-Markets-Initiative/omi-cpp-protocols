#pragma once

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
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// Number of entries in Market Data message
class IncrementalRefreshTradeGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshTradeGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshTradeGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshTradeGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    Decimal md_entry_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(0))), -7); }

    std::int32_t md_entry_size() const { return wire::read_i32_le(at(8)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(12)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(16)); }

    std::optional<std::int32_t> number_of_orders() const { return wire::nullable(wire::read_i32_le(at(20)), static_cast<std::int32_t>(2147483647LL)); }

    std::int32_t trade_id() const { return wire::read_i32_le(at(24)); }

    std::optional<AggressorSide> aggressor_side() const { return wire::nullable_enum<AggressorSide>(wire::read_u8(at(28)), static_cast<std::uint8_t>(255ULL)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(29))); }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(30).template first<2>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshTradeGroup{";
        out << "md_entry_px=";
        out << md_entry_px();
        out << ", md_entry_size=";
        out << md_entry_size();
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", number_of_orders=";
        print::optional(out, number_of_orders());
        out << ", trade_id=";
        out << trade_id();
        out << ", aggressor_side=";
        print::optional(out, aggressor_side());
        out << ", md_update_action=";
        out << md_update_action();
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
