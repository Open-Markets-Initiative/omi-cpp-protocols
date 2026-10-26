#include "SecurityListRequestRelatedSymbolGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

SecurityListRequestRelatedSymbolGroup::SecurityListRequestRelatedSymbolGroup(std::int32_t security_id)
  : security_id_(security_id) {}

std::int32_t SecurityListRequestRelatedSymbolGroup::security_id() const { return security_id_; }
void SecurityListRequestRelatedSymbolGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::size_t SecurityListRequestRelatedSymbolGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityListRequestRelatedSymbolGroup", wire_size, length);

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SecurityListRequestRelatedSymbolGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityListRequestRelatedSymbolGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    return offset;
}

std::size_t SecurityListRequestRelatedSymbolGroup::encoded_size() const {
    return wire_size;
}

void SecurityListRequestRelatedSymbolGroup::print(std::ostream& out) const {
    out << "SecurityListRequestRelatedSymbolGroup{";
    out << "security_id=";
    out << security_id_;
    out << '}';
}

bool SecurityListRequestRelatedSymbolGroup::operator==(const SecurityListRequestRelatedSymbolGroup& other) const {
    return security_id_ == other.security_id_;
}

bool SecurityListRequestRelatedSymbolGroup::operator!=(const SecurityListRequestRelatedSymbolGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityListRequestRelatedSymbolGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
