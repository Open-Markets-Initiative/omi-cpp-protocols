#include "ImbalanceCondition.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

ImbalanceCondition::ImbalanceCondition(std::uint16_t raw) : raw_(raw) {}

bool ImbalanceCondition::unused_imbalance_condition_0() const { return (raw_ & static_cast<std::uint16_t>(0x1)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_0(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x1)) : (raw_ & ~static_cast<std::uint16_t>(0x1))); }

bool ImbalanceCondition::unused_imbalance_condition_1() const { return (raw_ & static_cast<std::uint16_t>(0x2)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_1(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x2)) : (raw_ & ~static_cast<std::uint16_t>(0x2))); }

bool ImbalanceCondition::unused_imbalance_condition_2() const { return (raw_ & static_cast<std::uint16_t>(0x4)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_2(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x4)) : (raw_ & ~static_cast<std::uint16_t>(0x4))); }

bool ImbalanceCondition::unused_imbalance_condition_3() const { return (raw_ & static_cast<std::uint16_t>(0x8)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_3(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x8)) : (raw_ & ~static_cast<std::uint16_t>(0x8))); }

bool ImbalanceCondition::unused_imbalance_condition_4() const { return (raw_ & static_cast<std::uint16_t>(0x10)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_4(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x10)) : (raw_ & ~static_cast<std::uint16_t>(0x10))); }

bool ImbalanceCondition::unused_imbalance_condition_5() const { return (raw_ & static_cast<std::uint16_t>(0x20)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_5(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x20)) : (raw_ & ~static_cast<std::uint16_t>(0x20))); }

bool ImbalanceCondition::unused_imbalance_condition_6() const { return (raw_ & static_cast<std::uint16_t>(0x40)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_6(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x40)) : (raw_ & ~static_cast<std::uint16_t>(0x40))); }

bool ImbalanceCondition::unused_imbalance_condition_7() const { return (raw_ & static_cast<std::uint16_t>(0x80)) != 0; }
void ImbalanceCondition::set_unused_imbalance_condition_7(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x80)) : (raw_ & ~static_cast<std::uint16_t>(0x80))); }

bool ImbalanceCondition::imbalance_more_buyers() const { return (raw_ & static_cast<std::uint16_t>(0x100)) != 0; }
void ImbalanceCondition::set_imbalance_more_buyers(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x100)) : (raw_ & ~static_cast<std::uint16_t>(0x100))); }

bool ImbalanceCondition::imbalance_more_sellers() const { return (raw_ & static_cast<std::uint16_t>(0x200)) != 0; }
void ImbalanceCondition::set_imbalance_more_sellers(bool value) { raw_ = static_cast<std::uint16_t>(value ? (raw_ | static_cast<std::uint16_t>(0x200)) : (raw_ & ~static_cast<std::uint16_t>(0x200))); }

std::uint8_t ImbalanceCondition::reserved_6() const { return static_cast<std::uint8_t>((raw_ & static_cast<std::uint16_t>(0xFC00)) >> 10); }
void ImbalanceCondition::set_reserved_6(std::uint8_t value) { raw_ = static_cast<std::uint16_t>((raw_ & ~static_cast<std::uint16_t>(0xFC00)) | ((static_cast<std::uint16_t>(value) << 10) & static_cast<std::uint16_t>(0xFC00))); }

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
    out << "unused_imbalance_condition_0=";
    out << (unused_imbalance_condition_0() ? "true" : "false");
    out << ", unused_imbalance_condition_1=";
    out << (unused_imbalance_condition_1() ? "true" : "false");
    out << ", unused_imbalance_condition_2=";
    out << (unused_imbalance_condition_2() ? "true" : "false");
    out << ", unused_imbalance_condition_3=";
    out << (unused_imbalance_condition_3() ? "true" : "false");
    out << ", unused_imbalance_condition_4=";
    out << (unused_imbalance_condition_4() ? "true" : "false");
    out << ", unused_imbalance_condition_5=";
    out << (unused_imbalance_condition_5() ? "true" : "false");
    out << ", unused_imbalance_condition_6=";
    out << (unused_imbalance_condition_6() ? "true" : "false");
    out << ", unused_imbalance_condition_7=";
    out << (unused_imbalance_condition_7() ? "true" : "false");
    out << ", imbalance_more_buyers=";
    out << (imbalance_more_buyers() ? "true" : "false");
    out << ", imbalance_more_sellers=";
    out << (imbalance_more_sellers() ? "true" : "false");
    out << ", reserved_6=";
    out << static_cast<unsigned long long>(reserved_6());
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

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
