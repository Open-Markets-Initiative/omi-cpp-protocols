#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../groups/TickerMdEntry.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// A Ticker message indicates that a trade or cancel has occurred.
class TickerMessage {
  public:
    static constexpr const char* name = "TickerMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TickerMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TickerMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    std::size_t encoded_size() const { return ticker_md_entry_end(); }

    std::uint32_t class_key() const { return wire::read_u32_be(at(0)); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(4)); }

    std::uint8_t price_type() const { return wire::read_u8(at(8)); }

    std::uint8_t no_entries() const { return wire::read_u8(at(9)); }

    view::entries<TickerMdEntry> ticker_md_entry() const { return view::entries<TickerMdEntry>{ bytes_.subspan(10), wire::count(no_entries()) }; }

    void print(std::ostream& out) const {
        out << "TickerMessage{";
        out << "class_key=";
        out << class_key();
        out << ", security_id=";
        out << security_id();
        out << ", price_type=";
        out << static_cast<int>(price_type());
        out << ", no_entries=";
        out << static_cast<int>(no_entries());
        out << ", ticker_md_entry=";
        print::sequence(out, ticker_md_entry());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t ticker_md_entry_end() const { return 10 + ticker_md_entry().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TickerMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
