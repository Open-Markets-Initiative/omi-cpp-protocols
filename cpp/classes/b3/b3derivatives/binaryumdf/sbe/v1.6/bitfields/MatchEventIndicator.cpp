#include "MatchEventIndicator.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

MatchEventIndicator::MatchEventIndicator(std::uint8_t raw) : raw_(raw) {}

bool MatchEventIndicator::last_trade_msg() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void MatchEventIndicator::set_last_trade_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool MatchEventIndicator::last_volume_msg() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void MatchEventIndicator::set_last_volume_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool MatchEventIndicator::last_quote_msg() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void MatchEventIndicator::set_last_quote_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool MatchEventIndicator::last_stats_msg() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void MatchEventIndicator::set_last_stats_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool MatchEventIndicator::last_implied_msg() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void MatchEventIndicator::set_last_implied_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool MatchEventIndicator::recovery_msg() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void MatchEventIndicator::set_recovery_msg(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool MatchEventIndicator::unused() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void MatchEventIndicator::set_unused(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

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
    out << "last_trade_msg=";
    out << (last_trade_msg() ? "true" : "false");
    out << ", last_volume_msg=";
    out << (last_volume_msg() ? "true" : "false");
    out << ", last_quote_msg=";
    out << (last_quote_msg() ? "true" : "false");
    out << ", last_stats_msg=";
    out << (last_stats_msg() ? "true" : "false");
    out << ", last_implied_msg=";
    out << (last_implied_msg() ? "true" : "false");
    out << ", recovery_msg=";
    out << (recovery_msg() ? "true" : "false");
    out << ", unused=";
    out << (unused() ? "true" : "false");
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

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
