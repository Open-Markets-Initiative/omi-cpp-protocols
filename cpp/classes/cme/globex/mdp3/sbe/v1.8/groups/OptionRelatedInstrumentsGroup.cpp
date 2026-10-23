#include "OptionRelatedInstrumentsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

OptionRelatedInstrumentsGroup::OptionRelatedInstrumentsGroup(std::int32_t related_security_id, const std::string& related_symbol)
  : related_security_id_(related_security_id), related_symbol_(related_symbol) {}

std::int32_t OptionRelatedInstrumentsGroup::related_security_id() const { return related_security_id_; }
void OptionRelatedInstrumentsGroup::set_related_security_id(std::int32_t value) { related_security_id_ = value; }

const std::string& OptionRelatedInstrumentsGroup::related_symbol() const { return related_symbol_; }
std::string& OptionRelatedInstrumentsGroup::related_symbol() { return related_symbol_; }
void OptionRelatedInstrumentsGroup::set_related_symbol(const std::string& value) { related_symbol_ = value; }

std::size_t OptionRelatedInstrumentsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionRelatedInstrumentsGroup", wire_size, length);

    related_security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    related_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    return offset;
}

std::size_t OptionRelatedInstrumentsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionRelatedInstrumentsGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(related_security_id_));
    offset += 4;

    wire::write_text(data + offset, 20, '\0', related_symbol_);
    offset += 20;

    return offset;
}

std::size_t OptionRelatedInstrumentsGroup::encoded_size() const {
    return wire_size;
}

void OptionRelatedInstrumentsGroup::print(std::ostream& out) const {
    out << "OptionRelatedInstrumentsGroup{";
    out << "related_security_id=";
    out << related_security_id_;
    out << ", related_symbol=";
    print::text(out, related_symbol_);
    out << '}';
}

bool OptionRelatedInstrumentsGroup::operator==(const OptionRelatedInstrumentsGroup& other) const {
    return related_security_id_ == other.related_security_id_
        && related_symbol_ == other.related_symbol_;
}

bool OptionRelatedInstrumentsGroup::operator!=(const OptionRelatedInstrumentsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OptionRelatedInstrumentsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
