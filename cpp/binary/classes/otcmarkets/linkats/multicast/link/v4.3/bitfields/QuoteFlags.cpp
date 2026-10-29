#include "QuoteFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

QuoteFlags::QuoteFlags(std::uint8_t raw) : raw_(raw) {}

bool QuoteFlags::update_side() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void QuoteFlags::set_update_side(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool QuoteFlags::state() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void QuoteFlags::set_state(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool QuoteFlags::ask_unsolicited() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void QuoteFlags::set_ask_unsolicited(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool QuoteFlags::ask_priced() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void QuoteFlags::set_ask_priced(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool QuoteFlags::ask_bid_wanted() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void QuoteFlags::set_ask_bid_wanted(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool QuoteFlags::bid_unsolicited() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void QuoteFlags::set_bid_unsolicited(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool QuoteFlags::bid_priced() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void QuoteFlags::set_bid_priced(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool QuoteFlags::bid_ask_wanted() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void QuoteFlags::set_bid_ask_wanted(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t QuoteFlags::raw() const { return raw_; }
void QuoteFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t QuoteFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("QuoteFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t QuoteFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("QuoteFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t QuoteFlags::encoded_size() const {
    return wire_size;
}

void QuoteFlags::print(std::ostream& out) const {
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

bool QuoteFlags::operator==(const QuoteFlags& other) const {
    return raw_ == other.raw_;
}

bool QuoteFlags::operator!=(const QuoteFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const QuoteFlags& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
