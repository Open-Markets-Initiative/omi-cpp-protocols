#include "TradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

TradeCorrectionMessage::TradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const std::string& corrected_sale_condition, Decimal corrected_trade_price, std::uint32_t corrected_trade_volume, std::uint8_t corrected_sellers_sale_days, char corrected_stop_stock_indicator, char corrected_trade_through_exempt_indicator, char corrected_short_sale_restriction_indicator, TradeReportingFacilityId trade_reporting_facility_id, const Timestamp2& timestamp_2, std::int64_t original_participant_reference_number, const std::string& original_sale_condition, Decimal original_trade_price, std::uint32_t original_trade_volume, std::uint8_t original_sellers_sale_days, char original_stop_stock_indicator, char original_trade_through_exempt_indicator, char original_short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, std::uint32_t consolidated_previous_close_price_date, char consolidated_last_participant_id, Decimal consolidated_last_price, Decimal consolidated_high_price, Decimal consolidated_low_price, std::uint32_t consolidated_total_volume, char consolidated_tick, std::uint32_t participant_previous_close_price_date, Decimal participant_last_price, Decimal participant_high_price, Decimal participant_low_price, Decimal participant_open_price, std::uint32_t participant_total_volume, char participant_tick)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), corrected_sale_condition_(corrected_sale_condition), corrected_trade_price_(corrected_trade_price), corrected_trade_volume_(corrected_trade_volume), corrected_sellers_sale_days_(corrected_sellers_sale_days), corrected_stop_stock_indicator_(corrected_stop_stock_indicator), corrected_trade_through_exempt_indicator_(corrected_trade_through_exempt_indicator), corrected_short_sale_restriction_indicator_(corrected_short_sale_restriction_indicator), trade_reporting_facility_id_(trade_reporting_facility_id), timestamp_2_(timestamp_2), original_participant_reference_number_(original_participant_reference_number), original_sale_condition_(original_sale_condition), original_trade_price_(original_trade_price), original_trade_volume_(original_trade_volume), original_sellers_sale_days_(original_sellers_sale_days), original_stop_stock_indicator_(original_stop_stock_indicator), original_trade_through_exempt_indicator_(original_trade_through_exempt_indicator), original_short_sale_restriction_indicator_(original_short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), consolidated_previous_close_price_date_(consolidated_previous_close_price_date), consolidated_last_participant_id_(consolidated_last_participant_id), consolidated_last_price_(consolidated_last_price), consolidated_high_price_(consolidated_high_price), consolidated_low_price_(consolidated_low_price), consolidated_total_volume_(consolidated_total_volume), consolidated_tick_(consolidated_tick), participant_previous_close_price_date_(participant_previous_close_price_date), participant_last_price_(participant_last_price), participant_high_price_(participant_high_price), participant_low_price_(participant_low_price), participant_open_price_(participant_open_price), participant_total_volume_(participant_total_volume), participant_tick_(participant_tick) {}

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

const std::string& TradeCorrectionMessage::corrected_sale_condition() const { return corrected_sale_condition_; }
std::string& TradeCorrectionMessage::corrected_sale_condition() { return corrected_sale_condition_; }
void TradeCorrectionMessage::set_corrected_sale_condition(const std::string& value) { corrected_sale_condition_ = value; }

Decimal TradeCorrectionMessage::corrected_trade_price() const { return corrected_trade_price_; }
void TradeCorrectionMessage::set_corrected_trade_price(Decimal value) { corrected_trade_price_ = value; }

std::uint32_t TradeCorrectionMessage::corrected_trade_volume() const { return corrected_trade_volume_; }
void TradeCorrectionMessage::set_corrected_trade_volume(std::uint32_t value) { corrected_trade_volume_ = value; }

std::uint8_t TradeCorrectionMessage::corrected_sellers_sale_days() const { return corrected_sellers_sale_days_; }
void TradeCorrectionMessage::set_corrected_sellers_sale_days(std::uint8_t value) { corrected_sellers_sale_days_ = value; }

char TradeCorrectionMessage::corrected_stop_stock_indicator() const { return corrected_stop_stock_indicator_; }
void TradeCorrectionMessage::set_corrected_stop_stock_indicator(char value) { corrected_stop_stock_indicator_ = value; }

char TradeCorrectionMessage::corrected_trade_through_exempt_indicator() const { return corrected_trade_through_exempt_indicator_; }
void TradeCorrectionMessage::set_corrected_trade_through_exempt_indicator(char value) { corrected_trade_through_exempt_indicator_ = value; }

char TradeCorrectionMessage::corrected_short_sale_restriction_indicator() const { return corrected_short_sale_restriction_indicator_; }
void TradeCorrectionMessage::set_corrected_short_sale_restriction_indicator(char value) { corrected_short_sale_restriction_indicator_ = value; }

TradeReportingFacilityId TradeCorrectionMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void TradeCorrectionMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

const Timestamp2& TradeCorrectionMessage::timestamp_2() const { return timestamp_2_; }
Timestamp2& TradeCorrectionMessage::timestamp_2() { return timestamp_2_; }
void TradeCorrectionMessage::set_timestamp_2(const Timestamp2& value) { timestamp_2_ = value; }

std::int64_t TradeCorrectionMessage::original_participant_reference_number() const { return original_participant_reference_number_; }
void TradeCorrectionMessage::set_original_participant_reference_number(std::int64_t value) { original_participant_reference_number_ = value; }

const std::string& TradeCorrectionMessage::original_sale_condition() const { return original_sale_condition_; }
std::string& TradeCorrectionMessage::original_sale_condition() { return original_sale_condition_; }
void TradeCorrectionMessage::set_original_sale_condition(const std::string& value) { original_sale_condition_ = value; }

Decimal TradeCorrectionMessage::original_trade_price() const { return original_trade_price_; }
void TradeCorrectionMessage::set_original_trade_price(Decimal value) { original_trade_price_ = value; }

std::uint32_t TradeCorrectionMessage::original_trade_volume() const { return original_trade_volume_; }
void TradeCorrectionMessage::set_original_trade_volume(std::uint32_t value) { original_trade_volume_ = value; }

std::uint8_t TradeCorrectionMessage::original_sellers_sale_days() const { return original_sellers_sale_days_; }
void TradeCorrectionMessage::set_original_sellers_sale_days(std::uint8_t value) { original_sellers_sale_days_ = value; }

char TradeCorrectionMessage::original_stop_stock_indicator() const { return original_stop_stock_indicator_; }
void TradeCorrectionMessage::set_original_stop_stock_indicator(char value) { original_stop_stock_indicator_ = value; }

char TradeCorrectionMessage::original_trade_through_exempt_indicator() const { return original_trade_through_exempt_indicator_; }
void TradeCorrectionMessage::set_original_trade_through_exempt_indicator(char value) { original_trade_through_exempt_indicator_ = value; }

char TradeCorrectionMessage::original_short_sale_restriction_indicator() const { return original_short_sale_restriction_indicator_; }
void TradeCorrectionMessage::set_original_short_sale_restriction_indicator(char value) { original_short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId TradeCorrectionMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void TradeCorrectionMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator TradeCorrectionMessage::financial_status_indicator() const { return financial_status_indicator_; }
void TradeCorrectionMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

std::uint32_t TradeCorrectionMessage::consolidated_previous_close_price_date() const { return consolidated_previous_close_price_date_; }
void TradeCorrectionMessage::set_consolidated_previous_close_price_date(std::uint32_t value) { consolidated_previous_close_price_date_ = value; }

char TradeCorrectionMessage::consolidated_last_participant_id() const { return consolidated_last_participant_id_; }
void TradeCorrectionMessage::set_consolidated_last_participant_id(char value) { consolidated_last_participant_id_ = value; }

Decimal TradeCorrectionMessage::consolidated_last_price() const { return consolidated_last_price_; }
void TradeCorrectionMessage::set_consolidated_last_price(Decimal value) { consolidated_last_price_ = value; }

Decimal TradeCorrectionMessage::consolidated_high_price() const { return consolidated_high_price_; }
void TradeCorrectionMessage::set_consolidated_high_price(Decimal value) { consolidated_high_price_ = value; }

Decimal TradeCorrectionMessage::consolidated_low_price() const { return consolidated_low_price_; }
void TradeCorrectionMessage::set_consolidated_low_price(Decimal value) { consolidated_low_price_ = value; }

std::uint32_t TradeCorrectionMessage::consolidated_total_volume() const { return consolidated_total_volume_; }
void TradeCorrectionMessage::set_consolidated_total_volume(std::uint32_t value) { consolidated_total_volume_ = value; }

char TradeCorrectionMessage::consolidated_tick() const { return consolidated_tick_; }
void TradeCorrectionMessage::set_consolidated_tick(char value) { consolidated_tick_ = value; }

std::uint32_t TradeCorrectionMessage::participant_previous_close_price_date() const { return participant_previous_close_price_date_; }
void TradeCorrectionMessage::set_participant_previous_close_price_date(std::uint32_t value) { participant_previous_close_price_date_ = value; }

Decimal TradeCorrectionMessage::participant_last_price() const { return participant_last_price_; }
void TradeCorrectionMessage::set_participant_last_price(Decimal value) { participant_last_price_ = value; }

Decimal TradeCorrectionMessage::participant_high_price() const { return participant_high_price_; }
void TradeCorrectionMessage::set_participant_high_price(Decimal value) { participant_high_price_ = value; }

Decimal TradeCorrectionMessage::participant_low_price() const { return participant_low_price_; }
void TradeCorrectionMessage::set_participant_low_price(Decimal value) { participant_low_price_ = value; }

Decimal TradeCorrectionMessage::participant_open_price() const { return participant_open_price_; }
void TradeCorrectionMessage::set_participant_open_price(Decimal value) { participant_open_price_ = value; }

std::uint32_t TradeCorrectionMessage::participant_total_volume() const { return participant_total_volume_; }
void TradeCorrectionMessage::set_participant_total_volume(std::uint32_t value) { participant_total_volume_ = value; }

char TradeCorrectionMessage::participant_tick() const { return participant_tick_; }
void TradeCorrectionMessage::set_participant_tick(char value) { participant_tick_ = value; }

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

    corrected_sale_condition_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    corrected_trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    corrected_trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    corrected_sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    corrected_stop_stock_indicator_ = wire::read_char(data + offset);
    offset += 1;

    corrected_trade_through_exempt_indicator_ = wire::read_char(data + offset);
    offset += 1;

    corrected_short_sale_restriction_indicator_ = wire::read_char(data + offset);
    offset += 1;

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_2_.decode(data + offset, length - offset);

    original_participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    original_sale_condition_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    original_trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    original_trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    original_sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    original_stop_stock_indicator_ = wire::read_char(data + offset);
    offset += 1;

    original_trade_through_exempt_indicator_ = wire::read_char(data + offset);
    offset += 1;

    original_short_sale_restriction_indicator_ = wire::read_char(data + offset);
    offset += 1;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    consolidated_previous_close_price_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    consolidated_last_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    consolidated_last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    consolidated_high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    consolidated_low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    consolidated_total_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    consolidated_tick_ = wire::read_char(data + offset);
    offset += 1;

    participant_previous_close_price_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    participant_high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    participant_low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    participant_open_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    participant_total_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_tick_ = wire::read_char(data + offset);
    offset += 1;

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

    wire::write_text(data + offset, 4, ' ', corrected_sale_condition_);
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(corrected_trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(corrected_trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(corrected_sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, corrected_stop_stock_indicator_);
    offset += 1;

    wire::write_char(data + offset, corrected_trade_through_exempt_indicator_);
    offset += 1;

    wire::write_char(data + offset, corrected_short_sale_restriction_indicator_);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    offset += timestamp_2_.encode(data + offset, capacity - offset);

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(original_participant_reference_number_));
    offset += 8;

    wire::write_text(data + offset, 4, ' ', original_sale_condition_);
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(original_sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, original_stop_stock_indicator_);
    offset += 1;

    wire::write_char(data + offset, original_trade_through_exempt_indicator_);
    offset += 1;

    wire::write_char(data + offset, original_short_sale_restriction_indicator_);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_previous_close_price_date_));
    offset += 4;

    wire::write_char(data + offset, consolidated_last_participant_id_);
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_high_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(consolidated_low_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(consolidated_total_volume_));
    offset += 4;

    wire::write_char(data + offset, consolidated_tick_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_previous_close_price_date_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(participant_last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(participant_high_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(participant_low_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(participant_open_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_total_volume_));
    offset += 4;

    wire::write_char(data + offset, participant_tick_);
    offset += 1;

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
    out << ", corrected_sale_condition=";
    print::text(out, corrected_sale_condition_);
    out << ", corrected_trade_price=";
    out << corrected_trade_price_;
    out << ", corrected_trade_volume=";
    out << corrected_trade_volume_;
    out << ", corrected_sellers_sale_days=";
    out << static_cast<int>(corrected_sellers_sale_days_);
    out << ", corrected_stop_stock_indicator=";
    print::character(out, corrected_stop_stock_indicator_);
    out << ", corrected_trade_through_exempt_indicator=";
    print::character(out, corrected_trade_through_exempt_indicator_);
    out << ", corrected_short_sale_restriction_indicator=";
    print::character(out, corrected_short_sale_restriction_indicator_);
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", timestamp_2=";
    timestamp_2_.print(out);
    out << ", original_participant_reference_number=";
    out << original_participant_reference_number_;
    out << ", original_sale_condition=";
    print::text(out, original_sale_condition_);
    out << ", original_trade_price=";
    out << original_trade_price_;
    out << ", original_trade_volume=";
    out << original_trade_volume_;
    out << ", original_sellers_sale_days=";
    out << static_cast<int>(original_sellers_sale_days_);
    out << ", original_stop_stock_indicator=";
    print::character(out, original_stop_stock_indicator_);
    out << ", original_trade_through_exempt_indicator=";
    print::character(out, original_trade_through_exempt_indicator_);
    out << ", original_short_sale_restriction_indicator=";
    print::character(out, original_short_sale_restriction_indicator_);
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", consolidated_previous_close_price_date=";
    out << consolidated_previous_close_price_date_;
    out << ", consolidated_last_participant_id=";
    print::character(out, consolidated_last_participant_id_);
    out << ", consolidated_last_price=";
    out << consolidated_last_price_;
    out << ", consolidated_high_price=";
    out << consolidated_high_price_;
    out << ", consolidated_low_price=";
    out << consolidated_low_price_;
    out << ", consolidated_total_volume=";
    out << consolidated_total_volume_;
    out << ", consolidated_tick=";
    print::character(out, consolidated_tick_);
    out << ", participant_previous_close_price_date=";
    out << participant_previous_close_price_date_;
    out << ", participant_last_price=";
    out << participant_last_price_;
    out << ", participant_high_price=";
    out << participant_high_price_;
    out << ", participant_low_price=";
    out << participant_low_price_;
    out << ", participant_open_price=";
    out << participant_open_price_;
    out << ", participant_total_volume=";
    out << participant_total_volume_;
    out << ", participant_tick=";
    print::character(out, participant_tick_);
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
        && corrected_sale_condition_ == other.corrected_sale_condition_
        && corrected_trade_price_ == other.corrected_trade_price_
        && corrected_trade_volume_ == other.corrected_trade_volume_
        && corrected_sellers_sale_days_ == other.corrected_sellers_sale_days_
        && corrected_stop_stock_indicator_ == other.corrected_stop_stock_indicator_
        && corrected_trade_through_exempt_indicator_ == other.corrected_trade_through_exempt_indicator_
        && corrected_short_sale_restriction_indicator_ == other.corrected_short_sale_restriction_indicator_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && timestamp_2_ == other.timestamp_2_
        && original_participant_reference_number_ == other.original_participant_reference_number_
        && original_sale_condition_ == other.original_sale_condition_
        && original_trade_price_ == other.original_trade_price_
        && original_trade_volume_ == other.original_trade_volume_
        && original_sellers_sale_days_ == other.original_sellers_sale_days_
        && original_stop_stock_indicator_ == other.original_stop_stock_indicator_
        && original_trade_through_exempt_indicator_ == other.original_trade_through_exempt_indicator_
        && original_short_sale_restriction_indicator_ == other.original_short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && consolidated_previous_close_price_date_ == other.consolidated_previous_close_price_date_
        && consolidated_last_participant_id_ == other.consolidated_last_participant_id_
        && consolidated_last_price_ == other.consolidated_last_price_
        && consolidated_high_price_ == other.consolidated_high_price_
        && consolidated_low_price_ == other.consolidated_low_price_
        && consolidated_total_volume_ == other.consolidated_total_volume_
        && consolidated_tick_ == other.consolidated_tick_
        && participant_previous_close_price_date_ == other.participant_previous_close_price_date_
        && participant_last_price_ == other.participant_last_price_
        && participant_high_price_ == other.participant_high_price_
        && participant_low_price_ == other.participant_low_price_
        && participant_open_price_ == other.participant_open_price_
        && participant_total_volume_ == other.participant_total_volume_
        && participant_tick_ == other.participant_tick_;
}

bool TradeCorrectionMessage::operator!=(const TradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
