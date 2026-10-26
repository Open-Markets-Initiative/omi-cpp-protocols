#include "SecurityStatusRequestRelatedSymbolGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

SecurityStatusRequestRelatedSymbolGroup::SecurityStatusRequestRelatedSymbolGroup(std::int32_t security_id)
  : security_id_(security_id) {}

std::int32_t SecurityStatusRequestRelatedSymbolGroup::security_id() const { return security_id_; }
void SecurityStatusRequestRelatedSymbolGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::size_t SecurityStatusRequestRelatedSymbolGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityStatusRequestRelatedSymbolGroup", wire_size, length);

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SecurityStatusRequestRelatedSymbolGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityStatusRequestRelatedSymbolGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    return offset;
}

std::size_t SecurityStatusRequestRelatedSymbolGroup::encoded_size() const {
    return wire_size;
}

void SecurityStatusRequestRelatedSymbolGroup::print(std::ostream& out) const {
    out << "SecurityStatusRequestRelatedSymbolGroup{";
    out << "security_id=";
    out << security_id_;
    out << '}';
}

bool SecurityStatusRequestRelatedSymbolGroup::operator==(const SecurityStatusRequestRelatedSymbolGroup& other) const {
    return security_id_ == other.security_id_;
}

bool SecurityStatusRequestRelatedSymbolGroup::operator!=(const SecurityStatusRequestRelatedSymbolGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityStatusRequestRelatedSymbolGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
