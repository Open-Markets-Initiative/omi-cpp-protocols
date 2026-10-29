#include "AddOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

AddOrderMessage::AddOrderMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, Side side, std::uint32_t shares, const std::string& stock, Decimal price)
  : nanoseconds_(nanoseconds), order_reference_number_(order_reference_number), side_(side), shares_(shares), stock_(stock), price_(price) {}

std::chrono::nanoseconds AddOrderMessage::nanoseconds() const { return nanoseconds_; }
void AddOrderMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t AddOrderMessage::order_reference_number() const { return order_reference_number_; }
void AddOrderMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

Side AddOrderMessage::side() const { return side_; }
void AddOrderMessage::set_side(Side value) { side_ = value; }

std::uint32_t AddOrderMessage::shares() const { return shares_; }
void AddOrderMessage::set_shares(std::uint32_t value) { shares_ = value; }

const std::string& AddOrderMessage::stock() const { return stock_; }
std::string& AddOrderMessage::stock() { return stock_; }
void AddOrderMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal AddOrderMessage::price() const { return price_; }
void AddOrderMessage::set_price(Decimal value) { price_ = value; }

SequencedMessageCode AddOrderMessage::type() const { return message_type; }

std::string_view AddOrderMessage::name() const { return "Add Order Message"; }

std::size_t AddOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderMessage", wire_size, length);

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

    return offset;
}

std::size_t AddOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderMessage", wire_size, capacity);

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

    return offset;
}

std::size_t AddOrderMessage::encoded_size() const {
    return wire_size;
}

void AddOrderMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> AddOrderMessage::clone() const {
    return std::make_unique<AddOrderMessage>(*this);
}

void AddOrderMessage::print(std::ostream& out) const {
    out << "AddOrderMessage{";
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
    out << '}';
}

bool AddOrderMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const AddOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderMessage::operator==(const AddOrderMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_reference_number_ == other.order_reference_number_
        && side_ == other.side_
        && shares_ == other.shares_
        && stock_ == other.stock_
        && price_ == other.price_;
}

bool AddOrderMessage::operator!=(const AddOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
