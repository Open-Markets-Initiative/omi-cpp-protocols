#include "AdjustedClosingPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

AdjustedClosingPriceMessage::AdjustedClosingPriceMessage(const std::string& issue_symbol, SecurityClass security_class, Decimal adjusted_closing_price)
  : issue_symbol_(issue_symbol), security_class_(security_class), adjusted_closing_price_(adjusted_closing_price) {}

const std::string& AdjustedClosingPriceMessage::issue_symbol() const { return issue_symbol_; }
std::string& AdjustedClosingPriceMessage::issue_symbol() { return issue_symbol_; }
void AdjustedClosingPriceMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass AdjustedClosingPriceMessage::security_class() const { return security_class_; }
void AdjustedClosingPriceMessage::set_security_class(SecurityClass value) { security_class_ = value; }

Decimal AdjustedClosingPriceMessage::adjusted_closing_price() const { return adjusted_closing_price_; }
void AdjustedClosingPriceMessage::set_adjusted_closing_price(Decimal value) { adjusted_closing_price_ = value; }

MessageCode AdjustedClosingPriceMessage::type() const { return message_type; }

std::string_view AdjustedClosingPriceMessage::name() const { return "Adjusted Closing Price Message"; }

std::size_t AdjustedClosingPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AdjustedClosingPriceMessage", wire_size, length);

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    adjusted_closing_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t AdjustedClosingPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AdjustedClosingPriceMessage", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(adjusted_closing_price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t AdjustedClosingPriceMessage::encoded_size() const {
    return wire_size;
}

void AdjustedClosingPriceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AdjustedClosingPriceMessage::clone() const {
    return std::make_unique<AdjustedClosingPriceMessage>(*this);
}

void AdjustedClosingPriceMessage::print(std::ostream& out) const {
    out << "AdjustedClosingPriceMessage{";
    out << "issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", adjusted_closing_price=";
    out << adjusted_closing_price_;
    out << '}';
}

bool AdjustedClosingPriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AdjustedClosingPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AdjustedClosingPriceMessage::operator==(const AdjustedClosingPriceMessage& other) const {
    return issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && adjusted_closing_price_ == other.adjusted_closing_price_;
}

bool AdjustedClosingPriceMessage::operator!=(const AdjustedClosingPriceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
