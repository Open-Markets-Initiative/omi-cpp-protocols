#include "UdpPayloadOrderAddedWithAttributesMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadOrderAddedWithAttributesMessage::UdpPayloadOrderAddedWithAttributesMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price, const std::string& attribution, OrderType order_type)
  : nanoseconds_(nanoseconds), order_number_(order_number), buy_sell_indicator_(buy_sell_indicator), quantity_(quantity), orderbook_id_(orderbook_id), group_(group), price_(price), attribution_(attribution), order_type_(order_type) {}

std::chrono::nanoseconds UdpPayloadOrderAddedWithAttributesMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t UdpPayloadOrderAddedWithAttributesMessage::order_number() const { return order_number_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_order_number(std::uint64_t value) { order_number_ = value; }

BuySellIndicator UdpPayloadOrderAddedWithAttributesMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t UdpPayloadOrderAddedWithAttributesMessage::quantity() const { return quantity_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t UdpPayloadOrderAddedWithAttributesMessage::orderbook_id() const { return orderbook_id_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& UdpPayloadOrderAddedWithAttributesMessage::group() const { return group_; }
std::string& UdpPayloadOrderAddedWithAttributesMessage::group() { return group_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_group(const std::string& value) { group_ = value; }

Decimal UdpPayloadOrderAddedWithAttributesMessage::price() const { return price_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_price(Decimal value) { price_ = value; }

const std::string& UdpPayloadOrderAddedWithAttributesMessage::attribution() const { return attribution_; }
std::string& UdpPayloadOrderAddedWithAttributesMessage::attribution() { return attribution_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_attribution(const std::string& value) { attribution_ = value; }

OrderType UdpPayloadOrderAddedWithAttributesMessage::order_type() const { return order_type_; }
void UdpPayloadOrderAddedWithAttributesMessage::set_order_type(OrderType value) { order_type_ = value; }

PacketMessageCode UdpPayloadOrderAddedWithAttributesMessage::type() const { return message_type; }

std::string_view UdpPayloadOrderAddedWithAttributesMessage::name() const { return "Order Added With Attributes Message"; }

std::size_t UdpPayloadOrderAddedWithAttributesMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadOrderAddedWithAttributesMessage", wire_size, length);

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

    attribution_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    order_type_ = static_cast<OrderType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadOrderAddedWithAttributesMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadOrderAddedWithAttributesMessage", wire_size, capacity);

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

    wire::write_text(data + offset, 4, ' ', attribution_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(order_type_));
    offset += 1;

    return offset;
}

std::size_t UdpPayloadOrderAddedWithAttributesMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadOrderAddedWithAttributesMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadOrderAddedWithAttributesMessage::clone() const {
    return std::make_unique<UdpPayloadOrderAddedWithAttributesMessage>(*this);
}

void UdpPayloadOrderAddedWithAttributesMessage::print(std::ostream& out) const {
    out << "UdpPayloadOrderAddedWithAttributesMessage{";
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
    out << ", attribution=";
    print::text(out, attribution_);
    out << ", order_type=";
    out << order_type_;
    out << '}';
}

bool UdpPayloadOrderAddedWithAttributesMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadOrderAddedWithAttributesMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadOrderAddedWithAttributesMessage::operator==(const UdpPayloadOrderAddedWithAttributesMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_number_ == other.order_number_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && quantity_ == other.quantity_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && price_ == other.price_
        && attribution_ == other.attribution_
        && order_type_ == other.order_type_;
}

bool UdpPayloadOrderAddedWithAttributesMessage::operator!=(const UdpPayloadOrderAddedWithAttributesMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
