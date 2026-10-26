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
#include "../enums/MdUpdateAction.hpp"
#include "../enums/MdEntryTypeBook.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class IncrementalRefreshBookGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshBookGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshBookGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshBookGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::optional<Decimal> md_entry_px_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<std::int32_t> md_entry_size_optional() const { return wire::nullable(wire::read_i32_le(at(8)), static_cast<std::int32_t>(2147483647LL)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(12)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(16)); }

    std::optional<std::int32_t> number_of_orders() const { return wire::nullable(wire::read_i32_le(at(20)), static_cast<std::int32_t>(2147483647LL)); }

    std::uint8_t md_price_level() const { return wire::read_u8(at(24)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(25))); }

    MdEntryTypeBook md_entry_type_book() const { return static_cast<MdEntryTypeBook>(wire::read_char(at(26))); }

    std::span<const std::byte, 5> padding_5() const { return bytes_.subspan(27).template first<5>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshBookGroup{";
        out << "md_entry_px_optional=";
        print::optional(out, md_entry_px_optional());
        out << ", md_entry_size_optional=";
        print::optional(out, md_entry_size_optional());
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", number_of_orders=";
        print::optional(out, number_of_orders());
        out << ", md_price_level=";
        out << static_cast<int>(md_price_level());
        out << ", md_update_action=";
        out << md_update_action();
        out << ", md_entry_type_book=";
        out << md_entry_type_book();
        out << ", padding_5=";
        print::hex(out, padding_5().data(), padding_5().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
