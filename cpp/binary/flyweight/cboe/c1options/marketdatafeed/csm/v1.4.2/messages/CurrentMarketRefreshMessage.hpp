#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../groups/MdEntry.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The Current Market Refresh message contains a snapshot of the current market information for
// one security along with the quantities and volume types for that particular security.
class CurrentMarketRefreshMessage {
  public:
    static constexpr const char* name = "CurrentMarketRefreshMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CurrentMarketRefreshMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CurrentMarketRefreshMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 15;
    std::size_t encoded_size() const { return md_entry_end(); }

    std::uint32_t class_key() const { return wire::read_u32_be(at(0)); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(4)); }

    SecurityTradingStatus security_trading_status() const { return static_cast<SecurityTradingStatus>(wire::read_u8(at(8))); }

    std::uint8_t price_type() const { return wire::read_u8(at(9)); }

    std::uint32_t appl_seq_num() const { return wire::read_u32_be(at(10)); }

    std::uint8_t no_entries() const { return wire::read_u8(at(14)); }

    view::entries<MdEntry> md_entry() const { return view::entries<MdEntry>{ bytes_.subspan(15), wire::count(no_entries()) }; }

    void print(std::ostream& out) const {
        out << "CurrentMarketRefreshMessage{";
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
        out << ", no_entries=";
        out << static_cast<int>(no_entries());
        out << ", md_entry=";
        print::sequence(out, md_entry());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t md_entry_end() const { return 15 + md_entry().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CurrentMarketRefreshMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
