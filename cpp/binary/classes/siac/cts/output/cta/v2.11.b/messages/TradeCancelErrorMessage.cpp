#include "TradeCancelErrorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

TradeCancelErrorMessage::TradeCancelErrorMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const SaleCondition4& sale_condition_4, Decimal trade_price, std::uint32_t trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, TradeReportingFacilityId trade_reporting_facility_id, std::int64_t original_participant_reference_number, const Timestamp2& timestamp_2, CancelErrorAction cancel_error_action, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, std::uint32_t consolidated_previous_close_price_date, char consolidated_last_participant_id, Decimal consolidated_last_price, Decimal consolidated_high_price, Decimal consolidated_low_price, std::uint32_t consolidated_total_volume, char consolidated_tick, std::uint32_t participant_previous_close_price_date, Decimal participant_last_price, Decimal participant_high_price, Decimal participant_low_price, Decimal participant_open_price, std::uint32_t participant_total_volume, char participant_tick)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), sale_condition_4_(sale_condition_4), trade_price_(trade_price), trade_volume_(trade_volume), sellers_sale_days_(sellers_sale_days), stop_stock_indicator_(stop_stock_indicator), trade_through_exempt_indicator_(trade_through_exempt_indicator), trade_reporting_facility_id_(trade_reporting_facility_id), original_participant_reference_number_(original_participant_reference_number), timestamp_2_(timestamp_2), cancel_error_action_(cancel_error_action), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), consolidated_previous_close_price_date_(consolidated_previous_close_price_date), consolidated_last_participant_id_(consolidated_last_participant_id), consolidated_last_price_(consolidated_last_price), consolidated_high_price_(consolidated_high_price), consolidated_low_price_(consolidated_low_price), consolidated_total_volume_(consolidated_total_volume), consolidated_tick_(consolidated_tick), participant_previous_close_price_date_(participant_previous_close_price_date), participant_last_price_(participant_last_price), participant_high_price_(participant_high_price), participant_low_price_(participant_low_price), participant_open_price_(participant_open_price), participant_total_volume_(participant_total_volume), participant_tick_(participant_tick) {}

ParticipantId TradeCancelErrorMessage::participant_id() const { return participant_id_; }
void TradeCancelErrorMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& TradeCancelErrorMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& TradeCancelErrorMessage::timestamp_1() { return timestamp_1_; }
void TradeCancelErrorMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t TradeCancelErrorMessage::message_id() const { return message_id_; }
void TradeCancelErrorMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t TradeCancelErrorMessage::transaction_id() const { return transaction_id_; }
void TradeCancelErrorMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t TradeCancelErrorMessage::participant_reference_number() const { return participant_reference_number_; }
void TradeCancelErrorMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& TradeCancelErrorMessage::security_symbol() const { return security_symbol_; }
std::string& TradeCancelErrorMessage::security_symbol() { return security_symbol_; }
void TradeCancelErrorMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType TradeCancelErrorMessage::instrument_type() const { return instrument_type_; }
void TradeCancelErrorMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

const SaleCondition4& TradeCancelErrorMessage::sale_condition_4() const { return sale_condition_4_; }
SaleCondition4& TradeCancelErrorMessage::sale_condition_4() { return sale_condition_4_; }
void TradeCancelErrorMessage::set_sale_condition_4(const SaleCondition4& value) { sale_condition_4_ = value; }

Decimal TradeCancelErrorMessage::trade_price() const { return trade_price_; }
void TradeCancelErrorMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t TradeCancelErrorMessage::trade_volume() const { return trade_volume_; }
void TradeCancelErrorMessage::set_trade_volume(std::uint32_t value) { trade_volume_ = value; }

std::uint8_t TradeCancelErrorMessage::sellers_sale_days() const { return sellers_sale_days_; }
void TradeCancelErrorMessage::set_sellers_sale_days(std::uint8_t value) { sellers_sale_days_ = value; }

StopStockIndicator TradeCancelErrorMessage::stop_stock_indicator() const { return stop_stock_indicator_; }
void TradeCancelErrorMessage::set_stop_stock_indicator(StopStockIndicator value) { stop_stock_indicator_ = value; }

TradeThroughExemptIndicator TradeCancelErrorMessage::trade_through_exempt_indicator() const { return trade_through_exempt_indicator_; }
void TradeCancelErrorMessage::set_trade_through_exempt_indicator(TradeThroughExemptIndicator value) { trade_through_exempt_indicator_ = value; }

TradeReportingFacilityId TradeCancelErrorMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void TradeCancelErrorMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

std::int64_t TradeCancelErrorMessage::original_participant_reference_number() const { return original_participant_reference_number_; }
void TradeCancelErrorMessage::set_original_participant_reference_number(std::int64_t value) { original_participant_reference_number_ = value; }

const Timestamp2& TradeCancelErrorMessage::timestamp_2() const { return timestamp_2_; }
Timestamp2& TradeCancelErrorMessage::timestamp_2() { return timestamp_2_; }
void TradeCancelErrorMessage::set_timestamp_2(const Timestamp2& value) { timestamp_2_ = value; }

CancelErrorAction TradeCancelErrorMessage::cancel_error_action() const { return cancel_error_action_; }
void TradeCancelErrorMessage::set_cancel_error_action(CancelErrorAction value) { cancel_error_action_ = value; }

ShortSaleRestrictionIndicator TradeCancelErrorMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void TradeCancelErrorMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId TradeCancelErrorMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void TradeCancelErrorMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator TradeCancelErrorMessage::financial_status_indicator() const { return financial_status_indicator_; }
void TradeCancelErrorMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

std::uint32_t TradeCancelErrorMessage::consolidated_previous_close_price_date() const { return consolidated_previous_close_price_date_; }
void TradeCancelErrorMessage::set_consolidated_previous_close_price_date(std::uint32_t value) { consolidated_previous_close_price_date_ = value; }

char TradeCancelErrorMessage::consolidated_last_participant_id() const { return consolidated_last_participant_id_; }
void TradeCancelErrorMessage::set_consolidated_last_participant_id(char value) { consolidated_last_participant_id_ = value; }

Decimal TradeCancelErrorMessage::consolidated_last_price() const { return consolidated_last_price_; }
void TradeCancelErrorMessage::set_consolidated_last_price(Decimal value) { consolidated_last_price_ = value; }

Decimal TradeCancelErrorMessage::consolidated_high_price() const { return consolidated_high_price_; }
void TradeCancelErrorMessage::set_consolidated_high_price(Decimal value) { consolidated_high_price_ = value; }

Decimal TradeCancelErrorMessage::consolidated_low_price() const { return consolidated_low_price_; }
void TradeCancelErrorMessage::set_consolidated_low_price(Decimal value) { consolidated_low_price_ = value; }

std::uint32_t TradeCancelErrorMessage::consolidated_total_volume() const { return consolidated_total_volume_; }
void TradeCancelErrorMessage::set_consolidated_total_volume(std::uint32_t value) { consolidated_total_volume_ = value; }

char TradeCancelErrorMessage::consolidated_tick() const { return consolidated_tick_; }
void TradeCancelErrorMessage::set_consolidated_tick(char value) { consolidated_tick_ = value; }

std::uint32_t TradeCancelErrorMessage::participant_previous_close_price_date() const { return participant_previous_close_price_date_; }
void TradeCancelErrorMessage::set_participant_previous_close_price_date(std::uint32_t value) { participant_previous_close_price_date_ = value; }

Decimal TradeCancelErrorMessage::participant_last_price() const { return participant_last_price_; }
void TradeCancelErrorMessage::set_participant_last_price(Decimal value) { participant_last_price_ = value; }

Decimal TradeCancelErrorMessage::participant_high_price() const { return participant_high_price_; }
void TradeCancelErrorMessage::set_participant_high_price(Decimal value) { participant_high_price_ = value; }

Decimal TradeCancelErrorMessage::participant_low_price() const { return participant_low_price_; }
void TradeCancelErrorMessage::set_participant_low_price(Decimal value) { participant_low_price_ = value; }

Decimal TradeCancelErrorMessage::participant_open_price() const { return participant_open_price_; }
void TradeCancelErrorMessage::set_participant_open_price(Decimal value) { participant_open_price_ = value; }

std::uint32_t TradeCancelErrorMessage::participant_total_volume() const { return participant_total_volume_; }
void TradeCancelErrorMessage::set_participant_total_volume(std::uint32_t value) { participant_total_volume_ = value; }

char TradeCancelErrorMessage::participant_tick() const { return participant_tick_; }
void TradeCancelErrorMessage::set_participant_tick(char value) { participant_tick_ = value; }

TradeMessagePayloadCode TradeCancelErrorMessage::type() const { return message_type; }

std::string_view TradeCancelErrorMessage::name() const { return "Trade Cancel Error Message"; }

std::size_t TradeCancelErrorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancelErrorMessage", wire_size, length);

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

    offset += sale_condition_4_.decode(data + offset, length - offset);

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    stop_stock_indicator_ = static_cast<StopStockIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exempt_indicator_ = static_cast<TradeThroughExemptIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    original_participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    offset += timestamp_2_.decode(data + offset, length - offset);

    cancel_error_action_ = static_cast<CancelErrorAction>(wire::read_char(data + offset));
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
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

std::size_t TradeCancelErrorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancelErrorMessage", wire_size, capacity);

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

    offset += sale_condition_4_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(stop_stock_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exempt_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(original_participant_reference_number_));
    offset += 8;

    offset += timestamp_2_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(cancel_error_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
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

std::size_t TradeCancelErrorMessage::encoded_size() const {
    return wire_size;
}

void TradeCancelErrorMessage::accept(TradeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TradeMessagePayload> TradeCancelErrorMessage::clone() const {
    return std::make_unique<TradeCancelErrorMessage>(*this);
}

void TradeCancelErrorMessage::print(std::ostream& out) const {
    out << "TradeCancelErrorMessage{";
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
    out << ", sale_condition_4=";
    sale_condition_4_.print(out);
    out << ", trade_price=";
    out << trade_price_;
    out << ", trade_volume=";
    out << trade_volume_;
    out << ", sellers_sale_days=";
    out << static_cast<int>(sellers_sale_days_);
    out << ", stop_stock_indicator=";
    out << stop_stock_indicator_;
    out << ", trade_through_exempt_indicator=";
    out << trade_through_exempt_indicator_;
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", original_participant_reference_number=";
    out << original_participant_reference_number_;
    out << ", timestamp_2=";
    timestamp_2_.print(out);
    out << ", cancel_error_action=";
    out << cancel_error_action_;
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
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

bool TradeCancelErrorMessage::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const TradeCancelErrorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancelErrorMessage::operator==(const TradeCancelErrorMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && sale_condition_4_ == other.sale_condition_4_
        && trade_price_ == other.trade_price_
        && trade_volume_ == other.trade_volume_
        && sellers_sale_days_ == other.sellers_sale_days_
        && stop_stock_indicator_ == other.stop_stock_indicator_
        && trade_through_exempt_indicator_ == other.trade_through_exempt_indicator_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && original_participant_reference_number_ == other.original_participant_reference_number_
        && timestamp_2_ == other.timestamp_2_
        && cancel_error_action_ == other.cancel_error_action_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
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

bool TradeCancelErrorMessage::operator!=(const TradeCancelErrorMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
