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
class IncrementalRefreshTradeSummaryLongGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshTradeSummaryLongGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshTradeSummaryLongGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshTradeSummaryLongGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    Decimal md_entry_px_ex() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(0))), -9); }

    std::uint64_t md_entry_size() const { return wire::read_u64_le(at(8)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(16)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(20)); }

    std::int32_t number_of_orders() const { return wire::read_i32_le(at(24)); }

    std::uint32_t md_trade_entry() const { return wire::read_u32_le(at(28)); }

    std::optional<AggressorSide> aggressor_side() const { return wire::nullable_enum<AggressorSide>(wire::read_u8(at(32)), static_cast<std::uint8_t>(255ULL)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(33))); }

    std::span<const std::byte, 6> padding_6() const { return bytes_.subspan(34).template first<6>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshTradeSummaryLongGroup{";
        out << "md_entry_px_ex=";
        out << md_entry_px_ex();
        out << ", md_entry_size=";
        out << md_entry_size();
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", number_of_orders=";
        out << number_of_orders();
        out << ", md_trade_entry=";
        out << md_trade_entry();
        out << ", aggressor_side=";
        print::optional(out, aggressor_side());
        out << ", md_update_action=";
        out << md_update_action();
        out << ", padding_6=";
        print::hex(out, padding_6().data(), padding_6().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
