#include "UdpPayloadOptionsTradeMessagesNonAuction.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadOptionsTradeMessagesNonAuction::UdpPayloadOptionsTradeMessagesNonAuction(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, BuySellIndicator buy_sell_indicator, std::uint32_t option_id, std::uint32_t cross_number, std::uint32_t match_number, Decimal price_long, std::uint32_t volume_long)
  : tracking_number_(tracking_number), timestamp_(timestamp), buy_sell_indicator_(buy_sell_indicator), option_id_(option_id), cross_number_(cross_number), match_number_(match_number), price_long_(price_long), volume_long_(volume_long) {}

std::uint16_t UdpPayloadOptionsTradeMessagesNonAuction::tracking_number() const { return tracking_number_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadOptionsTradeMessagesNonAuction::timestamp() const { return timestamp_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

BuySellIndicator UdpPayloadOptionsTradeMessagesNonAuction::buy_sell_indicator() const { return buy_sell_indicator_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t UdpPayloadOptionsTradeMessagesNonAuction::option_id() const { return option_id_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_option_id(std::uint32_t value) { option_id_ = value; }

std::uint32_t UdpPayloadOptionsTradeMessagesNonAuction::cross_number() const { return cross_number_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_cross_number(std::uint32_t value) { cross_number_ = value; }

std::uint32_t UdpPayloadOptionsTradeMessagesNonAuction::match_number() const { return match_number_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_match_number(std::uint32_t value) { match_number_ = value; }

Decimal UdpPayloadOptionsTradeMessagesNonAuction::price_long() const { return price_long_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_price_long(Decimal value) { price_long_ = value; }

std::uint32_t UdpPayloadOptionsTradeMessagesNonAuction::volume_long() const { return volume_long_; }
void UdpPayloadOptionsTradeMessagesNonAuction::set_volume_long(std::uint32_t value) { volume_long_ = value; }

PacketMessageCode UdpPayloadOptionsTradeMessagesNonAuction::type() const { return message_type; }

std::string_view UdpPayloadOptionsTradeMessagesNonAuction::name() const { return "Options Trade Messages Non Auction"; }

std::size_t UdpPayloadOptionsTradeMessagesNonAuction::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOptionsTradeMessagesNonAuction", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    buy_sell_indicator_ = static_cast<BuySellIndicator>(wire::read_char(data + offset));
    offset += 1;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    cross_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    volume_long_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOptionsTradeMessagesNonAuction::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOptionsTradeMessagesNonAuction", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_char(data + offset, static_cast<char>(buy_sell_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_long_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_long_));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOptionsTradeMessagesNonAuction::encoded_size() const {
    return wire_size;
}

void UdpPayloadOptionsTradeMessagesNonAuction::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOptionsTradeMessagesNonAuction::clone() const {
    return std::make_unique<UdpPayloadOptionsTradeMessagesNonAuction>(*this);
}

void UdpPayloadOptionsTradeMessagesNonAuction::print(std::ostream& out) const {
    out << "UdpPayloadOptionsTradeMessagesNonAuction{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", buy_sell_indicator=";
    out << buy_sell_indicator_;
    out << ", option_id=";
    out << option_id_;
    out << ", cross_number=";
    out << cross_number_;
    out << ", match_number=";
    out << match_number_;
    out << ", price_long=";
    out << price_long_;
    out << ", volume_long=";
    out << volume_long_;
    out << '}';
}

bool UdpPayloadOptionsTradeMessagesNonAuction::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOptionsTradeMessagesNonAuction*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOptionsTradeMessagesNonAuction::operator==(const UdpPayloadOptionsTradeMessagesNonAuction& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && option_id_ == other.option_id_
        && cross_number_ == other.cross_number_
        && match_number_ == other.match_number_
        && price_long_ == other.price_long_
        && volume_long_ == other.volume_long_;
}

bool UdpPayloadOptionsTradeMessagesNonAuction::operator!=(const UdpPayloadOptionsTradeMessagesNonAuction& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
