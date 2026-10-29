#include "TradeStatus.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

TradeStatus::TradeStatus(std::uint8_t raw) : raw_(raw) {}

bool TradeStatus::irregular() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void TradeStatus::set_irregular(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

std::uint8_t TradeStatus::raw() const { return raw_; }
void TradeStatus::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t TradeStatus::decode(const std::byte* data, std::size_t length) {
    wire::require("TradeStatus", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t TradeStatus::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("TradeStatus", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t TradeStatus::encoded_size() const {
    return wire_size;
}

void TradeStatus::print(std::ostream& out) const {
    out << "TradeStatus{";
    out << "irregular=";
    out << (irregular() ? "true" : "false");
    out << '}';
}

bool TradeStatus::operator==(const TradeStatus& other) const {
    return raw_ == other.raw_;
}

bool TradeStatus::operator!=(const TradeStatus& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TradeStatus& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
