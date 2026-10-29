#include "AuctionStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_10 {

AuctionStatusMessage::AuctionStatusMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, Decimal auction_collar_reference_price, Decimal auction_collar_upper_threshold_price, Decimal auction_collar_lower_threshold_price, std::uint8_t number_of_extensions, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, const std::string& future_use)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), auction_collar_reference_price_(auction_collar_reference_price), auction_collar_upper_threshold_price_(auction_collar_upper_threshold_price), auction_collar_lower_threshold_price_(auction_collar_lower_threshold_price), number_of_extensions_(number_of_extensions), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), future_use_(future_use) {}

ParticipantId AuctionStatusMessage::participant_id() const { return participant_id_; }
void AuctionStatusMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& AuctionStatusMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& AuctionStatusMessage::timestamp_1() { return timestamp_1_; }
void AuctionStatusMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t AuctionStatusMessage::message_id() const { return message_id_; }
void AuctionStatusMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t AuctionStatusMessage::transaction_id() const { return transaction_id_; }
void AuctionStatusMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t AuctionStatusMessage::participant_reference_number() const { return participant_reference_number_; }
void AuctionStatusMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& AuctionStatusMessage::security_symbol() const { return security_symbol_; }
std::string& AuctionStatusMessage::security_symbol() { return security_symbol_; }
void AuctionStatusMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType AuctionStatusMessage::instrument_type() const { return instrument_type_; }
void AuctionStatusMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

Decimal AuctionStatusMessage::auction_collar_reference_price() const { return auction_collar_reference_price_; }
void AuctionStatusMessage::set_auction_collar_reference_price(Decimal value) { auction_collar_reference_price_ = value; }

Decimal AuctionStatusMessage::auction_collar_upper_threshold_price() const { return auction_collar_upper_threshold_price_; }
void AuctionStatusMessage::set_auction_collar_upper_threshold_price(Decimal value) { auction_collar_upper_threshold_price_ = value; }

Decimal AuctionStatusMessage::auction_collar_lower_threshold_price() const { return auction_collar_lower_threshold_price_; }
void AuctionStatusMessage::set_auction_collar_lower_threshold_price(Decimal value) { auction_collar_lower_threshold_price_ = value; }

std::uint8_t AuctionStatusMessage::number_of_extensions() const { return number_of_extensions_; }
void AuctionStatusMessage::set_number_of_extensions(std::uint8_t value) { number_of_extensions_ = value; }

ShortSaleRestrictionIndicator AuctionStatusMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void AuctionStatusMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId AuctionStatusMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void AuctionStatusMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator AuctionStatusMessage::financial_status_indicator() const { return financial_status_indicator_; }
void AuctionStatusMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

const std::string& AuctionStatusMessage::future_use() const { return future_use_; }
std::string& AuctionStatusMessage::future_use() { return future_use_; }
void AuctionStatusMessage::set_future_use(const std::string& value) { future_use_ = value; }

TradeMessagePayloadCode AuctionStatusMessage::type() const { return message_type; }

std::string_view AuctionStatusMessage::name() const { return "Auction Status Message"; }

std::size_t AuctionStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionStatusMessage", wire_size, length);

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

    auction_collar_reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    auction_collar_upper_threshold_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    auction_collar_lower_threshold_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    number_of_extensions_ = wire::read_u8(data + offset);
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    future_use_ = wire::read_text(data + offset, 62, ' ');
    offset += 62;

    return offset;
}

std::size_t AuctionStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionStatusMessage", wire_size, capacity);

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

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(auction_collar_reference_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(auction_collar_upper_threshold_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(auction_collar_lower_threshold_price_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_extensions_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_text(data + offset, 62, ' ', future_use_);
    offset += 62;

    return offset;
}

std::size_t AuctionStatusMessage::encoded_size() const {
    return wire_size;
}

void AuctionStatusMessage::accept(TradeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TradeMessagePayload> AuctionStatusMessage::clone() const {
    return std::make_unique<AuctionStatusMessage>(*this);
}

void AuctionStatusMessage::print(std::ostream& out) const {
    out << "AuctionStatusMessage{";
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
    out << ", auction_collar_reference_price=";
    out << auction_collar_reference_price_;
    out << ", auction_collar_upper_threshold_price=";
    out << auction_collar_upper_threshold_price_;
    out << ", auction_collar_lower_threshold_price=";
    out << auction_collar_lower_threshold_price_;
    out << ", number_of_extensions=";
    out << static_cast<int>(number_of_extensions_);
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", future_use=";
    print::text(out, future_use_);
    out << '}';
}

bool AuctionStatusMessage::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const AuctionStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionStatusMessage::operator==(const AuctionStatusMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && auction_collar_reference_price_ == other.auction_collar_reference_price_
        && auction_collar_upper_threshold_price_ == other.auction_collar_upper_threshold_price_
        && auction_collar_lower_threshold_price_ == other.auction_collar_lower_threshold_price_
        && number_of_extensions_ == other.number_of_extensions_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && future_use_ == other.future_use_;
}

bool AuctionStatusMessage::operator!=(const AuctionStatusMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_10
