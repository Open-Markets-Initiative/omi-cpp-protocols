#include "RegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

RegShoShortSalePriceTestRestrictedIndicatorMessage::RegShoShortSalePriceTestRestrictedIndicatorMessage(std::uint16_t locate_code, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, RegShoAction reg_sho_action)
  : locate_code_(locate_code), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), reg_sho_action_(reg_sho_action) {}

std::uint16_t RegShoShortSalePriceTestRestrictedIndicatorMessage::locate_code() const { return locate_code_; }
void RegShoShortSalePriceTestRestrictedIndicatorMessage::set_locate_code(std::uint16_t value) { locate_code_ = value; }

std::uint16_t RegShoShortSalePriceTestRestrictedIndicatorMessage::tracking_number() const { return tracking_number_; }
void RegShoShortSalePriceTestRestrictedIndicatorMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds RegShoShortSalePriceTestRestrictedIndicatorMessage::timestamp() const { return timestamp_; }
void RegShoShortSalePriceTestRestrictedIndicatorMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& RegShoShortSalePriceTestRestrictedIndicatorMessage::stock() const { return stock_; }
std::string& RegShoShortSalePriceTestRestrictedIndicatorMessage::stock() { return stock_; }
void RegShoShortSalePriceTestRestrictedIndicatorMessage::set_stock(const std::string& value) { stock_ = value; }

RegShoAction RegShoShortSalePriceTestRestrictedIndicatorMessage::reg_sho_action() const { return reg_sho_action_; }
void RegShoShortSalePriceTestRestrictedIndicatorMessage::set_reg_sho_action(RegShoAction value) { reg_sho_action_ = value; }

MessageCode RegShoShortSalePriceTestRestrictedIndicatorMessage::type() const { return message_type; }

std::string_view RegShoShortSalePriceTestRestrictedIndicatorMessage::name() const { return "Reg Sho Short Sale Price Test Restricted Indicator Message"; }

std::size_t RegShoShortSalePriceTestRestrictedIndicatorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RegShoShortSalePriceTestRestrictedIndicatorMessage", wire_size, length);

    locate_code_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    reg_sho_action_ = static_cast<RegShoAction>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RegShoShortSalePriceTestRestrictedIndicatorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RegShoShortSalePriceTestRestrictedIndicatorMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(locate_code_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(reg_sho_action_));
    offset += 1;

    return offset;
}

std::size_t RegShoShortSalePriceTestRestrictedIndicatorMessage::encoded_size() const {
    return wire_size;
}

void RegShoShortSalePriceTestRestrictedIndicatorMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RegShoShortSalePriceTestRestrictedIndicatorMessage::clone() const {
    return std::make_unique<RegShoShortSalePriceTestRestrictedIndicatorMessage>(*this);
}

void RegShoShortSalePriceTestRestrictedIndicatorMessage::print(std::ostream& out) const {
    out << "RegShoShortSalePriceTestRestrictedIndicatorMessage{";
    out << "locate_code=";
    out << locate_code_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", reg_sho_action=";
    out << reg_sho_action_;
    out << '}';
}

bool RegShoShortSalePriceTestRestrictedIndicatorMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RegShoShortSalePriceTestRestrictedIndicatorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RegShoShortSalePriceTestRestrictedIndicatorMessage::operator==(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const {
    return locate_code_ == other.locate_code_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && reg_sho_action_ == other.reg_sho_action_;
}

bool RegShoShortSalePriceTestRestrictedIndicatorMessage::operator!=(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
