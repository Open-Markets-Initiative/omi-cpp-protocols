#include "MatchEventIndicatorOptional.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

MatchEventIndicatorOptional::MatchEventIndicatorOptional(std::uint8_t raw) : raw_(raw) {}

bool MatchEventIndicatorOptional::unused_match_event_indicator_0() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void MatchEventIndicatorOptional::set_unused_match_event_indicator_0(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool MatchEventIndicatorOptional::unused_match_event_indicator_1() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void MatchEventIndicatorOptional::set_unused_match_event_indicator_1(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool MatchEventIndicatorOptional::unused_match_event_indicator_2() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void MatchEventIndicatorOptional::set_unused_match_event_indicator_2(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool MatchEventIndicatorOptional::unused_match_event_indicator_3() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void MatchEventIndicatorOptional::set_unused_match_event_indicator_3(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool MatchEventIndicatorOptional::implied() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void MatchEventIndicatorOptional::set_implied(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool MatchEventIndicatorOptional::recovery_msg() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void MatchEventIndicatorOptional::set_recovery_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool MatchEventIndicatorOptional::unused_match_event_indicator_6() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void MatchEventIndicatorOptional::set_unused_match_event_indicator_6(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool MatchEventIndicatorOptional::end_of_event() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void MatchEventIndicatorOptional::set_end_of_event(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t MatchEventIndicatorOptional::raw() const { return raw_; }
void MatchEventIndicatorOptional::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t MatchEventIndicatorOptional::decode(const std::byte* data, std::size_t length) {
    wire::require("MatchEventIndicatorOptional", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t MatchEventIndicatorOptional::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("MatchEventIndicatorOptional", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t MatchEventIndicatorOptional::encoded_size() const {
    return wire_size;
}

void MatchEventIndicatorOptional::print(std::ostream& out) const {
    out << "MatchEventIndicatorOptional{";
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

bool MatchEventIndicatorOptional::operator==(const MatchEventIndicatorOptional& other) const {
    return raw_ == other.raw_;
}

bool MatchEventIndicatorOptional::operator!=(const MatchEventIndicatorOptional& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MatchEventIndicatorOptional& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
