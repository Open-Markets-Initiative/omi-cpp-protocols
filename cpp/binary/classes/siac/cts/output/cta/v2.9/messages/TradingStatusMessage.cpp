#include "TradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_9 {

TradingStatusMessage::TradingStatusMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, Decimal last_price, Decimal high_indication_price_upper_limit_price_band, Decimal low_indication_price_lower_limit_price_band, std::uint32_t buy_volume, std::uint32_t sell_volume, SecurityStatus security_status, HaltReason halt_reason, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, LimitUpLimitDownIndicator limit_up_limit_down_indicator)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), last_price_(last_price), high_indication_price_upper_limit_price_band_(high_indication_price_upper_limit_price_band), low_indication_price_lower_limit_price_band_(low_indication_price_lower_limit_price_band), buy_volume_(buy_volume), sell_volume_(sell_volume), security_status_(security_status), halt_reason_(halt_reason), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), limit_up_limit_down_indicator_(limit_up_limit_down_indicator) {}

ParticipantId TradingStatusMessage::participant_id() const { return participant_id_; }
void TradingStatusMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& TradingStatusMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& TradingStatusMessage::timestamp_1() { return timestamp_1_; }
void TradingStatusMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t TradingStatusMessage::message_id() const { return message_id_; }
void TradingStatusMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t TradingStatusMessage::transaction_id() const { return transaction_id_; }
void TradingStatusMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t TradingStatusMessage::participant_reference_number() const { return participant_reference_number_; }
void TradingStatusMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& TradingStatusMessage::security_symbol() const { return security_symbol_; }
std::string& TradingStatusMessage::security_symbol() { return security_symbol_; }
void TradingStatusMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType TradingStatusMessage::instrument_type() const { return instrument_type_; }
void TradingStatusMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

Decimal TradingStatusMessage::last_price() const { return last_price_; }
void TradingStatusMessage::set_last_price(Decimal value) { last_price_ = value; }

Decimal TradingStatusMessage::high_indication_price_upper_limit_price_band() const { return high_indication_price_upper_limit_price_band_; }
void TradingStatusMessage::set_high_indication_price_upper_limit_price_band(Decimal value) { high_indication_price_upper_limit_price_band_ = value; }

Decimal TradingStatusMessage::low_indication_price_lower_limit_price_band() const { return low_indication_price_lower_limit_price_band_; }
void TradingStatusMessage::set_low_indication_price_lower_limit_price_band(Decimal value) { low_indication_price_lower_limit_price_band_ = value; }

std::uint32_t TradingStatusMessage::buy_volume() const { return buy_volume_; }
void TradingStatusMessage::set_buy_volume(std::uint32_t value) { buy_volume_ = value; }

std::uint32_t TradingStatusMessage::sell_volume() const { return sell_volume_; }
void TradingStatusMessage::set_sell_volume(std::uint32_t value) { sell_volume_ = value; }

SecurityStatus TradingStatusMessage::security_status() const { return security_status_; }
void TradingStatusMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

HaltReason TradingStatusMessage::halt_reason() const { return halt_reason_; }
void TradingStatusMessage::set_halt_reason(HaltReason value) { halt_reason_ = value; }

ShortSaleRestrictionIndicator TradingStatusMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void TradingStatusMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId TradingStatusMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void TradingStatusMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator TradingStatusMessage::financial_status_indicator() const { return financial_status_indicator_; }
void TradingStatusMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

LimitUpLimitDownIndicator TradingStatusMessage::limit_up_limit_down_indicator() const { return limit_up_limit_down_indicator_; }
void TradingStatusMessage::set_limit_up_limit_down_indicator(LimitUpLimitDownIndicator value) { limit_up_limit_down_indicator_ = value; }

TradeMessagePayloadCode TradingStatusMessage::type() const { return message_type; }

std::string_view TradingStatusMessage::name() const { return "Trading Status Message"; }

std::size_t TradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradingStatusMessage", wire_size, length);

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

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    high_indication_price_upper_limit_price_band_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    low_indication_price_lower_limit_price_band_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    buy_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    sell_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    security_status_ = static_cast<SecurityStatus>(wire::read_char(data + offset));
    offset += 1;

    halt_reason_ = static_cast<HaltReason>(wire::read_char(data + offset));
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    limit_up_limit_down_indicator_ = static_cast<LimitUpLimitDownIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingStatusMessage", wire_size, capacity);

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

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(high_indication_price_upper_limit_price_band_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(low_indication_price_lower_limit_price_band_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(buy_volume_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(sell_volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(security_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(halt_reason_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(limit_up_limit_down_indicator_));
    offset += 1;

    return offset;
}

std::size_t TradingStatusMessage::encoded_size() const {
    return wire_size;
}

void TradingStatusMessage::accept(TradeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TradeMessagePayload> TradingStatusMessage::clone() const {
    return std::make_unique<TradingStatusMessage>(*this);
}

void TradingStatusMessage::print(std::ostream& out) const {
    out << "TradingStatusMessage{";
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
    out << ", last_price=";
    out << last_price_;
    out << ", high_indication_price_upper_limit_price_band=";
    out << high_indication_price_upper_limit_price_band_;
    out << ", low_indication_price_lower_limit_price_band=";
    out << low_indication_price_lower_limit_price_band_;
    out << ", buy_volume=";
    out << buy_volume_;
    out << ", sell_volume=";
    out << sell_volume_;
    out << ", security_status=";
    out << security_status_;
    out << ", halt_reason=";
    out << halt_reason_;
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", limit_up_limit_down_indicator=";
    out << limit_up_limit_down_indicator_;
    out << '}';
}

bool TradingStatusMessage::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const TradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradingStatusMessage::operator==(const TradingStatusMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && last_price_ == other.last_price_
        && high_indication_price_upper_limit_price_band_ == other.high_indication_price_upper_limit_price_band_
        && low_indication_price_lower_limit_price_band_ == other.low_indication_price_lower_limit_price_band_
        && buy_volume_ == other.buy_volume_
        && sell_volume_ == other.sell_volume_
        && security_status_ == other.security_status_
        && halt_reason_ == other.halt_reason_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && limit_up_limit_down_indicator_ == other.limit_up_limit_down_indicator_;
}

bool TradingStatusMessage::operator!=(const TradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_9
