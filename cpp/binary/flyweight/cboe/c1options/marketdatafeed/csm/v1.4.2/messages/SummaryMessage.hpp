#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/NetChgPrevDay.hpp"
#include "../structs/UnderlyingPx.hpp"
#include "../groups/SummaryMdEntry.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Summary messages contain the end of session market data for each product.
class SummaryMessage {
  public:
    static constexpr const char* name = "SummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    std::size_t encoded_size() const { return summary_md_entry_end(); }

    std::uint32_t class_key() const { return wire::read_u32_be(at(0)); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(4)); }

    std::uint8_t price_type() const { return wire::read_u8(at(8)); }

    std::uint32_t trade_volume() const { return wire::read_u32_be(at(9)); }

    std::uint32_t open_interest() const { return wire::read_u32_be(at(13)); }

    NetChgPrevDay net_chg_prev_day() const { return NetChgPrevDay{ bytes_.subspan(17) }; }

    UnderlyingPx underlying_px() const { return UnderlyingPx{ bytes_.subspan(22) }; }

    std::uint8_t no_entries() const { return wire::read_u8(at(27)); }

    view::entries<SummaryMdEntry> summary_md_entry() const { return view::entries<SummaryMdEntry>{ bytes_.subspan(28), wire::count(no_entries()) }; }

    void print(std::ostream& out) const {
        out << "SummaryMessage{";
        out << "class_key=";
        out << class_key();
        out << ", security_id=";
        out << security_id();
        out << ", price_type=";
        out << static_cast<int>(price_type());
        out << ", trade_volume=";
        out << trade_volume();
        out << ", open_interest=";
        out << open_interest();
        out << ", net_chg_prev_day=";
        net_chg_prev_day().print(out);
        out << ", underlying_px=";
        underlying_px().print(out);
        out << ", no_entries=";
        out << static_cast<int>(no_entries());
        out << ", summary_md_entry=";
        print::sequence(out, summary_md_entry());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t summary_md_entry_end() const { return 28 + summary_md_entry().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
