#include "UdpPayloadShortSellingPriceRestrictionStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

UdpPayloadShortSellingPriceRestrictionStateMessage::UdpPayloadShortSellingPriceRestrictionStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t orderbook_id, const std::string& group, ShortSellingState short_selling_state)
  : nanoseconds_(nanoseconds), orderbook_id_(orderbook_id), group_(group), short_selling_state_(short_selling_state) {}

std::chrono::nanoseconds UdpPayloadShortSellingPriceRestrictionStateMessage::nanoseconds() const { return nanoseconds_; }
void UdpPayloadShortSellingPriceRestrictionStateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t UdpPayloadShortSellingPriceRestrictionStateMessage::orderbook_id() const { return orderbook_id_; }
void UdpPayloadShortSellingPriceRestrictionStateMessage::set_orderbook_id(std::uint32_t value) { orderbook_id_ = value; }

const std::string& UdpPayloadShortSellingPriceRestrictionStateMessage::group() const { return group_; }
std::string& UdpPayloadShortSellingPriceRestrictionStateMessage::group() { return group_; }
void UdpPayloadShortSellingPriceRestrictionStateMessage::set_group(const std::string& value) { group_ = value; }

ShortSellingState UdpPayloadShortSellingPriceRestrictionStateMessage::short_selling_state() const { return short_selling_state_; }
void UdpPayloadShortSellingPriceRestrictionStateMessage::set_short_selling_state(ShortSellingState value) { short_selling_state_ = value; }

PacketMessageCode UdpPayloadShortSellingPriceRestrictionStateMessage::type() const { return message_type; }

std::string_view UdpPayloadShortSellingPriceRestrictionStateMessage::name() const { return "Short Selling Price Restriction State Message"; }

std::size_t UdpPayloadShortSellingPriceRestrictionStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadShortSellingPriceRestrictionStateMessage", wire_size, length);

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

std::size_t UdpPayloadShortSellingPriceRestrictionStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadShortSellingPriceRestrictionStateMessage", wire_size, capacity);

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

std::size_t UdpPayloadShortSellingPriceRestrictionStateMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadShortSellingPriceRestrictionStateMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadShortSellingPriceRestrictionStateMessage::clone() const {
    return std::make_unique<UdpPayloadShortSellingPriceRestrictionStateMessage>(*this);
}

void UdpPayloadShortSellingPriceRestrictionStateMessage::print(std::ostream& out) const {
    out << "UdpPayloadShortSellingPriceRestrictionStateMessage{";
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

bool UdpPayloadShortSellingPriceRestrictionStateMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadShortSellingPriceRestrictionStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadShortSellingPriceRestrictionStateMessage::operator==(const UdpPayloadShortSellingPriceRestrictionStateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && orderbook_id_ == other.orderbook_id_
        && group_ == other.group_
        && short_selling_state_ == other.short_selling_state_;
}

bool UdpPayloadShortSellingPriceRestrictionStateMessage::operator!=(const UdpPayloadShortSellingPriceRestrictionStateMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
