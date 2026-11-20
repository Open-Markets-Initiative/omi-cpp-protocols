// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: bitfields/EventIndicator.cpp
#include "EventIndicator.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

EventIndicator::EventIndicator(std::uint8_t raw) : raw_(raw) {}

bool EventIndicator::poss_resend() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void EventIndicator::set_poss_resend(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool EventIndicator::low_priority() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void EventIndicator::set_low_priority(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

std::uint8_t EventIndicator::raw() const { return raw_; }
void EventIndicator::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t EventIndicator::decode(const std::byte* data, std::size_t length) {
    wire::require("EventIndicator", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t EventIndicator::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("EventIndicator", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t EventIndicator::encoded_size() const {
    return wire_size;
}

void EventIndicator::print(std::ostream& out) const {
    out << "EventIndicator{";
    out << "poss_resend=";
    out << (poss_resend() ? "true" : "false");
    out << ", low_priority=";
    out << (low_priority() ? "true" : "false");
    out << '}';
}

bool EventIndicator::operator==(const EventIndicator& other) const {
    return raw_ == other.raw_;
}

bool EventIndicator::operator!=(const EventIndicator& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const EventIndicator& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
