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
#include "../structs/TradeCondition.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Volume Entry for this price level.
class TickerMdEntry {
  public:
    static constexpr const char* name = "TickerMdEntry";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TickerMdEntry(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TickerMdEntry has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    std::size_t encoded_size() const { return trade_condition_end(); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(0))); }

    MdEntryPx md_entry_px() const { return MdEntryPx{ bytes_.subspan(1) }; }

    std::uint32_t md_entry_size() const { return wire::read_u32_be(at(6)); }

    TradeCondition trade_condition() const { return TradeCondition{ bytes_.subspan(10) }; }

    void print(std::ostream& out) const {
        out << "TickerMdEntry{";
        out << "md_entry_type=";
        out << md_entry_type();
        out << ", md_entry_px=";
        md_entry_px().print(out);
        out << ", md_entry_size=";
        out << md_entry_size();
        out << ", trade_condition=";
        trade_condition().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t trade_condition_end() const { return 10 + trade_condition().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TickerMdEntry& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
