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

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message.
class IncrementalRefreshBookLongGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshBookLongGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshBookLongGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshBookLongGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::optional<Decimal> md_entry_px_optional_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::uint64_t> md_entry_size_optional() const { return wire::nullable(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(16)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(20)); }

    std::optional<std::int32_t> number_of_orders_optional() const { return wire::nullable(wire::read_i32_le(at(24)), static_cast<std::int32_t>(2147483647LL)); }

    std::uint8_t md_price_level() const { return wire::read_u8(at(28)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(29))); }

    MdEntryTypeBook md_entry_type_book() const { return static_cast<MdEntryTypeBook>(wire::read_char(at(30))); }

    std::span<const std::byte, 1> padding_1() const { return bytes_.subspan(31).template first<1>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshBookLongGroup{";
        out << "md_entry_px_optional_ex=";
        print::optional(out, md_entry_px_optional_ex());
        out << ", md_entry_size_optional=";
        print::optional(out, md_entry_size_optional());
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", number_of_orders_optional=";
        print::optional(out, number_of_orders_optional());
        out << ", md_price_level=";
        out << static_cast<int>(md_price_level());
        out << ", md_update_action=";
        out << md_update_action();
        out << ", md_entry_type_book=";
        out << md_entry_type_book();
        out << ", padding_1=";
        print::hex(out, padding_1().data(), padding_1().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
