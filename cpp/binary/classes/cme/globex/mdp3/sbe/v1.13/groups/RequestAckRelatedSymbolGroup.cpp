#include "RequestAckRelatedSymbolGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

RequestAckRelatedSymbolGroup::RequestAckRelatedSymbolGroup(std::int32_t security_id)
  : security_id_(security_id) {}

std::int32_t RequestAckRelatedSymbolGroup::security_id() const { return security_id_; }
void RequestAckRelatedSymbolGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::size_t RequestAckRelatedSymbolGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RequestAckRelatedSymbolGroup", wire_size, length);

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t RequestAckRelatedSymbolGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RequestAckRelatedSymbolGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    return offset;
}

std::size_t RequestAckRelatedSymbolGroup::encoded_size() const {
    return wire_size;
}

void RequestAckRelatedSymbolGroup::print(std::ostream& out) const {
    out << "RequestAckRelatedSymbolGroup{";
    out << "security_id=";
    out << security_id_;
    out << '}';
}

bool RequestAckRelatedSymbolGroup::operator==(const RequestAckRelatedSymbolGroup& other) const {
    return security_id_ == other.security_id_;
}

bool RequestAckRelatedSymbolGroup::operator!=(const RequestAckRelatedSymbolGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RequestAckRelatedSymbolGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
