#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// MDEntry indicating market data
class RecapUpdateMdEntry {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 10;

    RecapUpdateMdEntry() = default;
    RecapUpdateMdEntry(MdEntryType md_entry_type, const MdEntryPx& md_entry_px, std::uint32_t md_entry_size);

    // Md Entry Type: Side of book for this entry.
    MdEntryType md_entry_type() const;
    void set_md_entry_type(MdEntryType value);

    // Md Entry Px:
    const MdEntryPx& md_entry_px() const;
    MdEntryPx& md_entry_px();
    void set_md_entry_px(const MdEntryPx& value);

    // Md Entry Size: Quote Quantity
    std::uint32_t md_entry_size() const;
    void set_md_entry_size(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RecapUpdateMdEntry& other) const;
    bool operator!=(const RecapUpdateMdEntry& other) const;

  private:
    MdEntryType md_entry_type_{};
    MdEntryPx md_entry_px_{};
    std::uint32_t md_entry_size_{};
};

std::ostream& operator<<(std::ostream& out, const RecapUpdateMdEntry& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
