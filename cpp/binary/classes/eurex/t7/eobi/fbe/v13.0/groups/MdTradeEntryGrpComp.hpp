#pragma once

#include <array>
#include <cstddef>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// Md Trade Entry Grp Comp
class MdTradeEntryGrpComp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    MdTradeEntryGrpComp() = default;
    MdTradeEntryGrpComp(std::optional<Decimal> md_entry_px, std::optional<Decimal> md_entry_size, std::optional<MdEntryType> md_entry_type, const std::array<std::byte, 7>& pad7);

    // Md Entry Px:
    std::optional<Decimal> md_entry_px() const;
    void set_md_entry_px(std::optional<Decimal> value);

    // Md Entry Size:
    std::optional<Decimal> md_entry_size() const;
    void set_md_entry_size(std::optional<Decimal> value);

    // Md Entry Type:
    std::optional<MdEntryType> md_entry_type() const;
    void set_md_entry_type(std::optional<MdEntryType> value);

    // Pad7:
    const std::array<std::byte, 7>& pad7() const;
    std::array<std::byte, 7>& pad7();
    void set_pad7(const std::array<std::byte, 7>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MdTradeEntryGrpComp& other) const;
    bool operator!=(const MdTradeEntryGrpComp& other) const;

  private:
    std::optional<Decimal> md_entry_px_{};
    std::optional<Decimal> md_entry_size_{};
    std::optional<MdEntryType> md_entry_type_{};
    std::array<std::byte, 7> pad7_{};
};

std::ostream& operator<<(std::ostream& out, const MdTradeEntryGrpComp& value);

} // namespace eurex::t7::eobi::fbe::v13_0
