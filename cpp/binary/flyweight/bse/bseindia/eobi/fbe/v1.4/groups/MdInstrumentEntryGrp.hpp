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
#include "../enums/MdEntryType.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Instrument trade statistics repeated NoMDEntries times in the Instrument Summary Message.
// The group is not cut off by design.
class MdInstrumentEntryGrp {
  public:
    static constexpr const char* name = "MdInstrumentEntryGrp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MdInstrumentEntryGrp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdInstrumentEntryGrp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::optional<Decimal> md_entry_px() const { return wire::nullable_decimal(wire::read_i64_le(at(0)), static_cast<std::int64_t>(0x8000000000000000LL), -6); }

    std::optional<std::int64_t> md_entry_size() const { return wire::nullable(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_u8(at(16))); }

    std::span<const std::byte, 7> pad_7() const { return bytes_.subspan(17).template first<7>(); }

    void print(std::ostream& out) const {
        out << "MdInstrumentEntryGrp{";
        out << "md_entry_px=";
        print::optional(out, md_entry_px());
        out << ", md_entry_size=";
        print::optional(out, md_entry_size());
        out << ", md_entry_type=";
        out << md_entry_type();
        out << ", pad_7=";
        print::hex(out, pad_7().data(), pad_7().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MdInstrumentEntryGrp& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
