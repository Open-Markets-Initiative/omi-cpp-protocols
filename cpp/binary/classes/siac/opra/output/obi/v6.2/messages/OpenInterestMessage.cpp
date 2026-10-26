#include "OpenInterestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

OpenInterestMessage::OpenInterestMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, std::uint32_t open_interest_volume)
  : message_indicator_(message_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), reserved_1_(reserved_1), expiration_block_(expiration_block), strike_price_denominator_code_(strike_price_denominator_code), strike_price_(strike_price), open_interest_volume_(open_interest_volume) {}

char OpenInterestMessage::message_indicator() const { return message_indicator_; }
void OpenInterestMessage::set_message_indicator(char value) { message_indicator_ = value; }

std::uint32_t OpenInterestMessage::transaction_id() const { return transaction_id_; }
void OpenInterestMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t OpenInterestMessage::participant_reference_number() const { return participant_reference_number_; }
void OpenInterestMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

const std::string& OpenInterestMessage::security_symbol() const { return security_symbol_; }
std::string& OpenInterestMessage::security_symbol() { return security_symbol_; }
void OpenInterestMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::array<std::byte, 1>& OpenInterestMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& OpenInterestMessage::reserved_1() { return reserved_1_; }
void OpenInterestMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const ExpirationBlock& OpenInterestMessage::expiration_block() const { return expiration_block_; }
ExpirationBlock& OpenInterestMessage::expiration_block() { return expiration_block_; }
void OpenInterestMessage::set_expiration_block(const ExpirationBlock& value) { expiration_block_ = value; }

StrikePriceDenominatorCode OpenInterestMessage::strike_price_denominator_code() const { return strike_price_denominator_code_; }
void OpenInterestMessage::set_strike_price_denominator_code(StrikePriceDenominatorCode value) { strike_price_denominator_code_ = value; }

Decimal OpenInterestMessage::strike_price() const { return strike_price_; }
void OpenInterestMessage::set_strike_price(Decimal value) { strike_price_ = value; }
int OpenInterestMessage::strike_price_exponent(char code) {
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

std::uint32_t OpenInterestMessage::open_interest_volume() const { return open_interest_volume_; }
void OpenInterestMessage::set_open_interest_volume(std::uint32_t value) { open_interest_volume_ = value; }

OpenInterestMessagePayloadCode OpenInterestMessage::type() const { return message_type; }

std::string_view OpenInterestMessage::name() const { return "Open Interest Message"; }

std::size_t OpenInterestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OpenInterestMessage", wire_size, length);

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

    open_interest_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OpenInterestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OpenInterestMessage", wire_size, capacity);

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

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(open_interest_volume_));
    offset += 4;

    return offset;
}

std::size_t OpenInterestMessage::encoded_size() const {
    return wire_size;
}

void OpenInterestMessage::accept(OpenInterestMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<OpenInterestMessagePayload> OpenInterestMessage::clone() const {
    return std::make_unique<OpenInterestMessage>(*this);
}

void OpenInterestMessage::print(std::ostream& out) const {
    out << "OpenInterestMessage{";
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
    out << ", open_interest_volume=";
    out << open_interest_volume_;
    out << '}';
}

bool OpenInterestMessage::equals(const OpenInterestMessagePayload& other) const {
    const auto* that = dynamic_cast<const OpenInterestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OpenInterestMessage::operator==(const OpenInterestMessage& other) const {
    return message_indicator_ == other.message_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && reserved_1_ == other.reserved_1_
        && expiration_block_ == other.expiration_block_
        && strike_price_denominator_code_ == other.strike_price_denominator_code_
        && strike_price_ == other.strike_price_
        && open_interest_volume_ == other.open_interest_volume_;
}

bool OpenInterestMessage::operator!=(const OpenInterestMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
