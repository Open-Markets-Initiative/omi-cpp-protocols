#include "EquityAndIndexLastSaleMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

EquityAndIndexLastSaleMessage::EquityAndIndexLastSaleMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, std::uint32_t volume, PremiumPriceDenominatorCode premium_price_denominator_code, Decimal premium_price, std::uint32_t trade_identifier, const std::array<std::byte, 4>& reserved_4)
  : message_indicator_(message_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), reserved_1_(reserved_1), expiration_block_(expiration_block), strike_price_denominator_code_(strike_price_denominator_code), strike_price_(strike_price), volume_(volume), premium_price_denominator_code_(premium_price_denominator_code), premium_price_(premium_price), trade_identifier_(trade_identifier), reserved_4_(reserved_4) {}

char EquityAndIndexLastSaleMessage::message_indicator() const { return message_indicator_; }
void EquityAndIndexLastSaleMessage::set_message_indicator(char value) { message_indicator_ = value; }

std::uint32_t EquityAndIndexLastSaleMessage::transaction_id() const { return transaction_id_; }
void EquityAndIndexLastSaleMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t EquityAndIndexLastSaleMessage::participant_reference_number() const { return participant_reference_number_; }
void EquityAndIndexLastSaleMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

const std::string& EquityAndIndexLastSaleMessage::security_symbol() const { return security_symbol_; }
std::string& EquityAndIndexLastSaleMessage::security_symbol() { return security_symbol_; }
void EquityAndIndexLastSaleMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::array<std::byte, 1>& EquityAndIndexLastSaleMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& EquityAndIndexLastSaleMessage::reserved_1() { return reserved_1_; }
void EquityAndIndexLastSaleMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const ExpirationBlock& EquityAndIndexLastSaleMessage::expiration_block() const { return expiration_block_; }
ExpirationBlock& EquityAndIndexLastSaleMessage::expiration_block() { return expiration_block_; }
void EquityAndIndexLastSaleMessage::set_expiration_block(const ExpirationBlock& value) { expiration_block_ = value; }

StrikePriceDenominatorCode EquityAndIndexLastSaleMessage::strike_price_denominator_code() const { return strike_price_denominator_code_; }
void EquityAndIndexLastSaleMessage::set_strike_price_denominator_code(StrikePriceDenominatorCode value) { strike_price_denominator_code_ = value; }

Decimal EquityAndIndexLastSaleMessage::strike_price() const { return strike_price_; }
void EquityAndIndexLastSaleMessage::set_strike_price(Decimal value) { strike_price_ = value; }
int EquityAndIndexLastSaleMessage::strike_price_exponent(char code) {
    switch (code) {
        case 'A': return -1;
        case 'B': return -2;
        case 'C': return -3;
        case 'D': return -4;
        case 'E': return -5;
        case 'I': return 0;
        default: return 0;
    }
}

std::uint32_t EquityAndIndexLastSaleMessage::volume() const { return volume_; }
void EquityAndIndexLastSaleMessage::set_volume(std::uint32_t value) { volume_ = value; }

PremiumPriceDenominatorCode EquityAndIndexLastSaleMessage::premium_price_denominator_code() const { return premium_price_denominator_code_; }
void EquityAndIndexLastSaleMessage::set_premium_price_denominator_code(PremiumPriceDenominatorCode value) { premium_price_denominator_code_ = value; }

Decimal EquityAndIndexLastSaleMessage::premium_price() const { return premium_price_; }
void EquityAndIndexLastSaleMessage::set_premium_price(Decimal value) { premium_price_ = value; }
int EquityAndIndexLastSaleMessage::premium_price_exponent(char code) {
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

std::uint32_t EquityAndIndexLastSaleMessage::trade_identifier() const { return trade_identifier_; }
void EquityAndIndexLastSaleMessage::set_trade_identifier(std::uint32_t value) { trade_identifier_ = value; }

const std::array<std::byte, 4>& EquityAndIndexLastSaleMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& EquityAndIndexLastSaleMessage::reserved_4() { return reserved_4_; }
void EquityAndIndexLastSaleMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

EquityAndIndexLastSaleMessagePayloadCode EquityAndIndexLastSaleMessage::type() const { return type_; }
void EquityAndIndexLastSaleMessage::set_type(EquityAndIndexLastSaleMessagePayloadCode value) { type_ = value; }

std::string_view EquityAndIndexLastSaleMessage::name() const { return "Equity And Index Last Sale Message"; }

std::size_t EquityAndIndexLastSaleMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EquityAndIndexLastSaleMessage", wire_size, length);

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

    offset += expiration_block_.decode(data + offset, length - offset);

    strike_price_denominator_code_ = static_cast<StrikePriceDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), strike_price_exponent(static_cast<char>(strike_price_denominator_code_)));
    offset += 4;

    volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    premium_price_denominator_code_ = static_cast<PremiumPriceDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    premium_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), premium_price_exponent(static_cast<char>(premium_price_denominator_code_)));
    offset += 4;

    trade_identifier_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t EquityAndIndexLastSaleMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EquityAndIndexLastSaleMessage", wire_size, capacity);

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

    offset += expiration_block_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(strike_price_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(strike_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(premium_price_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(premium_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_identifier_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t EquityAndIndexLastSaleMessage::encoded_size() const {
    return wire_size;
}

void EquityAndIndexLastSaleMessage::accept(EquityAndIndexLastSaleMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<EquityAndIndexLastSaleMessagePayload> EquityAndIndexLastSaleMessage::clone() const {
    return std::make_unique<EquityAndIndexLastSaleMessage>(*this);
}

void EquityAndIndexLastSaleMessage::print(std::ostream& out) const {
    out << "EquityAndIndexLastSaleMessage{";
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
    out << ", expiration_block=";
    expiration_block_.print(out);
    out << ", strike_price_denominator_code=";
    out << strike_price_denominator_code_;
    out << ", strike_price=";
    out << strike_price_;
    out << ", volume=";
    out << volume_;
    out << ", premium_price_denominator_code=";
    out << premium_price_denominator_code_;
    out << ", premium_price=";
    out << premium_price_;
    out << ", trade_identifier=";
    out << trade_identifier_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << '}';
}

bool EquityAndIndexLastSaleMessage::equals(const EquityAndIndexLastSaleMessagePayload& other) const {
    const auto* that = dynamic_cast<const EquityAndIndexLastSaleMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EquityAndIndexLastSaleMessage::operator==(const EquityAndIndexLastSaleMessage& other) const {
    return message_indicator_ == other.message_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && reserved_1_ == other.reserved_1_
        && expiration_block_ == other.expiration_block_
        && strike_price_denominator_code_ == other.strike_price_denominator_code_
        && strike_price_ == other.strike_price_
        && volume_ == other.volume_
        && premium_price_denominator_code_ == other.premium_price_denominator_code_
        && premium_price_ == other.premium_price_
        && trade_identifier_ == other.trade_identifier_
        && reserved_4_ == other.reserved_4_
        && type_ == other.type_;
}

bool EquityAndIndexLastSaleMessage::operator!=(const EquityAndIndexLastSaleMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
