#include "ConsolidatedEndOfDaySummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v1_91 {

ConsolidatedEndOfDaySummaryMessage::ConsolidatedEndOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, LastParticipantId last_participant_id, std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, std::uint64_t total_volume, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, std::uint8_t number_of_participants)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), last_participant_id_(last_participant_id), previous_close_price_date_(previous_close_price_date), last_price_(last_price), high_price_(high_price), low_price_(low_price), total_volume_(total_volume), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), number_of_participants_(number_of_participants) {}

ParticipantId ConsolidatedEndOfDaySummaryMessage::participant_id() const { return participant_id_; }
void ConsolidatedEndOfDaySummaryMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& ConsolidatedEndOfDaySummaryMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& ConsolidatedEndOfDaySummaryMessage::timestamp_1() { return timestamp_1_; }
void ConsolidatedEndOfDaySummaryMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t ConsolidatedEndOfDaySummaryMessage::message_id() const { return message_id_; }
void ConsolidatedEndOfDaySummaryMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t ConsolidatedEndOfDaySummaryMessage::transaction_id() const { return transaction_id_; }
void ConsolidatedEndOfDaySummaryMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t ConsolidatedEndOfDaySummaryMessage::participant_reference_number() const { return participant_reference_number_; }
void ConsolidatedEndOfDaySummaryMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& ConsolidatedEndOfDaySummaryMessage::security_symbol() const { return security_symbol_; }
std::string& ConsolidatedEndOfDaySummaryMessage::security_symbol() { return security_symbol_; }
void ConsolidatedEndOfDaySummaryMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType ConsolidatedEndOfDaySummaryMessage::instrument_type() const { return instrument_type_; }
void ConsolidatedEndOfDaySummaryMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

LastParticipantId ConsolidatedEndOfDaySummaryMessage::last_participant_id() const { return last_participant_id_; }
void ConsolidatedEndOfDaySummaryMessage::set_last_participant_id(LastParticipantId value) { last_participant_id_ = value; }

std::uint32_t ConsolidatedEndOfDaySummaryMessage::previous_close_price_date() const { return previous_close_price_date_; }
void ConsolidatedEndOfDaySummaryMessage::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

Decimal ConsolidatedEndOfDaySummaryMessage::last_price() const { return last_price_; }
void ConsolidatedEndOfDaySummaryMessage::set_last_price(Decimal value) { last_price_ = value; }

Decimal ConsolidatedEndOfDaySummaryMessage::high_price() const { return high_price_; }
void ConsolidatedEndOfDaySummaryMessage::set_high_price(Decimal value) { high_price_ = value; }

Decimal ConsolidatedEndOfDaySummaryMessage::low_price() const { return low_price_; }
void ConsolidatedEndOfDaySummaryMessage::set_low_price(Decimal value) { low_price_ = value; }

std::uint64_t ConsolidatedEndOfDaySummaryMessage::total_volume() const { return total_volume_; }
void ConsolidatedEndOfDaySummaryMessage::set_total_volume(std::uint64_t value) { total_volume_ = value; }

ShortSaleRestrictionIndicator ConsolidatedEndOfDaySummaryMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void ConsolidatedEndOfDaySummaryMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId ConsolidatedEndOfDaySummaryMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void ConsolidatedEndOfDaySummaryMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator ConsolidatedEndOfDaySummaryMessage::financial_status_indicator() const { return financial_status_indicator_; }
void ConsolidatedEndOfDaySummaryMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

std::uint8_t ConsolidatedEndOfDaySummaryMessage::number_of_participants() const { return number_of_participants_; }
void ConsolidatedEndOfDaySummaryMessage::set_number_of_participants(std::uint8_t value) { number_of_participants_ = value; }

SummaryMessagePayloadCode ConsolidatedEndOfDaySummaryMessage::type() const { return message_type; }

std::string_view ConsolidatedEndOfDaySummaryMessage::name() const { return "Consolidated End Of Day Summary Message"; }

std::size_t ConsolidatedEndOfDaySummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ConsolidatedEndOfDaySummaryMessage", wire_size, length);

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

    instrument_type_ = static_cast<InstrumentType>(wire::read_char(data + offset));
    offset += 1;

    last_participant_id_ = static_cast<LastParticipantId>(wire::read_char(data + offset));
    offset += 1;

    previous_close_price_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    total_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    number_of_participants_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t ConsolidatedEndOfDaySummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ConsolidatedEndOfDaySummaryMessage", wire_size, capacity);

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

    wire::write_char(data + offset, static_cast<char>(instrument_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(last_participant_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(previous_close_price_date_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(high_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(low_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(total_volume_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_participants_));
    offset += 1;

    return offset;
}

std::size_t ConsolidatedEndOfDaySummaryMessage::encoded_size() const {
    return wire_size;
}

void ConsolidatedEndOfDaySummaryMessage::accept(SummaryMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SummaryMessagePayload> ConsolidatedEndOfDaySummaryMessage::clone() const {
    return std::make_unique<ConsolidatedEndOfDaySummaryMessage>(*this);
}

void ConsolidatedEndOfDaySummaryMessage::print(std::ostream& out) const {
    out << "ConsolidatedEndOfDaySummaryMessage{";
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
    out << ", instrument_type=";
    out << instrument_type_;
    out << ", last_participant_id=";
    out << last_participant_id_;
    out << ", previous_close_price_date=";
    out << previous_close_price_date_;
    out << ", last_price=";
    out << last_price_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", total_volume=";
    out << total_volume_;
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", number_of_participants=";
    out << static_cast<int>(number_of_participants_);
    out << '}';
}

bool ConsolidatedEndOfDaySummaryMessage::equals(const SummaryMessagePayload& other) const {
    const auto* that = dynamic_cast<const ConsolidatedEndOfDaySummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ConsolidatedEndOfDaySummaryMessage::operator==(const ConsolidatedEndOfDaySummaryMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && last_participant_id_ == other.last_participant_id_
        && previous_close_price_date_ == other.previous_close_price_date_
        && last_price_ == other.last_price_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && total_volume_ == other.total_volume_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && number_of_participants_ == other.number_of_participants_;
}

bool ConsolidatedEndOfDaySummaryMessage::operator!=(const ConsolidatedEndOfDaySummaryMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v1_91
