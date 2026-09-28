#include "UnderlyingsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

UnderlyingsGroup::UnderlyingsGroup(std::uint64_t underlying_security_id, const std::string& underlying_symbol)
  : underlying_security_id_(underlying_security_id), underlying_symbol_(underlying_symbol) {}

std::uint64_t UnderlyingsGroup::underlying_security_id() const { return underlying_security_id_; }
void UnderlyingsGroup::set_underlying_security_id(std::uint64_t value) { underlying_security_id_ = value; }

const std::string& UnderlyingsGroup::underlying_symbol() const { return underlying_symbol_; }
std::string& UnderlyingsGroup::underlying_symbol() { return underlying_symbol_; }
void UnderlyingsGroup::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

std::size_t UnderlyingsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingsGroup", wire_size, length);

    underlying_security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    underlying_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    return offset;
}

std::size_t UnderlyingsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingsGroup", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(underlying_security_id_));
    offset += 8;

    wire::write_text(data + offset, 20, '\0', underlying_symbol_);
    offset += 20;

    return offset;
}

std::size_t UnderlyingsGroup::encoded_size() const {
    return wire_size;
}

void UnderlyingsGroup::print(std::ostream& out) const {
    out << "UnderlyingsGroup{";
    out << "underlying_security_id=";
    out << underlying_security_id_;
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << '}';
}

bool UnderlyingsGroup::operator==(const UnderlyingsGroup& other) const {
    return underlying_security_id_ == other.underlying_security_id_
        && underlying_symbol_ == other.underlying_symbol_;
}

bool UnderlyingsGroup::operator!=(const UnderlyingsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const UnderlyingsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
