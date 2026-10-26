#include "ShortTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

ShortTradeMessage::ShortTradeMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol_5, SaleCondition1 sale_condition_1, SaleConditionCategory sale_condition_category, Decimal trade_price_2, std::uint16_t trade_volume_2, PrimaryListingMarketParticipantId primary_listing_market_participant_id, ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator, ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_5_(security_symbol_5), sale_condition_1_(sale_condition_1), sale_condition_category_(sale_condition_category), trade_price_2_(trade_price_2), trade_volume_2_(trade_volume_2), primary_listing_market_participant_id_(primary_listing_market_participant_id), consolidated_high_low_last_indicator_(consolidated_high_low_last_indicator), participant_open_high_low_last_indicator_(participant_open_high_low_last_indicator) {}

ParticipantId ShortTradeMessage::participant_id() const { return participant_id_; }
void ShortTradeMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& ShortTradeMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& ShortTradeMessage::timestamp_1() { return timestamp_1_; }
void ShortTradeMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t ShortTradeMessage::message_id() const { return message_id_; }
void ShortTradeMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t ShortTradeMessage::transaction_id() const { return transaction_id_; }
void ShortTradeMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t ShortTradeMessage::participant_reference_number() const { return participant_reference_number_; }
void ShortTradeMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& ShortTradeMessage::security_symbol_5() const { return security_symbol_5_; }
std::string& ShortTradeMessage::security_symbol_5() { return security_symbol_5_; }
void ShortTradeMessage::set_security_symbol_5(const std::string& value) { security_symbol_5_ = value; }

SaleCondition1 ShortTradeMessage::sale_condition_1() const { return sale_condition_1_; }
void ShortTradeMessage::set_sale_condition_1(SaleCondition1 value) { sale_condition_1_ = value; }

SaleConditionCategory ShortTradeMessage::sale_condition_category() const { return sale_condition_category_; }
void ShortTradeMessage::set_sale_condition_category(SaleConditionCategory value) { sale_condition_category_ = value; }

Decimal ShortTradeMessage::trade_price_2() const { return trade_price_2_; }
void ShortTradeMessage::set_trade_price_2(Decimal value) { trade_price_2_ = value; }

std::uint16_t ShortTradeMessage::trade_volume_2() const { return trade_volume_2_; }
void ShortTradeMessage::set_trade_volume_2(std::uint16_t value) { trade_volume_2_ = value; }

PrimaryListingMarketParticipantId ShortTradeMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void ShortTradeMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

ConsolidatedHighLowLastIndicator ShortTradeMessage::consolidated_high_low_last_indicator() const { return consolidated_high_low_last_indicator_; }
void ShortTradeMessage::set_consolidated_high_low_last_indicator(ConsolidatedHighLowLastIndicator value) { consolidated_high_low_last_indicator_ = value; }

ParticipantOpenHighLowLastIndicator ShortTradeMessage::participant_open_high_low_last_indicator() const { return participant_open_high_low_last_indicator_; }
void ShortTradeMessage::set_participant_open_high_low_last_indicator(ParticipantOpenHighLowLastIndicator value) { participant_open_high_low_last_indicator_ = value; }

TradeMessagePayloadCode ShortTradeMessage::type() const { return message_type; }

std::string_view ShortTradeMessage::name() const { return "Short Trade Message"; }

std::size_t ShortTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ShortTradeMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    security_symbol_5_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    sale_condition_1_ = static_cast<SaleCondition1>(wire::read_char(data + offset));
    offset += 1;

    sale_condition_category_ = static_cast<SaleConditionCategory>(wire::read_char(data + offset));
    offset += 1;

    trade_price_2_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    trade_volume_2_ = wire::read_u16_be(data + offset);
    offset += 2;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    consolidated_high_low_last_indicator_ = static_cast<ConsolidatedHighLowLastIndicator>(wire::read_char(data + offset));
    offset += 1;

    participant_open_high_low_last_indicator_ = static_cast<ParticipantOpenHighLowLastIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ShortTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ShortTradeMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_text(data + offset, 5, ' ', security_symbol_5_);
    offset += 5;

    wire::write_char(data + offset, static_cast<char>(sale_condition_1_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(sale_condition_category_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_price_2_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_volume_2_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(consolidated_high_low_last_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(participant_open_high_low_last_indicator_));
    offset += 1;

    return offset;
}

std::size_t ShortTradeMessage::encoded_size() const {
    return wire_size;
}

void ShortTradeMessage::accept(TradeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TradeMessagePayload> ShortTradeMessage::clone() const {
    return std::make_unique<ShortTradeMessage>(*this);
}

void ShortTradeMessage::print(std::ostream& out) const {
    out << "ShortTradeMessage{";
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
    out << ", security_symbol_5=";
    print::text(out, security_symbol_5_);
    out << ", sale_condition_1=";
    out << sale_condition_1_;
    out << ", sale_condition_category=";
    out << sale_condition_category_;
    out << ", trade_price_2=";
    out << trade_price_2_;
    out << ", trade_volume_2=";
    out << trade_volume_2_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", consolidated_high_low_last_indicator=";
    out << consolidated_high_low_last_indicator_;
    out << ", participant_open_high_low_last_indicator=";
    out << participant_open_high_low_last_indicator_;
    out << '}';
}

bool ShortTradeMessage::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const ShortTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ShortTradeMessage::operator==(const ShortTradeMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_5_ == other.security_symbol_5_
        && sale_condition_1_ == other.sale_condition_1_
        && sale_condition_category_ == other.sale_condition_category_
        && trade_price_2_ == other.trade_price_2_
        && trade_volume_2_ == other.trade_volume_2_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && consolidated_high_low_last_indicator_ == other.consolidated_high_low_last_indicator_
        && participant_open_high_low_last_indicator_ == other.participant_open_high_low_last_indicator_;
}

bool ShortTradeMessage::operator!=(const ShortTradeMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
