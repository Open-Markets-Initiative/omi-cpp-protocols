#include "SummaryFlags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

SummaryFlags::SummaryFlags(std::uint8_t raw) : raw_(raw) {}

bool SummaryFlags::high_price_valid() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void SummaryFlags::set_high_price_valid(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool SummaryFlags::high_price_is_bid() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void SummaryFlags::set_high_price_is_bid(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool SummaryFlags::low_price_valid() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void SummaryFlags::set_low_price_valid(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool SummaryFlags::low_price_is_offer() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void SummaryFlags::set_low_price_is_offer(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool SummaryFlags::open_close_valid() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void SummaryFlags::set_open_close_valid(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

std::uint8_t SummaryFlags::raw() const { return raw_; }
void SummaryFlags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t SummaryFlags::decode(const std::byte* data, std::size_t length) {
    wire::require("SummaryFlags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t SummaryFlags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("SummaryFlags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t SummaryFlags::encoded_size() const {
    return wire_size;
}

void SummaryFlags::print(std::ostream& out) const {
    out << "SummaryFlags{";
    out << "high_price_valid=";
    out << (high_price_valid() ? "true" : "false");
    out << ", high_price_is_bid=";
    out << (high_price_is_bid() ? "true" : "false");
    out << ", low_price_valid=";
    out << (low_price_valid() ? "true" : "false");
    out << ", low_price_is_offer=";
    out << (low_price_is_offer() ? "true" : "false");
    out << ", open_close_valid=";
    out << (open_close_valid() ? "true" : "false");
    out << '}';
}

bool SummaryFlags::operator==(const SummaryFlags& other) const {
    return raw_ == other.raw_;
}

bool SummaryFlags::operator!=(const SummaryFlags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SummaryFlags& value) {
    value.print(out);
    return out;
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
