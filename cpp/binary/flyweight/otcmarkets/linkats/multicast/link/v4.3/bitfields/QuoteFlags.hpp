#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Quote Information
class QuoteFlags {
  public:
    static constexpr const char* name = "QuoteFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool update_side() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool state() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    bool ask_unsolicited() const { return (raw() & static_cast<std::uint8_t>(0x4)) != 0; }

    bool ask_priced() const { return (raw() & static_cast<std::uint8_t>(0x8)) != 0; }

    bool ask_bid_wanted() const { return (raw() & static_cast<std::uint8_t>(0x10)) != 0; }

    bool bid_unsolicited() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool bid_priced() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool bid_ask_wanted() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "QuoteFlags{";
        out << "update_side=";
        out << (update_side() ? "true" : "false");
        out << ", state=";
        out << (state() ? "true" : "false");
        out << ", ask_unsolicited=";
        out << (ask_unsolicited() ? "true" : "false");
        out << ", ask_priced=";
        out << (ask_priced() ? "true" : "false");
        out << ", ask_bid_wanted=";
        out << (ask_bid_wanted() ? "true" : "false");
        out << ", bid_unsolicited=";
        out << (bid_unsolicited() ? "true" : "false");
        out << ", bid_priced=";
        out << (bid_priced() ? "true" : "false");
        out << ", bid_ask_wanted=";
        out << (bid_ask_wanted() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteFlags& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
