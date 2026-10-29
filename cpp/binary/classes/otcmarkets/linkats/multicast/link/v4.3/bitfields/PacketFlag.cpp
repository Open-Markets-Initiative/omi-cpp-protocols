#include "PacketFlag.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

PacketFlag::PacketFlag(std::uint8_t raw) : raw_(raw) {}

bool PacketFlag::heartbeat() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void PacketFlag::set_heartbeat(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool PacketFlag::seq_num_reset() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void PacketFlag::set_seq_num_reset(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool PacketFlag::replay() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void PacketFlag::set_replay(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool PacketFlag::test() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void PacketFlag::set_test(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t PacketFlag::raw() const { return raw_; }
void PacketFlag::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t PacketFlag::decode(const std::byte* data, std::size_t length) {
    wire::require("PacketFlag", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t PacketFlag::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("PacketFlag", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t PacketFlag::encoded_size() const {
    return wire_size;
}

void PacketFlag::print(std::ostream& out) const {
    out << "PacketFlag{";
    out << "heartbeat=";
    out << (heartbeat() ? "true" : "false");
    out << ", seq_num_reset=";
    out << (seq_num_reset() ? "true" : "false");
    out << ", replay=";
    out << (replay() ? "true" : "false");
    out << ", test=";
    out << (test() ? "true" : "false");
    out << '}';
}

bool PacketFlag::operator==(const PacketFlag& other) const {
    return raw_ == other.raw_;
}

bool PacketFlag::operator!=(const PacketFlag& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketFlag& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
