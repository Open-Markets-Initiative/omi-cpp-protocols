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
#include "../enums/MdEntryType.hpp"
#include "../bitfields/SettlPriceType.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of data blocks listed in the Incremental message
class SnapshotFullRefreshTcpGroup {
  public:
    static constexpr const char* name = "SnapshotFullRefreshTcpGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshTcpGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshTcpGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    static constexpr std::size_t fixed_size = 26;
    std::size_t encoded_size() const { return 26; }

    std::optional<Decimal> md_entry_px_optional_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::int32_t> md_entry_size_short_optional() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::int32_t> tradeable_size() const { return wire::nullable(wire::read_i32_le(at(12)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::int32_t> number_of_orders_optional() const { return wire::nullable(wire::read_i32_le(at(16)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::int8_t> md_price_level_optional() const { return wire::nullable(wire::read_i8(at(20)), static_cast<std::int8_t>(127LL)); }

    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const { return wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(at(21)), static_cast<std::uint8_t>(255ULL)); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(22))); }

    std::optional<std::uint16_t> trading_reference_date() const { return wire::nullable(wire::read_u16_le(at(23)), static_cast<std::uint16_t>(65535ULL)); }

    SettlPriceType settl_price_type() const { return SettlPriceType{ bytes_.subspan(25) }; }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshTcpGroup{";
        out << "md_entry_px_optional_ex=";
        print::optional(out, md_entry_px_optional_ex());
        out << ", md_entry_size_short_optional=";
        print::optional(out, md_entry_size_short_optional());
        out << ", tradeable_size=";
        print::optional(out, tradeable_size());
        out << ", number_of_orders_optional=";
        print::optional(out, number_of_orders_optional());
        out << ", md_price_level_optional=";
        print::optional(out, md_price_level_optional());
        out << ", open_close_settl_flag=";
        print::optional(out, open_close_settl_flag());
        out << ", md_entry_type=";
        out << md_entry_type();
        out << ", trading_reference_date=";
        print::optional(out, trading_reference_date());
        out << ", settl_price_type=";
        settl_price_type().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshTcpGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
