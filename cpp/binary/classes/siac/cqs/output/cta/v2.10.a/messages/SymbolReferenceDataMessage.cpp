#include "SymbolReferenceDataMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v2_10_a {

SymbolReferenceDataMessage::SymbolReferenceDataMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, const std::string& prior_security_symbol, PrimaryListingMarketParticipantId primary_listing_market_participant_id, Decimal primary_listing_market_previous_closing_price, Decimal consolidated_closing_price, std::uint16_t round_lot_size, char reserved, LuldTier luld_tier, Decimal luld_leverage_ratio, Test test, Ipo ipo, FinancialStatusIndicator financial_status_indicator, ShortSaleRestrictionIndicator short_sale_restriction_indicator, char halt_reason, InstrumentType instrument_type, char second_reserved, char third_reserved, const std::string& reserved_128)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), prior_security_symbol_(prior_security_symbol), primary_listing_market_participant_id_(primary_listing_market_participant_id), primary_listing_market_previous_closing_price_(primary_listing_market_previous_closing_price), consolidated_closing_price_(consolidated_closing_price), round_lot_size_(round_lot_size), reserved_(reserved), luld_tier_(luld_tier), luld_leverage_ratio_(luld_leverage_ratio), test_(test), ipo_(ipo), financial_status_indicator_(financial_status_indicator), short_sale_restriction_indicator_(short_sale_restriction_indicator), halt_reason_(halt_reason), instrument_type_(instrument_type), second_reserved_(second_reserved), third_reserved_(third_reserved), reserved_128_(reserved_128) {}

ParticipantId SymbolReferenceDataMessage::participant_id() const { return participant_id_; }
void SymbolReferenceDataMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& SymbolReferenceDataMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& SymbolReferenceDataMessage::timestamp_1() { return timestamp_1_; }
void SymbolReferenceDataMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t SymbolReferenceDataMessage::message_id() const { return message_id_; }
void SymbolReferenceDataMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t SymbolReferenceDataMessage::transaction_id() const { return transaction_id_; }
void SymbolReferenceDataMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t SymbolReferenceDataMessage::participant_reference_number() const { return participant_reference_number_; }
void SymbolReferenceDataMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& SymbolReferenceDataMessage::security_symbol() const { return security_symbol_; }
std::string& SymbolReferenceDataMessage::security_symbol() { return security_symbol_; }
void SymbolReferenceDataMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

const std::string& SymbolReferenceDataMessage::prior_security_symbol() const { return prior_security_symbol_; }
std::string& SymbolReferenceDataMessage::prior_security_symbol() { return prior_security_symbol_; }
void SymbolReferenceDataMessage::set_prior_security_symbol(const std::string& value) { prior_security_symbol_ = value; }

PrimaryListingMarketParticipantId SymbolReferenceDataMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void SymbolReferenceDataMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

Decimal SymbolReferenceDataMessage::primary_listing_market_previous_closing_price() const { return primary_listing_market_previous_closing_price_; }
void SymbolReferenceDataMessage::set_primary_listing_market_previous_closing_price(Decimal value) { primary_listing_market_previous_closing_price_ = value; }

Decimal SymbolReferenceDataMessage::consolidated_closing_price() const { return consolidated_closing_price_; }
void SymbolReferenceDataMessage::set_consolidated_closing_price(Decimal value) { consolidated_closing_price_ = value; }

std::uint16_t SymbolReferenceDataMessage::round_lot_size() const { return round_lot_size_; }
void SymbolReferenceDataMessage::set_round_lot_size(std::uint16_t value) { round_lot_size_ = value; }

char SymbolReferenceDataMessage::reserved() const { return reserved_; }
void SymbolReferenceDataMessage::set_reserved(char value) { reserved_ = value; }

LuldTier SymbolReferenceDataMessage::luld_tier() const { return luld_tier_; }
void SymbolReferenceDataMessage::set_luld_tier(LuldTier value) { luld_tier_ = value; }

Decimal SymbolReferenceDataMessage::luld_leverage_ratio() const { return luld_leverage_ratio_; }
void SymbolReferenceDataMessage::set_luld_leverage_ratio(Decimal value) { luld_leverage_ratio_ = value; }

Test SymbolReferenceDataMessage::test() const { return test_; }
void SymbolReferenceDataMessage::set_test(Test value) { test_ = value; }

Ipo SymbolReferenceDataMessage::ipo() const { return ipo_; }
void SymbolReferenceDataMessage::set_ipo(Ipo value) { ipo_ = value; }

FinancialStatusIndicator SymbolReferenceDataMessage::financial_status_indicator() const { return financial_status_indicator_; }
void SymbolReferenceDataMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

ShortSaleRestrictionIndicator SymbolReferenceDataMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void SymbolReferenceDataMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

char SymbolReferenceDataMessage::halt_reason() const { return halt_reason_; }
void SymbolReferenceDataMessage::set_halt_reason(char value) { halt_reason_ = value; }

InstrumentType SymbolReferenceDataMessage::instrument_type() const { return instrument_type_; }
void SymbolReferenceDataMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

char SymbolReferenceDataMessage::second_reserved() const { return second_reserved_; }
void SymbolReferenceDataMessage::set_second_reserved(char value) { second_reserved_ = value; }

char SymbolReferenceDataMessage::third_reserved() const { return third_reserved_; }
void SymbolReferenceDataMessage::set_third_reserved(char value) { third_reserved_ = value; }

const std::string& SymbolReferenceDataMessage::reserved_128() const { return reserved_128_; }
std::string& SymbolReferenceDataMessage::reserved_128() { return reserved_128_; }
void SymbolReferenceDataMessage::set_reserved_128(const std::string& value) { reserved_128_ = value; }

AdministrativeMessagePayloadCode SymbolReferenceDataMessage::type() const { return message_type; }

std::string_view SymbolReferenceDataMessage::name() const { return "Symbol Reference Data Message"; }

std::size_t SymbolReferenceDataMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolReferenceDataMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    security_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    prior_security_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    primary_listing_market_previous_closing_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    consolidated_closing_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    round_lot_size_ = wire::read_u16_be(data + offset);
    offset += 2;

    reserved_ = wire::read_char(data + offset);
    offset += 1;

    luld_tier_ = static_cast<LuldTier>(wire::read_char(data + offset));
    offset += 1;

    luld_leverage_ratio_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -6);
    offset += 4;

    test_ = static_cast<Test>(wire::read_char(data + offset));
    offset += 1;

    ipo_ = static_cast<Ipo>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    halt_reason_ = wire::read_char(data + offset);
    offset += 1;

    instrument_type_ = static_cast<InstrumentType>(wire::read_char(data + offset));
    offset += 1;

    second_reserved_ = wire::read_char(data + offset);
    offset += 1;

    third_reserved_ = wire::read_char(data + offset);
    offset += 1;

    reserved_128_ = wire::read_text(data + offset, 128, ' ');
    offset += 128;

    return offset;
}

std::size_t SymbolReferenceDataMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolReferenceDataMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_text(data + offset, 11, ' ', security_symbol_);
    offset += 11;

    wire::write_text(data + offset, 11, ' ', prior_security_symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(primary_listing_market_previous_closing_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_closing_price_.mantissa()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(round_lot_size_));
    offset += 2;

    wire::write_char(data + offset, reserved_);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(luld_tier_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(luld_leverage_ratio_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(test_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(ipo_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, halt_reason_);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(instrument_type_));
    offset += 1;

    wire::write_char(data + offset, second_reserved_);
    offset += 1;

    wire::write_char(data + offset, third_reserved_);
    offset += 1;

    wire::write_text(data + offset, 128, ' ', reserved_128_);
    offset += 128;

    return offset;
}

std::size_t SymbolReferenceDataMessage::encoded_size() const {
    return wire_size;
}

void SymbolReferenceDataMessage::accept(AdministrativeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<AdministrativeMessagePayload> SymbolReferenceDataMessage::clone() const {
    return std::make_unique<SymbolReferenceDataMessage>(*this);
}

void SymbolReferenceDataMessage::print(std::ostream& out) const {
    out << "SymbolReferenceDataMessage{";
    out << "participant_id=";
    out << participant_id_;
    out << ", timestamp_1=";
    timestamp_1_.print(out);
    out << ", message_id=";
    out << static_cast<int>(message_id_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", prior_security_symbol=";
    print::text(out, prior_security_symbol_);
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", primary_listing_market_previous_closing_price=";
    out << primary_listing_market_previous_closing_price_;
    out << ", consolidated_closing_price=";
    out << consolidated_closing_price_;
    out << ", round_lot_size=";
    out << round_lot_size_;
    out << ", reserved=";
    print::character(out, reserved_);
    out << ", luld_tier=";
    out << luld_tier_;
    out << ", luld_leverage_ratio=";
    out << luld_leverage_ratio_;
    out << ", test=";
    out << test_;
    out << ", ipo=";
    out << ipo_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", halt_reason=";
    print::character(out, halt_reason_);
    out << ", instrument_type=";
    out << instrument_type_;
    out << ", second_reserved=";
    print::character(out, second_reserved_);
    out << ", third_reserved=";
    print::character(out, third_reserved_);
    out << ", reserved_128=";
    print::text(out, reserved_128_);
    out << '}';
}

bool SymbolReferenceDataMessage::equals(const AdministrativeMessagePayload& other) const {
    const auto* that = dynamic_cast<const SymbolReferenceDataMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolReferenceDataMessage::operator==(const SymbolReferenceDataMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && prior_security_symbol_ == other.prior_security_symbol_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && primary_listing_market_previous_closing_price_ == other.primary_listing_market_previous_closing_price_
        && consolidated_closing_price_ == other.consolidated_closing_price_
        && round_lot_size_ == other.round_lot_size_
        && reserved_ == other.reserved_
        && luld_tier_ == other.luld_tier_
        && luld_leverage_ratio_ == other.luld_leverage_ratio_
        && test_ == other.test_
        && ipo_ == other.ipo_
        && financial_status_indicator_ == other.financial_status_indicator_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && halt_reason_ == other.halt_reason_
        && instrument_type_ == other.instrument_type_
        && second_reserved_ == other.second_reserved_
        && third_reserved_ == other.third_reserved_
        && reserved_128_ == other.reserved_128_;
}

bool SymbolReferenceDataMessage::operator!=(const SymbolReferenceDataMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cqs::output::cta::v2_10_a
