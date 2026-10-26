#include "EquityAndIndexEndOfDaySummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

EquityAndIndexEndOfDaySummaryMessage::EquityAndIndexEndOfDaySummaryMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, const std::string& security_symbol, const std::array<std::byte, 1>& reserved_1, const ExpirationBlock& expiration_block, StrikePriceDenominatorCode strike_price_denominator_code, Decimal strike_price, std::uint32_t volume, std::uint32_t open_interest_volume, PremiumPriceDenominatorCode premium_price_denominator_code, std::int32_t open_price, std::int32_t high_price, std::int32_t low_price, std::int32_t last_price, std::int32_t net_change, UnderlyingPriceDenominatorCode underlying_price_denominator_code, Decimal underlying_price, std::int32_t bid_price, std::int32_t offer_price)
  : message_indicator_(message_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), reserved_1_(reserved_1), expiration_block_(expiration_block), strike_price_denominator_code_(strike_price_denominator_code), strike_price_(strike_price), volume_(volume), open_interest_volume_(open_interest_volume), premium_price_denominator_code_(premium_price_denominator_code), open_price_(open_price), high_price_(high_price), low_price_(low_price), last_price_(last_price), net_change_(net_change), underlying_price_denominator_code_(underlying_price_denominator_code), underlying_price_(underlying_price), bid_price_(bid_price), offer_price_(offer_price) {}

char EquityAndIndexEndOfDaySummaryMessage::message_indicator() const { return message_indicator_; }
void EquityAndIndexEndOfDaySummaryMessage::set_message_indicator(char value) { message_indicator_ = value; }

std::uint32_t EquityAndIndexEndOfDaySummaryMessage::transaction_id() const { return transaction_id_; }
void EquityAndIndexEndOfDaySummaryMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t EquityAndIndexEndOfDaySummaryMessage::participant_reference_number() const { return participant_reference_number_; }
void EquityAndIndexEndOfDaySummaryMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

const std::string& EquityAndIndexEndOfDaySummaryMessage::security_symbol() const { return security_symbol_; }
std::string& EquityAndIndexEndOfDaySummaryMessage::security_symbol() { return security_symbol_; }
void EquityAndIndexEndOfDaySummaryMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::array<std::byte, 1>& EquityAndIndexEndOfDaySummaryMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& EquityAndIndexEndOfDaySummaryMessage::reserved_1() { return reserved_1_; }
void EquityAndIndexEndOfDaySummaryMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

const ExpirationBlock& EquityAndIndexEndOfDaySummaryMessage::expiration_block() const { return expiration_block_; }
ExpirationBlock& EquityAndIndexEndOfDaySummaryMessage::expiration_block() { return expiration_block_; }
void EquityAndIndexEndOfDaySummaryMessage::set_expiration_block(const ExpirationBlock& value) { expiration_block_ = value; }

StrikePriceDenominatorCode EquityAndIndexEndOfDaySummaryMessage::strike_price_denominator_code() const { return strike_price_denominator_code_; }
void EquityAndIndexEndOfDaySummaryMessage::set_strike_price_denominator_code(StrikePriceDenominatorCode value) { strike_price_denominator_code_ = value; }

Decimal EquityAndIndexEndOfDaySummaryMessage::strike_price() const { return strike_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_strike_price(Decimal value) { strike_price_ = value; }
int EquityAndIndexEndOfDaySummaryMessage::strike_price_exponent(char code) {
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

std::uint32_t EquityAndIndexEndOfDaySummaryMessage::volume() const { return volume_; }
void EquityAndIndexEndOfDaySummaryMessage::set_volume(std::uint32_t value) { volume_ = value; }

std::uint32_t EquityAndIndexEndOfDaySummaryMessage::open_interest_volume() const { return open_interest_volume_; }
void EquityAndIndexEndOfDaySummaryMessage::set_open_interest_volume(std::uint32_t value) { open_interest_volume_ = value; }

PremiumPriceDenominatorCode EquityAndIndexEndOfDaySummaryMessage::premium_price_denominator_code() const { return premium_price_denominator_code_; }
void EquityAndIndexEndOfDaySummaryMessage::set_premium_price_denominator_code(PremiumPriceDenominatorCode value) { premium_price_denominator_code_ = value; }

std::int32_t EquityAndIndexEndOfDaySummaryMessage::open_price() const { return open_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_open_price(std::int32_t value) { open_price_ = value; }

std::int32_t EquityAndIndexEndOfDaySummaryMessage::high_price() const { return high_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_high_price(std::int32_t value) { high_price_ = value; }

std::int32_t EquityAndIndexEndOfDaySummaryMessage::low_price() const { return low_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_low_price(std::int32_t value) { low_price_ = value; }

std::int32_t EquityAndIndexEndOfDaySummaryMessage::last_price() const { return last_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_last_price(std::int32_t value) { last_price_ = value; }

std::int32_t EquityAndIndexEndOfDaySummaryMessage::net_change() const { return net_change_; }
void EquityAndIndexEndOfDaySummaryMessage::set_net_change(std::int32_t value) { net_change_ = value; }

UnderlyingPriceDenominatorCode EquityAndIndexEndOfDaySummaryMessage::underlying_price_denominator_code() const { return underlying_price_denominator_code_; }
void EquityAndIndexEndOfDaySummaryMessage::set_underlying_price_denominator_code(UnderlyingPriceDenominatorCode value) { underlying_price_denominator_code_ = value; }

Decimal EquityAndIndexEndOfDaySummaryMessage::underlying_price() const { return underlying_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_underlying_price(Decimal value) { underlying_price_ = value; }
int EquityAndIndexEndOfDaySummaryMessage::underlying_price_exponent(char code) {
    switch (code) {
        case 'A': return -1;
        case 'B': return -2;
        case 'C': return -3;
        case 'D': return -4;
        case 'E': return -5;
        case 'F': return -6;
        case 'G': return -7;
        case 'H': return -8;
        case 'I': return 0;
        default: return 0;
    }
}

std::int32_t EquityAndIndexEndOfDaySummaryMessage::bid_price() const { return bid_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_bid_price(std::int32_t value) { bid_price_ = value; }

std::int32_t EquityAndIndexEndOfDaySummaryMessage::offer_price() const { return offer_price_; }
void EquityAndIndexEndOfDaySummaryMessage::set_offer_price(std::int32_t value) { offer_price_ = value; }

EquityAndIndexEndOfDaySummaryMessagePayloadCode EquityAndIndexEndOfDaySummaryMessage::type() const { return message_type; }

std::string_view EquityAndIndexEndOfDaySummaryMessage::name() const { return "Equity And Index End Of Day Summary Message"; }

std::size_t EquityAndIndexEndOfDaySummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EquityAndIndexEndOfDaySummaryMessage", wire_size, length);

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

    open_interest_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    premium_price_denominator_code_ = static_cast<PremiumPriceDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    open_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    high_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    low_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    last_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    net_change_ = wire::read_i32_be(data + offset);
    offset += 4;

    underlying_price_denominator_code_ = static_cast<UnderlyingPriceDenominatorCode>(wire::read_char(data + offset));
    offset += 1;

    underlying_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), underlying_price_exponent(static_cast<char>(underlying_price_denominator_code_)));
    offset += 8;

    bid_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    offer_price_ = wire::read_i32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t EquityAndIndexEndOfDaySummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EquityAndIndexEndOfDaySummaryMessage", wire_size, capacity);

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

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(open_interest_volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(premium_price_denominator_code_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(open_price_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(high_price_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(low_price_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(last_price_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(net_change_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(underlying_price_denominator_code_));
    offset += 1;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(underlying_price_.mantissa()));
    offset += 8;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(bid_price_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(offer_price_));
    offset += 4;

    return offset;
}

std::size_t EquityAndIndexEndOfDaySummaryMessage::encoded_size() const {
    return wire_size;
}

void EquityAndIndexEndOfDaySummaryMessage::accept(EquityAndIndexEndOfDaySummaryMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> EquityAndIndexEndOfDaySummaryMessage::clone() const {
    return std::make_unique<EquityAndIndexEndOfDaySummaryMessage>(*this);
}

void EquityAndIndexEndOfDaySummaryMessage::print(std::ostream& out) const {
    out << "EquityAndIndexEndOfDaySummaryMessage{";
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
    out << ", open_interest_volume=";
    out << open_interest_volume_;
    out << ", premium_price_denominator_code=";
    out << premium_price_denominator_code_;
    out << ", open_price=";
    out << open_price_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", last_price=";
    out << last_price_;
    out << ", net_change=";
    out << net_change_;
    out << ", underlying_price_denominator_code=";
    out << underlying_price_denominator_code_;
    out << ", underlying_price=";
    out << underlying_price_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", offer_price=";
    out << offer_price_;
    out << '}';
}

bool EquityAndIndexEndOfDaySummaryMessage::equals(const EquityAndIndexEndOfDaySummaryMessagePayload& other) const {
    const auto* that = dynamic_cast<const EquityAndIndexEndOfDaySummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EquityAndIndexEndOfDaySummaryMessage::operator==(const EquityAndIndexEndOfDaySummaryMessage& other) const {
    return message_indicator_ == other.message_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && reserved_1_ == other.reserved_1_
        && expiration_block_ == other.expiration_block_
        && strike_price_denominator_code_ == other.strike_price_denominator_code_
        && strike_price_ == other.strike_price_
        && volume_ == other.volume_
        && open_interest_volume_ == other.open_interest_volume_
        && premium_price_denominator_code_ == other.premium_price_denominator_code_
        && open_price_ == other.open_price_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && last_price_ == other.last_price_
        && net_change_ == other.net_change_
        && underlying_price_denominator_code_ == other.underlying_price_denominator_code_
        && underlying_price_ == other.underlying_price_
        && bid_price_ == other.bid_price_
        && offer_price_ == other.offer_price_;
}

bool EquityAndIndexEndOfDaySummaryMessage::operator!=(const EquityAndIndexEndOfDaySummaryMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
