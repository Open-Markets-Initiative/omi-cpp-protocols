#include "RegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

RegShoShortSalePriceTestRestrictedIndicatorMessage::RegShoShortSalePriceTestRestrictedIndicatorMessage(const std::string& issue_symbol, RegShoAction reg_sho_action)
  : issue_symbol_(issue_symbol), reg_sho_action_(reg_sho_action) {}

const std::string& RegShoShortSalePriceTestRestrictedIndicatorMessage::issue_symbol() const { return issue_symbol_; }
std::string& RegShoShortSalePriceTestRestrictedIndicatorMessage::issue_symbol() { return issue_symbol_; }
void RegShoShortSalePriceTestRestrictedIndicatorMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

RegShoAction RegShoShortSalePriceTestRestrictedIndicatorMessage::reg_sho_action() const { return reg_sho_action_; }
void RegShoShortSalePriceTestRestrictedIndicatorMessage::set_reg_sho_action(RegShoAction value) { reg_sho_action_ = value; }

MessageCode RegShoShortSalePriceTestRestrictedIndicatorMessage::type() const { return message_type; }

std::string_view RegShoShortSalePriceTestRestrictedIndicatorMessage::name() const { return "Reg Sho Short Sale Price Test Restricted Indicator Message"; }

std::size_t RegShoShortSalePriceTestRestrictedIndicatorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RegShoShortSalePriceTestRestrictedIndicatorMessage", wire_size, length);

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    reg_sho_action_ = static_cast<RegShoAction>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RegShoShortSalePriceTestRestrictedIndicatorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RegShoShortSalePriceTestRestrictedIndicatorMessage", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
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
    out << "issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", reg_sho_action=";
    out << reg_sho_action_;
    out << '}';
}

bool RegShoShortSalePriceTestRestrictedIndicatorMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RegShoShortSalePriceTestRestrictedIndicatorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RegShoShortSalePriceTestRestrictedIndicatorMessage::operator==(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const {
    return issue_symbol_ == other.issue_symbol_
        && reg_sho_action_ == other.reg_sho_action_;
}

bool RegShoShortSalePriceTestRestrictedIndicatorMessage::operator!=(const RegShoShortSalePriceTestRestrictedIndicatorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
