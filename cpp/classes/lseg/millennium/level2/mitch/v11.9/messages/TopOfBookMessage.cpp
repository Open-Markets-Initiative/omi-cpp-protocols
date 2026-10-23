#include "TopOfBookMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

TopOfBookMessage::TopOfBookMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, std::int64_t buy_limit_price, std::uint32_t buy_limit_size, std::int64_t sell_limit_price, std::uint32_t sell_limit_size)
  : nanosecond_(nanosecond), instrument_id_(instrument_id), buy_limit_price_(buy_limit_price), buy_limit_size_(buy_limit_size), sell_limit_price_(sell_limit_price), sell_limit_size_(sell_limit_size) {}

std::uint32_t TopOfBookMessage::nanosecond() const { return nanosecond_; }
void TopOfBookMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t TopOfBookMessage::instrument_id() const { return instrument_id_; }
void TopOfBookMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

std::int64_t TopOfBookMessage::buy_limit_price() const { return buy_limit_price_; }
void TopOfBookMessage::set_buy_limit_price(std::int64_t value) { buy_limit_price_ = value; }

std::uint32_t TopOfBookMessage::buy_limit_size() const { return buy_limit_size_; }
void TopOfBookMessage::set_buy_limit_size(std::uint32_t value) { buy_limit_size_ = value; }

std::int64_t TopOfBookMessage::sell_limit_price() const { return sell_limit_price_; }
void TopOfBookMessage::set_sell_limit_price(std::int64_t value) { sell_limit_price_ = value; }

std::uint32_t TopOfBookMessage::sell_limit_size() const { return sell_limit_size_; }
void TopOfBookMessage::set_sell_limit_size(std::uint32_t value) { sell_limit_size_ = value; }

MessageCode TopOfBookMessage::type() const { return message_type; }

std::string_view TopOfBookMessage::name() const { return "Top Of Book Message"; }

std::size_t TopOfBookMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TopOfBookMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    buy_limit_price_ = wire::read_i64_le(data + offset);
    offset += 8;

    buy_limit_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    sell_limit_price_ = wire::read_i64_le(data + offset);
    offset += 8;

    sell_limit_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TopOfBookMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TopOfBookMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(buy_limit_price_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(buy_limit_size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(sell_limit_price_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sell_limit_size_));
    offset += 4;

    return offset;
}

std::size_t TopOfBookMessage::encoded_size() const {
    return wire_size;
}

void TopOfBookMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TopOfBookMessage::clone() const {
    return std::make_unique<TopOfBookMessage>(*this);
}

void TopOfBookMessage::print(std::ostream& out) const {
    out << "TopOfBookMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", buy_limit_price=";
    out << buy_limit_price_;
    out << ", buy_limit_size=";
    out << buy_limit_size_;
    out << ", sell_limit_price=";
    out << sell_limit_price_;
    out << ", sell_limit_size=";
    out << sell_limit_size_;
    out << '}';
}

bool TopOfBookMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TopOfBookMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TopOfBookMessage::operator==(const TopOfBookMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && instrument_id_ == other.instrument_id_
        && buy_limit_price_ == other.buy_limit_price_
        && buy_limit_size_ == other.buy_limit_size_
        && sell_limit_price_ == other.sell_limit_price_
        && sell_limit_size_ == other.sell_limit_size_;
}

bool TopOfBookMessage::operator!=(const TopOfBookMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
