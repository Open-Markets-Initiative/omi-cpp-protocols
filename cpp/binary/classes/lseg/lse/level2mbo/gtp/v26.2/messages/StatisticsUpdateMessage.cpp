#include "StatisticsUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

StatisticsUpdateMessage::StatisticsUpdateMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, SourceVenue source_venue, StatisticType statistic_type, Decimal statistic_price, Decimal statistic_size, AuctionType auction_type, Decimal imbalance_quantity, AuctionInfo auction_info, OpeningClosingPriceIndicator opening_closing_price_indicator)
  : timestamp_(timestamp), instrument_(instrument), source_venue_(source_venue), statistic_type_(statistic_type), statistic_price_(statistic_price), statistic_size_(statistic_size), auction_type_(auction_type), imbalance_quantity_(imbalance_quantity), auction_info_(auction_info), opening_closing_price_indicator_(opening_closing_price_indicator) {}

std::chrono::nanoseconds StatisticsUpdateMessage::timestamp() const { return timestamp_; }
void StatisticsUpdateMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t StatisticsUpdateMessage::instrument() const { return instrument_; }
void StatisticsUpdateMessage::set_instrument(std::uint64_t value) { instrument_ = value; }

SourceVenue StatisticsUpdateMessage::source_venue() const { return source_venue_; }
void StatisticsUpdateMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

StatisticType StatisticsUpdateMessage::statistic_type() const { return statistic_type_; }
void StatisticsUpdateMessage::set_statistic_type(StatisticType value) { statistic_type_ = value; }

Decimal StatisticsUpdateMessage::statistic_price() const { return statistic_price_; }
void StatisticsUpdateMessage::set_statistic_price(Decimal value) { statistic_price_ = value; }

Decimal StatisticsUpdateMessage::statistic_size() const { return statistic_size_; }
void StatisticsUpdateMessage::set_statistic_size(Decimal value) { statistic_size_ = value; }

AuctionType StatisticsUpdateMessage::auction_type() const { return auction_type_; }
void StatisticsUpdateMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

Decimal StatisticsUpdateMessage::imbalance_quantity() const { return imbalance_quantity_; }
void StatisticsUpdateMessage::set_imbalance_quantity(Decimal value) { imbalance_quantity_ = value; }

AuctionInfo StatisticsUpdateMessage::auction_info() const { return auction_info_; }
void StatisticsUpdateMessage::set_auction_info(AuctionInfo value) { auction_info_ = value; }

OpeningClosingPriceIndicator StatisticsUpdateMessage::opening_closing_price_indicator() const { return opening_closing_price_indicator_; }
void StatisticsUpdateMessage::set_opening_closing_price_indicator(OpeningClosingPriceIndicator value) { opening_closing_price_indicator_ = value; }

MessageCode StatisticsUpdateMessage::type() const { return message_type; }

std::string_view StatisticsUpdateMessage::name() const { return "Statistics Update Message"; }

std::size_t StatisticsUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StatisticsUpdateMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_ = wire::read_u64_le(data + offset);
    offset += 8;

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    statistic_type_ = static_cast<StatisticType>(wire::read_u16_le(data + offset));
    offset += 2;

    statistic_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    statistic_size_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -8);
    offset += 8;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    imbalance_quantity_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -8);
    offset += 8;

    auction_info_ = static_cast<AuctionInfo>(wire::read_char(data + offset));
    offset += 1;

    opening_closing_price_indicator_ = static_cast<OpeningClosingPriceIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t StatisticsUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StatisticsUpdateMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(instrument_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(statistic_type_));
    offset += 2;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(statistic_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(statistic_size_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(imbalance_quantity_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_info_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(opening_closing_price_indicator_));
    offset += 1;

    return offset;
}

std::size_t StatisticsUpdateMessage::encoded_size() const {
    return wire_size;
}

void StatisticsUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StatisticsUpdateMessage::clone() const {
    return std::make_unique<StatisticsUpdateMessage>(*this);
}

void StatisticsUpdateMessage::print(std::ostream& out) const {
    out << "StatisticsUpdateMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument=";
    out << instrument_;
    out << ", source_venue=";
    out << source_venue_;
    out << ", statistic_type=";
    out << statistic_type_;
    out << ", statistic_price=";
    out << statistic_price_;
    out << ", statistic_size=";
    out << statistic_size_;
    out << ", auction_type=";
    out << auction_type_;
    out << ", imbalance_quantity=";
    out << imbalance_quantity_;
    out << ", auction_info=";
    out << auction_info_;
    out << ", opening_closing_price_indicator=";
    out << opening_closing_price_indicator_;
    out << '}';
}

bool StatisticsUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StatisticsUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StatisticsUpdateMessage::operator==(const StatisticsUpdateMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_ == other.instrument_
        && source_venue_ == other.source_venue_
        && statistic_type_ == other.statistic_type_
        && statistic_price_ == other.statistic_price_
        && statistic_size_ == other.statistic_size_
        && auction_type_ == other.auction_type_
        && imbalance_quantity_ == other.imbalance_quantity_
        && auction_info_ == other.auction_info_
        && opening_closing_price_indicator_ == other.opening_closing_price_indicator_;
}

bool StatisticsUpdateMessage::operator!=(const StatisticsUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
