#include "MatchEventIndicator.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

MatchEventIndicator::MatchEventIndicator(std::uint8_t raw) : raw_(raw) {}

bool MatchEventIndicator::unused_match_event_indicator_0() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void MatchEventIndicator::set_unused_match_event_indicator_0(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool MatchEventIndicator::unused_match_event_indicator_1() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void MatchEventIndicator::set_unused_match_event_indicator_1(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool MatchEventIndicator::unused_match_event_indicator_2() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void MatchEventIndicator::set_unused_match_event_indicator_2(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool MatchEventIndicator::unused_match_event_indicator_3() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void MatchEventIndicator::set_unused_match_event_indicator_3(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool MatchEventIndicator::implied() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void MatchEventIndicator::set_implied(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool MatchEventIndicator::recovery_msg() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void MatchEventIndicator::set_recovery_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool MatchEventIndicator::unused_match_event_indicator_6() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void MatchEventIndicator::set_unused_match_event_indicator_6(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool MatchEventIndicator::end_of_event() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void MatchEventIndicator::set_end_of_event(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t MatchEventIndicator::raw() const { return raw_; }
void MatchEventIndicator::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t MatchEventIndicator::decode(const std::byte* data, std::size_t length) {
    wire::require("MatchEventIndicator", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t MatchEventIndicator::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("MatchEventIndicator", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t MatchEventIndicator::encoded_size() const {
    return wire_size;
}

void MatchEventIndicator::print(std::ostream& out) const {
    out << "MatchEventIndicator{";
    out << "unused_match_event_indicator_0=";
    out << (unused_match_event_indicator_0() ? "true" : "false");
    out << ", unused_match_event_indicator_1=";
    out << (unused_match_event_indicator_1() ? "true" : "false");
    out << ", unused_match_event_indicator_2=";
    out << (unused_match_event_indicator_2() ? "true" : "false");
    out << ", unused_match_event_indicator_3=";
    out << (unused_match_event_indicator_3() ? "true" : "false");
    out << ", implied=";
    out << (implied() ? "true" : "false");
    out << ", recovery_msg=";
    out << (recovery_msg() ? "true" : "false");
    out << ", unused_match_event_indicator_6=";
    out << (unused_match_event_indicator_6() ? "true" : "false");
    out << ", end_of_event=";
    out << (end_of_event() ? "true" : "false");
    out << '}';
}

bool MatchEventIndicator::operator==(const MatchEventIndicator& other) const {
    return raw_ == other.raw_;
}

bool MatchEventIndicator::operator!=(const MatchEventIndicator& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MatchEventIndicator& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
