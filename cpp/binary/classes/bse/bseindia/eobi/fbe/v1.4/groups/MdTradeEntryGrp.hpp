#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/MdEntryType.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Trade statistics repeated NoMDEntries times in the Trade Reversal Message.
class MdTradeEntryGrp {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    MdTradeEntryGrp() = default;
    MdTradeEntryGrp(std::optional<Decimal> md_entry_px, std::optional<std::int64_t> md_entry_size, MdEntryType md_entry_type, const std::array<std::byte, 7>& pad_7);

    // Md Entry Px: Price.
    std::optional<Decimal> md_entry_px() const;
    void set_md_entry_px(std::optional<Decimal> value);

    // Md Entry Size: Quantity.
    std::optional<std::int64_t> md_entry_size() const;
    void set_md_entry_size(std::optional<std::int64_t> value);

    // Md Entry Type: Type of market data entry.
    MdEntryType md_entry_type() const;
    void set_md_entry_type(MdEntryType value);

    // Pad 7: not used
    const std::array<std::byte, 7>& pad_7() const;
    std::array<std::byte, 7>& pad_7();
    void set_pad_7(const std::array<std::byte, 7>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MdTradeEntryGrp& other) const;
    bool operator!=(const MdTradeEntryGrp& other) const;

  private:
    std::optional<Decimal> md_entry_px_{};
    std::optional<std::int64_t> md_entry_size_{};
    MdEntryType md_entry_type_{};
    std::array<std::byte, 7> pad_7_{};
};

std::ostream& operator<<(std::ostream& out, const MdTradeEntryGrp& value);

} // namespace bse::bseindia::eobi::fbe::v1_4
