#include "MarketDataRequestRelatedSymbolGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

MarketDataRequestRelatedSymbolGroup::MarketDataRequestRelatedSymbolGroup(std::int32_t security_id)
  : security_id_(security_id) {}

std::int32_t MarketDataRequestRelatedSymbolGroup::security_id() const { return security_id_; }
void MarketDataRequestRelatedSymbolGroup::set_security_id(std::int32_t value) { security_id_ = value; }

std::size_t MarketDataRequestRelatedSymbolGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketDataRequestRelatedSymbolGroup", wire_size, length);

    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t MarketDataRequestRelatedSymbolGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketDataRequestRelatedSymbolGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    return offset;
}

std::size_t MarketDataRequestRelatedSymbolGroup::encoded_size() const {
    return wire_size;
}

void MarketDataRequestRelatedSymbolGroup::print(std::ostream& out) const {
    out << "MarketDataRequestRelatedSymbolGroup{";
    out << "security_id=";
    out << security_id_;
    out << '}';
}

bool MarketDataRequestRelatedSymbolGroup::operator==(const MarketDataRequestRelatedSymbolGroup& other) const {
    return security_id_ == other.security_id_;
}

bool MarketDataRequestRelatedSymbolGroup::operator!=(const MarketDataRequestRelatedSymbolGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MarketDataRequestRelatedSymbolGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
