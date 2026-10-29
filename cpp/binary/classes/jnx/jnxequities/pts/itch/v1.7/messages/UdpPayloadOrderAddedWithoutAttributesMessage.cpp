#include "UdpPayloadOrderAddedWithoutAttributesMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadOrderAddedWithoutAttributesMessage::UdpPayloadOrderAddedWithoutAttributesMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price)
  : nanoseconds_(nanoseconds), order_number_(order_number), buy_sell_indicator_(buy_sell_indicator), quantity_(quantity), orderbook_id_(orderbook_id), group_(group), price_(price) {}

std::chrono::nanoseconds UdpPayloadOrderAddedWithoutAttributesMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadOrderAddedWithoutAttributesMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t UdpPayloadOrderAddedWithoutAttributesMessage::order_number() const { return order_number_; }
void UdpPayloadOrderAddedWithoutAttributesMessage::set_order_number(std::uint64_t value) { order_number_ = value; }

BuySellIndicator UdpPayloadOrderAddedWithoutAttributesMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void UdpPayloadOrderAddedWithoutAttributesMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t UdpPayloadOrderAddedWithoutAttributesMessage::quantity() const { return quantity_; }
void UdpPayloadOrderAddedWithoutAttributesMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t UdpPayloadOrderAddedWithoutAttributesMessage::orderbook_id() const { return orderbook_id_; }
void UdpPayloadOrderAddedWithoutAttributesMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& UdpPayloadOrderAddedWithoutAttributesMessage::group() const { return group_; }
std::string& UdpPayloadOrderAddedWithoutAttributesMessage::group() { return group_; }
void UdpPayloadOrderAddedWithoutAttributesMessage::set_group(const std::string& value) { group_ = value; }

Decimal UdpPayloadOrderAddedWithoutAttributesMessage::price() const { return price_; }
void UdpPayloadOrderAddedWithoutAttributesMessage::set_price(Decimal value) { price_ = value; }

PacketMessageCode UdpPayloadOrderAddedWithoutAttributesMessage::type() const { return message_type; }

std::string_view UdpPayloadOrderAddedWithoutAttributesMessage::name() const { return "Order Added Without Attributes Message"; }

std::size_t UdpPayloadOrderAddedWithoutAttributesMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOrderAddedWithoutAttributesMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    buy_sell_indicator_ = static_cast<BuySellIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    group_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderAddedWithoutAttributesMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOrderAddedWithoutAttributesMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(buy_sell_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(orderbook_id_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', group_);
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t UdpPayloadOrderAddedWithoutAttributesMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOrderAddedWithoutAttributesMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOrderAddedWithoutAttributesMessage::clone() const {
    return std::make_unique<UdpPayloadOrderAddedWithoutAttributesMessage>(*this);
}

void UdpPayloadOrderAddedWithoutAttributesMessage::print(std::ostream& out) const {
    out << "UdpPayloadOrderAddedWithoutAttributesMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_number=";
    out << order_number_;
    out << ", buy_sell_indicator=";
    out << buy_sell_indicator_;
    out << ", quantity=";
    out << quantity_;
    out << ", orderbook_id=";
    out << orderbook_id_;
    out << ", group=";
    print::text(out, group_);
    out << ", price=";
    out << price_;
    out << '}';
}

bool UdpPayloadOrderAddedWithoutAttributesMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOrderAddedWithoutAttributesMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOrderAddedWithoutAttributesMessage::operator==(const UdpPayloadOrderAddedWithoutAttributesMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_number_ == other.order_number_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && quantity_ == other.quantity_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && price_ == other.price_;
}

bool UdpPayloadOrderAddedWithoutAttributesMessage::operator!=(const UdpPayloadOrderAddedWithoutAttributesMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
