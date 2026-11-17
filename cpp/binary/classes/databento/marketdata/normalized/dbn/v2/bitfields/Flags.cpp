// Databento.MarketData.Normalized.Dbn.v2: bitfields/Flags.cpp
#include "Flags.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

Flags::Flags(std::uint8_t raw) : raw_(raw) {}

bool Flags::reserved_flag() const { return (raw_ & static_cast<std::uint8_t>(0x1)) != 0; }
void Flags::set_reserved_flag(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x1)) : (raw_ & ~static_cast<std::uint8_t>(0x1))); }

bool Flags::publisher_specific() const { return (raw_ & static_cast<std::uint8_t>(0x2)) != 0; }
void Flags::set_publisher_specific(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x2)) : (raw_ & ~static_cast<std::uint8_t>(0x2))); }

bool Flags::maybe_bad_book() const { return (raw_ & static_cast<std::uint8_t>(0x4)) != 0; }
void Flags::set_maybe_bad_book(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x4)) : (raw_ & ~static_cast<std::uint8_t>(0x4))); }

bool Flags::bad_ts_recv() const { return (raw_ & static_cast<std::uint8_t>(0x8)) != 0; }
void Flags::set_bad_ts_recv(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x8)) : (raw_ & ~static_cast<std::uint8_t>(0x8))); }

bool Flags::mbp() const { return (raw_ & static_cast<std::uint8_t>(0x10)) != 0; }
void Flags::set_mbp(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x10)) : (raw_ & ~static_cast<std::uint8_t>(0x10))); }

bool Flags::snapshot() const { return (raw_ & static_cast<std::uint8_t>(0x20)) != 0; }
void Flags::set_snapshot(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x20)) : (raw_ & ~static_cast<std::uint8_t>(0x20))); }

bool Flags::tob() const { return (raw_ & static_cast<std::uint8_t>(0x40)) != 0; }
void Flags::set_tob(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x40)) : (raw_ & ~static_cast<std::uint8_t>(0x40))); }

bool Flags::last() const { return (raw_ & static_cast<std::uint8_t>(0x80)) != 0; }
void Flags::set_last(bool value) { raw_ = static_cast<std::uint8_t>(value ? (raw_ | static_cast<std::uint8_t>(0x80)) : (raw_ & ~static_cast<std::uint8_t>(0x80))); }

std::uint8_t Flags::raw() const { return raw_; }
void Flags::set_raw(std::uint8_t value) { raw_ = value; }

std::size_t Flags::decode(const std::byte* data, std::size_t length) {
    wire::require("Flags", wire_size, length);
    raw_ = wire::read_u8(data);
    return wire_size;
}

std::size_t Flags::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("Flags", wire_size, capacity);
    wire::write_u8(data, raw_);
    return wire_size;
}

std::size_t Flags::encoded_size() const {
    return wire_size;
}

void Flags::print(std::ostream& out) const {
    out << "Flags{";
    out << "reserved_flag=";
    out << (reserved_flag() ? "true" : "false");
    out << ", publisher_specific=";
    out << (publisher_specific() ? "true" : "false");
    out << ", maybe_bad_book=";
    out << (maybe_bad_book() ? "true" : "false");
    out << ", bad_ts_recv=";
    out << (bad_ts_recv() ? "true" : "false");
    out << ", mbp=";
    out << (mbp() ? "true" : "false");
    out << ", snapshot=";
    out << (snapshot() ? "true" : "false");
    out << ", tob=";
    out << (tob() ? "true" : "false");
    out << ", last=";
    out << (last() ? "true" : "false");
    out << '}';
}

bool Flags::operator==(const Flags& other) const {
    return raw_ == other.raw_;
}

bool Flags::operator!=(const Flags& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Flags& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
