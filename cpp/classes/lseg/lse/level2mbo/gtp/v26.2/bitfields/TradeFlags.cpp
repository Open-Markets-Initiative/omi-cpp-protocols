#include "TradeFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

TradeFlags::TradeFlags(std::uint8_t raw) : raw_(raw) {}

bool TradeFlags::trade_cancellation() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void TradeFlags::set_trade_cancellation(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool TradeFlags::trade_correction() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void TradeFlags::set_trade_correction(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

std::uint8_t TradeFlags::raw() const { return raw_; }
void TradeFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t TradeFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("TradeFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t TradeFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("TradeFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t TradeFlags::encoded_size() const {
    return wire_size;
}

void TradeFlags::print(std::ostream& out) const {
    out << "TradeFlags{";
    out << "trade_cancellation=";
    out << (trade_cancellation() ? "true" : "false");
    out << ", trade_correction=";
    out << (trade_correction() ? "true" : "false");
    out << '}';
}

bool TradeFlags::operator==(const TradeFlags& other) const {
    return raw_ == other.raw_;
}

bool TradeFlags::operator!=(const TradeFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TradeFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
