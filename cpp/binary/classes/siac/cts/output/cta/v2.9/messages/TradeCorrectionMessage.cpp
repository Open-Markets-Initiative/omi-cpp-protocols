#include "TradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_9 {

TradeCorrectionMessage::TradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const CorrectedTrade& corrected_trade, TradeReportingFacilityId trade_reporting_facility_id, const Timestamp2& timestamp_2, std::int64_t original_participant_reference_number, const OriginalTrade& original_trade, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, const ConsolidatedData& consolidated_data, const ParticipantData& participant_data)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), corrected_trade_(corrected_trade), trade_reporting_facility_id_(trade_reporting_facility_id), timestamp_2_(timestamp_2), original_participant_reference_number_(original_participant_reference_number), original_trade_(original_trade), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), consolidated_data_(consolidated_data), participant_data_(participant_data) {}

ParticipantId TradeCorrectionMessage::participant_id() const { return participant_id_; }
void TradeCorrectionMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& TradeCorrectionMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& TradeCorrectionMessage::timestamp_1() { return timestamp_1_; }
void TradeCorrectionMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t TradeCorrectionMessage::message_id() const { return message_id_; }
void TradeCorrectionMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t TradeCorrectionMessage::transaction_id() const { return transaction_id_; }
void TradeCorrectionMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t TradeCorrectionMessage::participant_reference_number() const { return participant_reference_number_; }
void TradeCorrectionMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& TradeCorrectionMessage::security_symbol() const { return security_symbol_; }
std::string& TradeCorrectionMessage::security_symbol() { return security_symbol_; }
void TradeCorrectionMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType TradeCorrectionMessage::instrument_type() const { return instrument_type_; }
void TradeCorrectionMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

const CorrectedTrade& TradeCorrectionMessage::corrected_trade() const { return corrected_trade_; }
CorrectedTrade& TradeCorrectionMessage::corrected_trade() { return corrected_trade_; }
void TradeCorrectionMessage::set_corrected_trade(const CorrectedTrade& value) { corrected_trade_ = value; }

TradeReportingFacilityId TradeCorrectionMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void TradeCorrectionMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

const Timestamp2& TradeCorrectionMessage::timestamp_2() const { return timestamp_2_; }
Timestamp2& TradeCorrectionMessage::timestamp_2() { return timestamp_2_; }
void TradeCorrectionMessage::set_timestamp_2(const Timestamp2& value) { timestamp_2_ = value; }

std::int64_t TradeCorrectionMessage::original_participant_reference_number() const { return original_participant_reference_number_; }
void TradeCorrectionMessage::set_original_participant_reference_number(std::int64_t value) { original_participant_reference_number_ = value; }

const OriginalTrade& TradeCorrectionMessage::original_trade() const { return original_trade_; }
OriginalTrade& TradeCorrectionMessage::original_trade() { return original_trade_; }
void TradeCorrectionMessage::set_original_trade(const OriginalTrade& value) { original_trade_ = value; }

PrimaryListingMarketParticipantId TradeCorrectionMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void TradeCorrectionMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator TradeCorrectionMessage::financial_status_indicator() const { return financial_status_indicator_; }
void TradeCorrectionMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

const ConsolidatedData& TradeCorrectionMessage::consolidated_data() const { return consolidated_data_; }
ConsolidatedData& TradeCorrectionMessage::consolidated_data() { return consolidated_data_; }
void TradeCorrectionMessage::set_consolidated_data(const ConsolidatedData& value) { consolidated_data_ = value; }

const ParticipantData& TradeCorrectionMessage::participant_data() const { return participant_data_; }
ParticipantData& TradeCorrectionMessage::participant_data() { return participant_data_; }
void TradeCorrectionMessage::set_participant_data(const ParticipantData& value) { participant_data_ = value; }

TradeMessagePayloadCode TradeCorrectionMessage::type() const { return message_type; }

std::string_view TradeCorrectionMessage::name() const { return "Trade Correction Message"; }

std::size_t TradeCorrectionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCorrectionMessage", wire_size, length);

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

    offset += corrected_trade_.decode(data + offset, length - offset);

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_2_.decode(data + offset, length - offset);

    original_participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    offset += original_trade_.decode(data + offset, length - offset);

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    offset += consolidated_data_.decode(data + offset, length - offset);

    offset += participant_data_.decode(data + offset, length - offset);

    return offset;
}

std::size_t TradeCorrectionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCorrectionMessage", wire_size, capacity);

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

    offset += corrected_trade_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    offset += timestamp_2_.encode(data + offset, capacity - offset);

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(original_participant_reference_number_));
    offset += 8;

    offset += original_trade_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    offset += consolidated_data_.encode(data + offset, capacity - offset);

    offset += participant_data_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TradeCorrectionMessage::encoded_size() const {
    return wire_size;
}

void TradeCorrectionMessage::accept(TradeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TradeMessagePayload> TradeCorrectionMessage::clone() const {
    return std::make_unique<TradeCorrectionMessage>(*this);
}

void TradeCorrectionMessage::print(std::ostream& out) const {
    out << "TradeCorrectionMessage{";
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
    out << ", corrected_trade=";
    corrected_trade_.print(out);
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", timestamp_2=";
    timestamp_2_.print(out);
    out << ", original_participant_reference_number=";
    out << original_participant_reference_number_;
    out << ", original_trade=";
    original_trade_.print(out);
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", consolidated_data=";
    consolidated_data_.print(out);
    out << ", participant_data=";
    participant_data_.print(out);
    out << '}';
}

bool TradeCorrectionMessage::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const TradeCorrectionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCorrectionMessage::operator==(const TradeCorrectionMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && corrected_trade_ == other.corrected_trade_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && timestamp_2_ == other.timestamp_2_
        && original_participant_reference_number_ == other.original_participant_reference_number_
        && original_trade_ == other.original_trade_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && consolidated_data_ == other.consolidated_data_
        && participant_data_ == other.participant_data_;
}

bool TradeCorrectionMessage::operator!=(const TradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_9
