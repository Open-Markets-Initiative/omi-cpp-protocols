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
#include "../enums/OpenCloseSettlFlag.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../enums/MdEntryTypeStatistics.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message
class IncrementalRefreshSessionStatisticsLongGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshSessionStatisticsLongGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshSessionStatisticsLongGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshSessionStatisticsLongGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    Decimal md_entry_px_ex() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(0))), -9); }

    std::optional<std::uint64_t> md_entry_size_optional() const { return wire::nullable(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(16)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(20)); }

    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const { return wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(at(24)), static_cast<std::uint8_t>(255ULL)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(25))); }

    MdEntryTypeStatistics md_entry_type_statistics() const { return static_cast<MdEntryTypeStatistics>(wire::read_char(at(26))); }

    std::span<const std::byte, 5> padding_5() const { return bytes_.subspan(27).template first<5>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshSessionStatisticsLongGroup{";
        out << "md_entry_px_ex=";
        out << md_entry_px_ex();
        out << ", md_entry_size_optional=";
        print::optional(out, md_entry_size_optional());
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", open_close_settl_flag=";
        print::optional(out, open_close_settl_flag());
        out << ", md_update_action=";
        out << md_update_action();
        out << ", md_entry_type_statistics=";
        out << md_entry_type_statistics();
        out << ", padding_5=";
        print::hex(out, padding_5().data(), padding_5().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshSessionStatisticsLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
