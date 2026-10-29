#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// MDEntry indicating market data
class RecapUpdateMdEntry {
  public:
    static constexpr const char* name = "RecapUpdateMdEntry";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecapUpdateMdEntry(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecapUpdateMdEntry has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(0))); }

    MdEntryPx md_entry_px() const { return MdEntryPx{ bytes_.subspan(1) }; }

    std::uint32_t md_entry_size() const { return wire::read_u32_be(at(6)); }

    void print(std::ostream& out) const {
        out << "RecapUpdateMdEntry{";
        out << "md_entry_type=";
        out << md_entry_type();
        out << ", md_entry_px=";
        md_entry_px().print(out);
        out << ", md_entry_size=";
        out << md_entry_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecapUpdateMdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
