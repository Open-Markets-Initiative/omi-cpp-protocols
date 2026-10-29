#include "ShortSellingPriceRestrictionStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

ShortSellingPriceRestrictionStateMessage::ShortSellingPriceRestrictionStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& group, ShortSellingState short_selling_state)
  : nanoseconds_(nanoseconds), orderbook_id_(orderbook_id), group_(group), short_selling_state_(short_selling_state) {}

std::chrono::nanoseconds ShortSellingPriceRestrictionStateMessage::nanoseconds() const { return nanoseconds_; }
void ShortSellingPriceRestrictionStateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t ShortSellingPriceRestrictionStateMessage::orderbook_id() const { return orderbook_id_; }
void ShortSellingPriceRestrictionStateMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& ShortSellingPriceRestrictionStateMessage::group() const { return group_; }
std::string& ShortSellingPriceRestrictionStateMessage::group() { return group_; }
void ShortSellingPriceRestrictionStateMessage::set_group(const std::string& value) { group_ = value; }

ShortSellingState ShortSellingPriceRestrictionStateMessage::short_selling_state() const { return short_selling_state_; }
void ShortSellingPriceRestrictionStateMessage::set_short_selling_state(ShortSellingState value) { short_selling_state_ = value; }

MessageCode ShortSellingPriceRestrictionStateMessage::type() const { return message_type; }

std::string_view ShortSellingPriceRestrictionStateMessage::name() const { return "Short Selling Price Restriction State Message"; }

std::size_t ShortSellingPriceRestrictionStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ShortSellingPriceRestrictionStateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    orderbook_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    group_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    short_selling_state_ = static_cast<ShortSellingState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ShortSellingPriceRestrictionStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ShortSellingPriceRestrictionStateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(orderbook_id_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', group_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(short_selling_state_));
    offset += 1;

    return offset;
}

std::size_t ShortSellingPriceRestrictionStateMessage::encoded_size() const {
    return wire_size;
}

void ShortSellingPriceRestrictionStateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ShortSellingPriceRestrictionStateMessage::clone() const {
    return std::make_unique<ShortSellingPriceRestrictionStateMessage>(*this);
}

void ShortSellingPriceRestrictionStateMessage::print(std::ostream& out) const {
    out << "ShortSellingPriceRestrictionStateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", orderbook_id=";
    out << orderbook_id_;
    out << ", group=";
    print::text(out, group_);
    out << ", short_selling_state=";
    out << short_selling_state_;
    out << '}';
}

bool ShortSellingPriceRestrictionStateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ShortSellingPriceRestrictionStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ShortSellingPriceRestrictionStateMessage::operator==(const ShortSellingPriceRestrictionStateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && short_selling_state_ == other.short_selling_state_;
}

bool ShortSellingPriceRestrictionStateMessage::operator!=(const ShortSellingPriceRestrictionStateMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_6
