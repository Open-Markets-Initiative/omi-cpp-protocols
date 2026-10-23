#include "RegShoRestrictionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

RegShoRestrictionMessage::RegShoRestrictionMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, const std::string& stock, RegShoAction reg_sho_action)
  : tracking_number_(tracking_number), time_stamp_(time_stamp), stock_(stock), reg_sho_action_(reg_sho_action) {}

std::uint16_t RegShoRestrictionMessage::tracking_number() const { return tracking_number_; }
void RegShoRestrictionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds RegShoRestrictionMessage::time_stamp() const { return time_stamp_; }
void RegShoRestrictionMessage::set_time_stamp(std::chrono::nanoseconds value) { time_stamp_ = value; }

const std::string& RegShoRestrictionMessage::stock() const { return stock_; }
std::string& RegShoRestrictionMessage::stock() { return stock_; }
void RegShoRestrictionMessage::set_stock(const std::string& value) { stock_ = value; }

RegShoAction RegShoRestrictionMessage::reg_sho_action() const { return reg_sho_action_; }
void RegShoRestrictionMessage::set_reg_sho_action(RegShoAction value) { reg_sho_action_ = value; }

MessageCode RegShoRestrictionMessage::type() const { return message_type; }

std::string_view RegShoRestrictionMessage::name() const { return "Reg Sho Restriction Message"; }

std::size_t RegShoRestrictionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RegShoRestrictionMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    time_stamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    reg_sho_action_ = static_cast<RegShoAction>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RegShoRestrictionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RegShoRestrictionMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(time_stamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(reg_sho_action_));
    offset += 1;

    return offset;
}

std::size_t RegShoRestrictionMessage::encoded_size() const {
    return wire_size;
}

void RegShoRestrictionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RegShoRestrictionMessage::clone() const {
    return std::make_unique<RegShoRestrictionMessage>(*this);
}

void RegShoRestrictionMessage::print(std::ostream& out) const {
    out << "RegShoRestrictionMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", time_stamp=";
    out << time_stamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", reg_sho_action=";
    out << reg_sho_action_;
    out << '}';
}

bool RegShoRestrictionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RegShoRestrictionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RegShoRestrictionMessage::operator==(const RegShoRestrictionMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && time_stamp_ == other.time_stamp_
        && stock_ == other.stock_
        && reg_sho_action_ == other.reg_sho_action_;
}

bool RegShoRestrictionMessage::operator!=(const RegShoRestrictionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
