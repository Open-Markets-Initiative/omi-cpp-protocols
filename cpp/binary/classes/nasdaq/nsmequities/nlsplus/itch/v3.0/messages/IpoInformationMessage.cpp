#include "IpoInformationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

IpoInformationMessage::IpoInformationMessage(const std::string& issue_symbol, SecurityClass security_class, ReferenceForNetChange reference_for_net_change, Decimal reference_price)
  : issue_symbol_(issue_symbol), security_class_(security_class), reference_for_net_change_(reference_for_net_change), reference_price_(reference_price) {}

const std::string& IpoInformationMessage::issue_symbol() const { return issue_symbol_; }
std::string& IpoInformationMessage::issue_symbol() { return issue_symbol_; }
void IpoInformationMessage::set_issue_symbol(const std::string& value) { issue_symbol_ = value; }

SecurityClass IpoInformationMessage::security_class() const { return security_class_; }
void IpoInformationMessage::set_security_class(SecurityClass value) { security_class_ = value; }

ReferenceForNetChange IpoInformationMessage::reference_for_net_change() const { return reference_for_net_change_; }
void IpoInformationMessage::set_reference_for_net_change(ReferenceForNetChange value) { reference_for_net_change_ = value; }

Decimal IpoInformationMessage::reference_price() const { return reference_price_; }
void IpoInformationMessage::set_reference_price(Decimal value) { reference_price_ = value; }

MessageCode IpoInformationMessage::type() const { return message_type; }

std::string_view IpoInformationMessage::name() const { return "Ipo Information Message"; }

std::size_t IpoInformationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("IpoInformationMessage", wire_size, length);

    issue_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    security_class_ = static_cast<SecurityClass>(wire::read_char(data + offset));
    offset += 1;

    reference_for_net_change_ = static_cast<ReferenceForNetChange>(wire::read_char(data + offset));
    offset += 1;

    reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t IpoInformationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IpoInformationMessage", wire_size, capacity);

    wire::write_text(data + offset, 8, ' ', issue_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(security_class_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(reference_for_net_change_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(reference_price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t IpoInformationMessage::encoded_size() const {
    return wire_size;
}

void IpoInformationMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> IpoInformationMessage::clone() const {
    return std::make_unique<IpoInformationMessage>(*this);
}

void IpoInformationMessage::print(std::ostream& out) const {
    out << "IpoInformationMessage{";
    out << "issue_symbol=";
    print::text(out, issue_symbol_);
    out << ", security_class=";
    out << security_class_;
    out << ", reference_for_net_change=";
    out << reference_for_net_change_;
    out << ", reference_price=";
    out << reference_price_;
    out << '}';
}

bool IpoInformationMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const IpoInformationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool IpoInformationMessage::operator==(const IpoInformationMessage& other) const {
    return issue_symbol_ == other.issue_symbol_
        && security_class_ == other.security_class_
        && reference_for_net_change_ == other.reference_for_net_change_
        && reference_price_ == other.reference_price_;
}

bool IpoInformationMessage::operator!=(const IpoInformationMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
