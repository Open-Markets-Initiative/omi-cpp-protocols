#include "OptionUnderlyingsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

OptionUnderlyingsGroup::OptionUnderlyingsGroup(std::int32_t underlying_security_id, const std::string& underlying_symbol)
  : underlying_security_id_(underlying_security_id), underlying_symbol_(underlying_symbol) {}

std::int32_t OptionUnderlyingsGroup::underlying_security_id() const { return underlying_security_id_; }
void OptionUnderlyingsGroup::set_underlying_security_id(std::int32_t value) { underlying_security_id_ = value; }

const std::string& OptionUnderlyingsGroup::underlying_symbol() const { return underlying_symbol_; }
std::string& OptionUnderlyingsGroup::underlying_symbol() { return underlying_symbol_; }
void OptionUnderlyingsGroup::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

std::size_t OptionUnderlyingsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionUnderlyingsGroup", wire_size, length);

    underlying_security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    underlying_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    return offset;
}

std::size_t OptionUnderlyingsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionUnderlyingsGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(underlying_security_id_));
    offset += 4;

    wire::write_text(data + offset, 20, '\0', underlying_symbol_);
    offset += 20;

    return offset;
}

std::size_t OptionUnderlyingsGroup::encoded_size() const {
    return wire_size;
}

void OptionUnderlyingsGroup::print(std::ostream& out) const {
    out << "OptionUnderlyingsGroup{";
    out << "underlying_security_id=";
    out << underlying_security_id_;
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << '}';
}

bool OptionUnderlyingsGroup::operator==(const OptionUnderlyingsGroup& other) const {
    return underlying_security_id_ == other.underlying_security_id_
        && underlying_symbol_ == other.underlying_symbol_;
}

bool OptionUnderlyingsGroup::operator!=(const OptionUnderlyingsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OptionUnderlyingsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
