#include "UdpPayloadAddOrderMessageShortMessageForm.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadAddOrderMessageShortMessageForm::UdpPayloadAddOrderMessageShortMessageForm(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, MarketSide market_side, std::uint32_t option_id, Decimal price_short, std::uint16_t volume_short)
  : tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), market_side_(market_side), option_id_(option_id), price_short_(price_short), volume_short_(volume_short) {}

std::uint16_t UdpPayloadAddOrderMessageShortMessageForm::tracking_number() const { return tracking_number_; }
void UdpPayloadAddOrderMessageShortMessageForm::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadAddOrderMessageShortMessageForm::timestamp() const { return timestamp_; }
void UdpPayloadAddOrderMessageShortMessageForm::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t UdpPayloadAddOrderMessageShortMessageForm::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t UdpPayloadAddOrderMessageShortMessageForm::order_reference_number() const { return order_reference_number_; }
void UdpPayloadAddOrderMessageShortMessageForm::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

MarketSide UdpPayloadAddOrderMessageShortMessageForm::market_side() const { return market_side_; }
void UdpPayloadAddOrderMessageShortMessageForm::set_market_side(MarketSide value) { market_side_ = value; }

std::uint32_t UdpPayloadAddOrderMessageShortMessageForm::option_id() const { return option_id_; }
void UdpPayloadAddOrderMessageShortMessageForm::set_option_id(std::uint32_t value) { option_id_ = value; }

Decimal UdpPayloadAddOrderMessageShortMessageForm::price_short() const { return price_short_; }
void UdpPayloadAddOrderMessageShortMessageForm::set_price_short(Decimal value) { price_short_ = value; }

std::uint16_t UdpPayloadAddOrderMessageShortMessageForm::volume_short() const { return volume_short_; }
void UdpPayloadAddOrderMessageShortMessageForm::set_volume_short(std::uint16_t value) { volume_short_ = value; }

PacketMessageCode UdpPayloadAddOrderMessageShortMessageForm::type() const { return message_type; }

std::string_view UdpPayloadAddOrderMessageShortMessageForm::name() const { return "Add Order Message Short Message Form"; }

std::size_t UdpPayloadAddOrderMessageShortMessageForm::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadAddOrderMessageShortMessageForm", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    market_side_ = static_cast<MarketSide>(wire::read_char(data + offset));
    offset += 1;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -4);
    offset += 2;

    volume_short_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t UdpPayloadAddOrderMessageShortMessageForm::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadAddOrderMessageShortMessageForm", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(price_short_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(volume_short_));
    offset += 2;

    return offset;
}

std::size_t UdpPayloadAddOrderMessageShortMessageForm::encoded_size() const {
    return wire_size;
}

void UdpPayloadAddOrderMessageShortMessageForm::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadAddOrderMessageShortMessageForm::clone() const {
    return std::make_unique<UdpPayloadAddOrderMessageShortMessageForm>(*this);
}

void UdpPayloadAddOrderMessageShortMessageForm::print(std::ostream& out) const {
    out << "UdpPayloadAddOrderMessageShortMessageForm{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", market_side=";
    out << market_side_;
    out << ", option_id=";
    out << option_id_;
    out << ", price_short=";
    out << price_short_;
    out << ", volume_short=";
    out << volume_short_;
    out << '}';
}

bool UdpPayloadAddOrderMessageShortMessageForm::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadAddOrderMessageShortMessageForm*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadAddOrderMessageShortMessageForm::operator==(const UdpPayloadAddOrderMessageShortMessageForm& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && market_side_ == other.market_side_
        && option_id_ == other.option_id_
        && price_short_ == other.price_short_
        && volume_short_ == other.volume_short_;
}

bool UdpPayloadAddOrderMessageShortMessageForm::operator!=(const UdpPayloadAddOrderMessageShortMessageForm& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
