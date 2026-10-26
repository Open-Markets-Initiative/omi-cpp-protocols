#include "FractionalConsolidatedEndOfDaySummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

FractionalConsolidatedEndOfDaySummaryMessage::FractionalConsolidatedEndOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, char last_participant_id, std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, Decimal fractional_total_volume, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, std::uint8_t number_of_participants)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), last_participant_id_(last_participant_id), previous_close_price_date_(previous_close_price_date), last_price_(last_price), high_price_(high_price), low_price_(low_price), fractional_total_volume_(fractional_total_volume), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), number_of_participants_(number_of_participants) {}

ParticipantId FractionalConsolidatedEndOfDaySummaryMessage::participant_id() const { return participant_id_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& FractionalConsolidatedEndOfDaySummaryMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& FractionalConsolidatedEndOfDaySummaryMessage::timestamp_1() { return timestamp_1_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t FractionalConsolidatedEndOfDaySummaryMessage::message_id() const { return message_id_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t FractionalConsolidatedEndOfDaySummaryMessage::transaction_id() const { return transaction_id_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t FractionalConsolidatedEndOfDaySummaryMessage::participant_reference_number() const { return participant_reference_number_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& FractionalConsolidatedEndOfDaySummaryMessage::security_symbol() const { return security_symbol_; }
std::string& FractionalConsolidatedEndOfDaySummaryMessage::security_symbol() { return security_symbol_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType FractionalConsolidatedEndOfDaySummaryMessage::instrument_type() const { return instrument_type_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

char FractionalConsolidatedEndOfDaySummaryMessage::last_participant_id() const { return last_participant_id_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_last_participant_id(char value) { last_participant_id_ = value; }

std::uint32_t FractionalConsolidatedEndOfDaySummaryMessage::previous_close_price_date() const { return previous_close_price_date_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

Decimal FractionalConsolidatedEndOfDaySummaryMessage::last_price() const { return last_price_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_last_price(Decimal value) { last_price_ = value; }

Decimal FractionalConsolidatedEndOfDaySummaryMessage::high_price() const { return high_price_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_high_price(Decimal value) { high_price_ = value; }

Decimal FractionalConsolidatedEndOfDaySummaryMessage::low_price() const { return low_price_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_low_price(Decimal value) { low_price_ = value; }

Decimal FractionalConsolidatedEndOfDaySummaryMessage::fractional_total_volume() const { return fractional_total_volume_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_fractional_total_volume(Decimal value) { fractional_total_volume_ = value; }

ShortSaleRestrictionIndicator FractionalConsolidatedEndOfDaySummaryMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId FractionalConsolidatedEndOfDaySummaryMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator FractionalConsolidatedEndOfDaySummaryMessage::financial_status_indicator() const { return financial_status_indicator_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

std::uint8_t FractionalConsolidatedEndOfDaySummaryMessage::number_of_participants() const { return number_of_participants_; }
void FractionalConsolidatedEndOfDaySummaryMessage::set_number_of_participants(std::uint8_t value) { number_of_participants_ = value; }

SummaryMessagePayloadCode FractionalConsolidatedEndOfDaySummaryMessage::type() const { return message_type; }

std::string_view FractionalConsolidatedEndOfDaySummaryMessage::name() const { return "Fractional Consolidated End Of Day Summary Message"; }

std::size_t FractionalConsolidatedEndOfDaySummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FractionalConsolidatedEndOfDaySummaryMessage", wire_size, length);

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

    last_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    previous_close_price_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    fractional_total_volume_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
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

std::size_t FractionalConsolidatedEndOfDaySummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalConsolidatedEndOfDaySummaryMessage", wire_size, capacity);

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

    wire::write_char(data + offset, last_participant_id_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(previous_close_price_date_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(high_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(low_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_total_volume_.mantissa()));
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

std::size_t FractionalConsolidatedEndOfDaySummaryMessage::encoded_size() const {
    return wire_size;
}

void FractionalConsolidatedEndOfDaySummaryMessage::accept(SummaryMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SummaryMessagePayload> FractionalConsolidatedEndOfDaySummaryMessage::clone() const {
    return std::make_unique<FractionalConsolidatedEndOfDaySummaryMessage>(*this);
}

void FractionalConsolidatedEndOfDaySummaryMessage::print(std::ostream& out) const {
    out << "FractionalConsolidatedEndOfDaySummaryMessage{";
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
    print::character(out, last_participant_id_);
    out << ", previous_close_price_date=";
    out << previous_close_price_date_;
    out << ", last_price=";
    out << last_price_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", fractional_total_volume=";
    out << fractional_total_volume_;
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

bool FractionalConsolidatedEndOfDaySummaryMessage::equals(const SummaryMessagePayload& other) const {
    const auto* that = dynamic_cast<const FractionalConsolidatedEndOfDaySummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FractionalConsolidatedEndOfDaySummaryMessage::operator==(const FractionalConsolidatedEndOfDaySummaryMessage& other) const {
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
        && fractional_total_volume_ == other.fractional_total_volume_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && number_of_participants_ == other.number_of_participants_;
}

bool FractionalConsolidatedEndOfDaySummaryMessage::operator!=(const FractionalConsolidatedEndOfDaySummaryMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
