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

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message
class SnapshotfullRefreshTcpLongGroup {
  public:
    static constexpr const char* name = "SnapshotfullRefreshTcpLongGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotfullRefreshTcpLongGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotfullRefreshTcpLongGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 23;
    static constexpr std::size_t fixed_size = 23;
    std::size_t encoded_size() const { return 23; }

    std::optional<Decimal> md_entry_px_optional_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::uint64_t> md_entry_size_optional() const { return wire::nullable(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::int32_t> number_of_orders_optional() const { return wire::nullable(wire::read_i32_le(at(16)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::uint8_t> md_price_level_unsigned_optional() const { return wire::nullable(wire::read_u8(at(20)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<OpenCloseSettlFlag> open_close_settl_flag() const { return wire::nullable_enum<OpenCloseSettlFlag>(wire::read_u8(at(21)), static_cast<std::uint8_t>(255ULL)); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(22))); }

    void print(std::ostream& out) const {
        out << "SnapshotfullRefreshTcpLongGroup{";
        out << "md_entry_px_optional_ex=";
        print::optional(out, md_entry_px_optional_ex());
        out << ", md_entry_size_optional=";
        print::optional(out, md_entry_size_optional());
        out << ", number_of_orders_optional=";
        print::optional(out, number_of_orders_optional());
        out << ", md_price_level_unsigned_optional=";
        print::optional(out, md_price_level_unsigned_optional());
        out << ", open_close_settl_flag=";
        print::optional(out, open_close_settl_flag());
        out << ", md_entry_type=";
        out << md_entry_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotfullRefreshTcpLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
