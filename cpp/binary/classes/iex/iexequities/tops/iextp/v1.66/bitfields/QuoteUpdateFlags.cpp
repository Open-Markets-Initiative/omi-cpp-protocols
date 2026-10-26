#include "QuoteUpdateFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

QuoteUpdateFlags::QuoteUpdateFlags(std::uint8_t raw) : raw_(raw) {}

bool QuoteUpdateFlags::market_session() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void QuoteUpdateFlags::set_market_session(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool QuoteUpdateFlags::symbol_availability() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void QuoteUpdateFlags::set_symbol_availability(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t QuoteUpdateFlags::raw() const { return raw_; }
void QuoteUpdateFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t QuoteUpdateFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("QuoteUpdateFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t QuoteUpdateFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("QuoteUpdateFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t QuoteUpdateFlags::encoded_size() const {
    return wire_size;
}

void QuoteUpdateFlags::print(std::ostream& out) const {
    out << "QuoteUpdateFlags{";
    out << "market_session=";
    out << (market_session() ? "true" : "false");
    out << ", symbol_availability=";
    out << (symbol_availability() ? "true" : "false");
    out << '}';
}

bool QuoteUpdateFlags::operator==(const QuoteUpdateFlags& other) const {
    return raw_ == other.raw_;
}

bool QuoteUpdateFlags::operator!=(const QuoteUpdateFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const QuoteUpdateFlags& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::iextp::v1_66
