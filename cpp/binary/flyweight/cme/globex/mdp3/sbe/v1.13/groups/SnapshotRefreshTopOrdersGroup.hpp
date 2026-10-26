#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdEntryTypeBook.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of data blocks following
class SnapshotRefreshTopOrdersGroup {
  public:
    static constexpr const char* name = "SnapshotRefreshTopOrdersGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotRefreshTopOrdersGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotRefreshTopOrdersGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::uint64_t order_id() const { return wire::read_u64_le(at(0)); }

    std::uint64_t md_order_priority() const { return wire::read_u64_le(at(8)); }

    Decimal md_entry_px_ex() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(16))), -9); }

    std::int32_t md_display_qty() const { return wire::read_i32_le(at(24)); }

    MdEntryTypeBook md_entry_type_book() const { return static_cast<MdEntryTypeBook>(wire::read_char(at(28))); }

    void print(std::ostream& out) const {
        out << "SnapshotRefreshTopOrdersGroup{";
        out << "order_id=";
        out << order_id();
        out << ", md_order_priority=";
        out << md_order_priority();
        out << ", md_entry_px_ex=";
        out << md_entry_px_ex();
        out << ", md_display_qty=";
        out << md_display_qty();
        out << ", md_entry_type_book=";
        out << md_entry_type_book();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotRefreshTopOrdersGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
