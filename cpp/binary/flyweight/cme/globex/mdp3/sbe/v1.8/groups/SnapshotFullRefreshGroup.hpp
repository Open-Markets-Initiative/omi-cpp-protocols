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
#include "../bitfields/SettlPriceType.hpp"
#include "../enums/MdEntryType.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class SnapshotFullRefreshGroup {
  public:
    static constexpr const char* name = "SnapshotFullRefreshGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    std::optional<Decimal> md_entry_px_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<std::int32_t> md_entry_size_optional() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::int32_t> number_of_orders() const { return wire::nullable(wire::read_i32_le(at(12)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::int8_t> md_price_level_optional() const { return wire::nullable(wire::read_i8(at(16)), static_cast<std::int8_t>(127LL)); }

    std::optional<std::uint16_t> trading_reference_date() const { return wire::nullable(wire::read_u16_le(at(17)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const { return wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(at(19)), static_cast<std::uint8_t>(255ULL)); }

    SettlPriceType settl_price_type() const { return SettlPriceType{ bytes_.subspan(20) }; }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(21))); }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshGroup{";
        out << "md_entry_px_optional=";
        print::optional(out, md_entry_px_optional());
        out << ", md_entry_size_optional=";
        print::optional(out, md_entry_size_optional());
        out << ", number_of_orders=";
        print::optional(out, number_of_orders());
        out << ", md_price_level_optional=";
        print::optional(out, md_price_level_optional());
        out << ", trading_reference_date=";
        print::optional(out, trading_reference_date());
        out << ", open_close_settl_flag=";
        print::optional(out, open_close_settl_flag());
        out << ", settl_price_type=";
        settl_price_type().print(out);
        out << ", md_entry_type=";
        out << md_entry_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
