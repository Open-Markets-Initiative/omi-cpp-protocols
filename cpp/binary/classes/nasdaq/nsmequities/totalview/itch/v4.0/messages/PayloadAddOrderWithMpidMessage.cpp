#include "PayloadAddOrderWithMpidMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadAddOrderWithMpidMessage::PayloadAddOrderWithMpidMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, Side side, std::uint32_t shares, const std::string& stock, Decimal price, const std::string& attribution)
  : nanoseconds_(nanoseconds), order_reference_number_(order_reference_number), side_(side), shares_(shares), stock_(stock), price_(price), attribution_(attribution) {}

std::chrono::nanoseconds PayloadAddOrderWithMpidMessage::nanoseconds() const { return nanoseconds_; }
void PayloadAddOrderWithMpidMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t PayloadAddOrderWithMpidMessage::order_reference_number() const { return order_reference_number_; }
void PayloadAddOrderWithMpidMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

Side PayloadAddOrderWithMpidMessage::side() const { return side_; }
void PayloadAddOrderWithMpidMessage::set_side(Side value) { side_ = value; }

std::uint32_t PayloadAddOrderWithMpidMessage::shares() const { return shares_; }
void PayloadAddOrderWithMpidMessage::set_shares(std::uint32_t value) { shares_ = value; }

const std::string& PayloadAddOrderWithMpidMessage::stock() const { return stock_; }
std::string& PayloadAddOrderWithMpidMessage::stock() { return stock_; }
void PayloadAddOrderWithMpidMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal PayloadAddOrderWithMpidMessage::price() const { return price_; }
void PayloadAddOrderWithMpidMessage::set_price(Decimal value) { price_ = value; }

const std::string& PayloadAddOrderWithMpidMessage::attribution() const { return attribution_; }
std::string& PayloadAddOrderWithMpidMessage::attribution() { return attribution_; }
void PayloadAddOrderWithMpidMessage::set_attribution(const std::string& value) { attribution_ = value; }

PacketMessageCode PayloadAddOrderWithMpidMessage::type() const { return message_type; }

std::string_view PayloadAddOrderWithMpidMessage::name() const { return "Add Order With Mpid Message"; }

std::size_t PayloadAddOrderWithMpidMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadAddOrderWithMpidMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    stock_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    attribution_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t PayloadAddOrderWithMpidMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadAddOrderWithMpidMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(shares_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', stock_);
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', attribution_);
    offset += 4;

    return offset;
}

std::size_t PayloadAddOrderWithMpidMessage::encoded_size() const {
    return wire_size;
}

void PayloadAddOrderWithMpidMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadAddOrderWithMpidMessage::clone() const {
    return std::make_unique<PayloadAddOrderWithMpidMessage>(*this);
}

void PayloadAddOrderWithMpidMessage::print(std::ostream& out) const {
    out << "PayloadAddOrderWithMpidMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", side=";
    out << side_;
    out << ", shares=";
    out << shares_;
    out << ", stock=";
    print::text(out, stock_);
    out << ", price=";
    out << price_;
    out << ", attribution=";
    print::text(out, attribution_);
    out << '}';
}

bool PayloadAddOrderWithMpidMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadAddOrderWithMpidMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadAddOrderWithMpidMessage::operator==(const PayloadAddOrderWithMpidMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_reference_number_ == other.order_reference_number_
        && side_ == other.side_
        && shares_ == other.shares_
        && stock_ == other.stock_
        && price_ == other.price_
        && attribution_ == other.attribution_;
}

bool PayloadAddOrderWithMpidMessage::operator!=(const PayloadAddOrderWithMpidMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
