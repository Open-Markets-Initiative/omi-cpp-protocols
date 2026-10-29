#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../structs/PrevClosePx.hpp"
#include "../groups/MdEntry.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The Market Data Refresh message contains a snapshot / refresh of the Current Market and
// Recap information (Last Sale, Last Sale Size, Open, High, Low, Previous Close Price) for one
// product.
class MarketDataRefreshMessage {
  public:
    static constexpr const char* name = "MarketDataRefreshMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketDataRefreshMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketDataRefreshMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    std::size_t encoded_size() const { return md_entry_end(); }

    std::uint32_t class_key() const { return wire::read_u32_be(at(0)); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(4)); }

    SecurityTradingStatus security_trading_status() const { return static_cast<SecurityTradingStatus>(wire::read_u8(at(8))); }

    std::uint8_t price_type() const { return wire::read_u8(at(9)); }

    std::uint32_t appl_seq_num() const { return wire::read_u32_be(at(10)); }

    PrevClosePx prev_close_px() const { return PrevClosePx{ bytes_.subspan(14) }; }

    std::uint32_t trade_volume() const { return wire::read_u32_be(at(19)); }

    std::uint8_t no_entries() const { return wire::read_u8(at(23)); }

    view::entries<MdEntry> md_entry() const { return view::entries<MdEntry>{ bytes_.subspan(24), wire::count(no_entries()) }; }

    void print(std::ostream& out) const {
        out << "MarketDataRefreshMessage{";
        out << "class_key=";
        out << class_key();
        out << ", security_id=";
        out << security_id();
        out << ", security_trading_status=";
        out << security_trading_status();
        out << ", price_type=";
        out << static_cast<int>(price_type());
        out << ", appl_seq_num=";
        out << appl_seq_num();
        out << ", prev_close_px=";
        prev_close_px().print(out);
        out << ", trade_volume=";
        out << trade_volume();
        out << ", no_entries=";
        out << static_cast<int>(no_entries());
        out << ", md_entry=";
        print::sequence(out, md_entry());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t md_entry_end() const { return 24 + md_entry().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketDataRefreshMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
