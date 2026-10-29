#include "LongFormAdjustedClosingPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

LongFormAdjustedClosingPriceMessage::LongFormAdjustedClosingPriceMessage(const std::string& issue_symbol, SecurityClass security_class, Decimal adjusted_closing_price_long)
  : issue_symbol_(issue_symbol), security_class_(security_class), adjusted_closing_price_long_(adjusted_closing_price_long) {}

const std::string& LongFormAdjustedClosingPriceMessage::issue_symbol() const { return issue_symbol_; }
std::string& LongFormAdjustedClosingPriceMessage::issue_symbol() { return issue_symbol_; }
void LongFormAdjustedClosingPriceMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass LongFormAdjustedClosingPriceMessage::security_class() const { return security_class_; }
void LongFormAdjustedClosingPriceMessage::set_security_class(SecurityClass value) { security_class_ = value; }

Decimal LongFormAdjustedClosingPriceMessage::adjusted_closing_price_long() const { return adjusted_closing_price_long_; }
void LongFormAdjustedClosingPriceMessage::set_adjusted_closing_price_long(Decimal value) { adjusted_closing_price_long_ = value; }

MessageCode LongFormAdjustedClosingPriceMessage::type() const { return message_type; }

std::string_view LongFormAdjustedClosingPriceMessage::name() const { return "Long Form Adjusted Closing Price Message"; }

std::size_t LongFormAdjustedClosingPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LongFormAdjustedClosingPriceMessage", wire_size, length);

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    adjusted_closing_price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t LongFormAdjustedClosingPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LongFormAdjustedClosingPriceMessage", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(adjusted_closing_price_long_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t LongFormAdjustedClosingPriceMessage::encoded_size() const {
    return wire_size;
}

void LongFormAdjustedClosingPriceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LongFormAdjustedClosingPriceMessage::clone() const {
    return std::make_unique<LongFormAdjustedClosingPriceMessage>(*this);
}

void LongFormAdjustedClosingPriceMessage::print(std::ostream& out) const {
    out << "LongFormAdjustedClosingPriceMessage{";
    out << "issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", adjusted_closing_price_long=";
    out << adjusted_closing_price_long_;
    out << '}';
}

bool LongFormAdjustedClosingPriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LongFormAdjustedClosingPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool LongFormAdjustedClosingPriceMessage::operator==(const LongFormAdjustedClosingPriceMessage& other) const {
    return issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && adjusted_closing_price_long_ == other.adjusted_closing_price_long_;
}

bool LongFormAdjustedClosingPriceMessage::operator!=(const LongFormAdjustedClosingPriceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
