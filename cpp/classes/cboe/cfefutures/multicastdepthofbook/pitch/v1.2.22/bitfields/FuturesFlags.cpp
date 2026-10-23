#include "FuturesFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

FuturesFlags::FuturesFlags(std::uint8_t raw) : raw_(raw) {}

bool FuturesFlags::variance() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void FuturesFlags::set_variance(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

std::uint8_t FuturesFlags::raw() const { return raw_; }
void FuturesFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t FuturesFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("FuturesFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t FuturesFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("FuturesFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t FuturesFlags::encoded_size() const {
    return wire_size;
}

void FuturesFlags::print(std::ostream& out) const {
    out << "FuturesFlags{";
    out << "variance=";
    out << (variance() ? "true" : "false");
    out << '}';
}

bool FuturesFlags::operator==(const FuturesFlags& other) const {
    return raw_ == other.raw_;
}

bool FuturesFlags::operator!=(const FuturesFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FuturesFlags& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
