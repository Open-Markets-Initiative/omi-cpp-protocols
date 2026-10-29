#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

// Md Instrument Entry Grp Comp
class MdInstrumentEntryGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    MdInstrumentEntryGrpComp() = default;
    MdInstrumentEntryGrpComp(std::optional<Decimal> md_entry_px, std::optional<std::int32_t> md_entry_size, std::optional<MdEntryType> md_entry_type, const std::array<std::byte, 3>& pad3);

    // Md Entry Px:
    std::optional<Decimal> md_entry_px() const;
    void set_md_entry_px(std::optional<Decimal> value);

    // Md Entry Size:
    std::optional<std::int32_t> md_entry_size() const;
    void set_md_entry_size(std::optional<std::int32_t> value);

    // Md Entry Type:
    std::optional<MdEntryType> md_entry_type() const;
    void set_md_entry_type(std::optional<MdEntryType> value);

    // Pad3:
    const std::array<std::byte, 3>& pad3() const;
    std::array<std::byte, 3>& pad3();
    void set_pad3(const std::array<std::byte, 3>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MdInstrumentEntryGrpComp& other) const;
    bool operator!=(const MdInstrumentEntryGrpComp& other) const;

  private:
    std::optional<Decimal> md_entry_px_{};
    std::optional<std::int32_t> md_entry_size_{};
    std::optional<MdEntryType> md_entry_type_{};
    std::array<std::byte, 3> pad3_{};
};

std::ostream& operator<<(std::ostream& out, const MdInstrumentEntryGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v3_0
