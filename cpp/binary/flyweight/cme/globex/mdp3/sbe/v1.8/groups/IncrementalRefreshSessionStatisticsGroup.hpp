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

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class IncrementalRefreshSessionStatisticsGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshSessionStatisticsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshSessionStatisticsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshSessionStatisticsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    Decimal md_entry_px() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(0))), -7); }

    std::int32_t security_id() const { return wire::read_i32_le(at(8)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(12)); }

    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const { return wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(at(16)), static_cast<std::uint8_t>(255ULL)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(17))); }

    MdEntryTypeStatistics md_entry_type_statistics() const { return static_cast<MdEntryTypeStatistics>(wire::read_char(at(18))); }

    std::optional<std::int32_t> md_entry_size_optional() const { return wire::nullable(wire::read_i32_le(at(19)), static_cast<std::int32_t>(2147483647LL)); }

    std::span<const std::byte, 1> padding_1() const { return bytes_.subspan(23).template first<1>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshSessionStatisticsGroup{";
        out << "md_entry_px=";
        out << md_entry_px();
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
        out << ", md_entry_size_optional=";
        print::optional(out, md_entry_size_optional());
        out << ", padding_1=";
        print::hex(out, padding_1().data(), padding_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshSessionStatisticsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
