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

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of Trade Summary entries
class IncrementalRefreshTradeSummaryGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshTradeSummaryGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshTradeSummaryGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshTradeSummaryGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    Decimal md_entry_px_ex() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(0))), -9); }

    std::int32_t md_entry_size_short() const { return wire::read_i32_le(at(8)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(12)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(16)); }

    std::int32_t number_of_orders() const { return wire::read_i32_le(at(20)); }

    std::optional<AggressorSide> aggressor_side() const { return wire::nullable_enum<AggressorSide>(wire::read_u8(at(24)), static_cast<std::uint8_t>(255ULL)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(25))); }

    std::optional<std::uint32_t> md_trade_entry_optional() const { return wire::nullable(wire::read_u32_le(at(26)), static_cast<std::uint32_t>(4294967295ULL)); }

    std::span<const std::byte, 2> padding_2() const { return bytes_.subspan(30).template first<2>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshTradeSummaryGroup{";
        out << "md_entry_px_ex=";
        out << md_entry_px_ex();
        out << ", md_entry_size_short=";
        out << md_entry_size_short();
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", number_of_orders=";
        out << number_of_orders();
        out << ", aggressor_side=";
        print::optional(out, aggressor_side());
        out << ", md_update_action=";
        out << md_update_action();
        out << ", md_trade_entry_optional=";
        print::optional(out, md_trade_entry_optional());
        out << ", padding_2=";
        print::hex(out, padding_2().data(), padding_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
