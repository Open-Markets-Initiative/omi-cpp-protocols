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
#include "../bitfields/SettlPriceType.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../enums/MdEntryTypeDailyStatistics.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class IncrementalRefreshDailyStatisticsGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshDailyStatisticsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshDailyStatisticsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshDailyStatisticsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::optional<Decimal> md_entry_px_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<std::int32_t> md_entry_size_optional() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(2147483647LL)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(12)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(16)); }

    std::optional<std::uint16_t> trading_reference_date() const { return wire::nullable(wire::read_u16_le(at(20)), static_cast<std::uint16_t>(65535ULL)); }

    SettlPriceType settl_price_type() const { return SettlPriceType{ bytes_.subspan(22) }; }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(23))); }

    MdEntryTypeDailyStatistics md_entry_type_daily_statistics() const { return static_cast<MdEntryTypeDailyStatistics>(wire::read_char(at(24))); }

    std::span<const std::byte, 7> padding_7() const { return bytes_.subspan(25).template first<7>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshDailyStatisticsGroup{";
        out << "md_entry_px_optional=";
        print::optional(out, md_entry_px_optional());
        out << ", md_entry_size_optional=";
        print::optional(out, md_entry_size_optional());
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", trading_reference_date=";
        print::optional(out, trading_reference_date());
        out << ", settl_price_type=";
        settl_price_type().print(out);
        out << ", md_update_action=";
        out << md_update_action();
        out << ", md_entry_type_daily_statistics=";
        out << md_entry_type_daily_statistics();
        out << ", padding_7=";
        print::hex(out, padding_7().data(), padding_7().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshDailyStatisticsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
