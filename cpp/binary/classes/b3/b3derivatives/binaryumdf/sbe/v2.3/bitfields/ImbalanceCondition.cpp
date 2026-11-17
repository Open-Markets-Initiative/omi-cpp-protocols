// B3.B3Derivatives.BinaryUmdf.Sbe.v2.3: bitfields/ImbalanceCondition.cpp
#include "ImbalanceCondition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

ImbalanceCondition::ImbalanceCondition(std::uint16_t raw) : raw_(raw) {}

bool ImbalanceCondition::imbalance_more_buyers() const { return (raw_ & static_cast<std::uint16_t>(0x100)) != 0; }
void ImbalanceCondition::set_imbalance_more_buyers(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x100)) : (raw_ & ~static_cast<std::uint16_t>(0x100))); }

bool ImbalanceCondition::imbalance_more_sellers() const { return (raw_ & static_cast<std::uint16_t>(0x200)) != 0; }
void ImbalanceCondition::set_imbalance_more_sellers(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x200)) : (raw_ & ~static_cast<std::uint16_t>(0x200))); }

std::uint16_t ImbalanceCondition::raw() const { return raw_; }
void ImbalanceCondition::set_raw(std::uint16_t value) { raw_ = value; }

std::size_t ImbalanceCondition::decode(const std::byte* data, std::size_t length) {
    wire::require("ImbalanceCondition", wire_size, length);
    raw_ = wire::read_u16_le(data);
    return wire_size;
}

std::size_t ImbalanceCondition::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("ImbalanceCondition", wire_size, capacity);
    wire::write_u16_le(data, raw_);
    return wire_size;
}

std::size_t ImbalanceCondition::encoded_size() const {
    return wire_size;
}

void ImbalanceCondition::print(std::ostream& out) const {
    out << "ImbalanceCondition{";
    out << "imbalance_more_buyers=";
    out << (imbalance_more_buyers() ? "true" : "false");
    out << ", imbalance_more_sellers=";
    out << (imbalance_more_sellers() ? "true" : "false");
    out << '}';
}

bool ImbalanceCondition::operator==(const ImbalanceCondition& other) const {
    return raw_ == other.raw_;
}

bool ImbalanceCondition::operator!=(const ImbalanceCondition& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ImbalanceCondition& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
