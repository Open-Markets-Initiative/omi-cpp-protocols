#include "UnderlyingValueLastSaleMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnderlyingValueLastSaleMessage::UnderlyingValueLastSaleMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, IndexValueDenominatorCode index_value_denominator_code, Decimal index_value, const std::array<std::byte, 4>& reserved_4)
  : message_indicator_(message_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), reserved_1_(reserved_1), index_value_denominator_code_(index_value_denominator_code), index_value_(index_value), reserved_4_(reserved_4) {}

char UnderlyingValueLastSaleMessage::message_indicator() const { return message_indicator_; }
void UnderlyingValueLastSaleMessage::set_message_indicator(char value) { message_indicator_ = value; }

std::uint32_t UnderlyingValueLastSaleMessage::transaction_id() const { return transaction_id_; }
void UnderlyingValueLastSaleMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t UnderlyingValueLastSaleMessage::participant_reference_number() const { return participant_reference_number_; }
void UnderlyingValueLastSaleMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

const std::string& UnderlyingValueLastSaleMessage::security_symbol() const { return security_symbol_; }
std::string& UnderlyingValueLastSaleMessage::security_symbol() { return security_symbol_; }
void UnderlyingValueLastSaleMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::array<std::byte, 1>& UnderlyingValueLastSaleMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& UnderlyingValueLastSaleMessage::reserved_1() { return reserved_1_; }
void UnderlyingValueLastSaleMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

IndexValueDenominatorCode UnderlyingValueLastSaleMessage::index_value_denominator_code() const { return index_value_denominator_code_; }
void UnderlyingValueLastSaleMessage::set_index_value_denominator_code(IndexValueDenominatorCode value) { index_value_denominator_code_ = value; }

Decimal UnderlyingValueLastSaleMessage::index_value() const { return index_value_; }
void UnderlyingValueLastSaleMessage::set_index_value(Decimal value) { index_value_ = value; }
int UnderlyingValueLastSaleMessage::index_value_exponent(char code) {
    switch (code) {
        case 'A': return -1;
        case 'B': return -2;
        case 'C': return -3;
        case 'D': return -4;
        case 'E': return -5;
        case 'F': return -6;
        case 'G': return -7;
        case 'I': return 0;
        default: return 0;
    }
}

const std::array<std::byte, 4>& UnderlyingValueLastSaleMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& UnderlyingValueLastSaleMessage::reserved_4() { return reserved_4_; }
void UnderlyingValueLastSaleMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

UnderlyingValueMessagePayloadCode UnderlyingValueLastSaleMessage::type() const { return message_type; }

std::string_view UnderlyingValueLastSaleMessage::name() const { return "Underlying Value Last Sale Message"; }

std::size_t UnderlyingValueLastSaleMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingValueLastSaleMessage", wire_size, length);

    message_indicator_ = wire::read_char(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    security_symbol_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    index_value_denominator_code_ = static_cast<IndexValueDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    index_value_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), index_value_exponent(static_cast<char>(index_value_denominator_code_)));
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t UnderlyingValueLastSaleMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingValueLastSaleMessage", wire_size, capacity);

    wire::write_char(data + offset, message_indicator_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_reference_number_));
    offset += 4;

    wire::write_text(data + offset, 5, ' ', security_symbol_);
    offset += 5;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(index_value_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(index_value_.mantissa()));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t UnderlyingValueLastSaleMessage::encoded_size() const {
    return wire_size;
}

void UnderlyingValueLastSaleMessage::accept(UnderlyingValueMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnderlyingValueMessagePayload> UnderlyingValueLastSaleMessage::clone() const {
    return std::make_unique<UnderlyingValueLastSaleMessage>(*this);
}

void UnderlyingValueLastSaleMessage::print(std::ostream& out) const {
    out << "UnderlyingValueLastSaleMessage{";
    out << "message_indicator=";
    print::character(out, message_indicator_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", index_value_denominator_code=";
    out << index_value_denominator_code_;
    out << ", index_value=";
    out << index_value_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << '}';
}

bool UnderlyingValueLastSaleMessage::equals(const UnderlyingValueMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnderlyingValueLastSaleMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnderlyingValueLastSaleMessage::operator==(const UnderlyingValueLastSaleMessage& other) const {
    return message_indicator_ == other.message_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && reserved_1_ == other.reserved_1_
        && index_value_denominator_code_ == other.index_value_denominator_code_
        && index_value_ == other.index_value_
        && reserved_4_ == other.reserved_4_;
}

bool UnderlyingValueLastSaleMessage::operator!=(const UnderlyingValueLastSaleMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
