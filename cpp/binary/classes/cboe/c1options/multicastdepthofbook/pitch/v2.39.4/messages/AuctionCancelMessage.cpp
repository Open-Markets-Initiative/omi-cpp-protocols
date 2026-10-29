#include "AuctionCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

AuctionCancelMessage::AuctionCancelMessage(std::chrono::nanoseconds time_offset, std::uint64_t auction_id)
  : time_offset_(time_offset), auction_id_(auction_id) {}

std::chrono::nanoseconds AuctionCancelMessage::time_offset() const { return time_offset_; }
void AuctionCancelMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AuctionCancelMessage::auction_id() const { return auction_id_; }
void AuctionCancelMessage::set_auction_id(std::uint64_t value) { auction_id_ = value; }

MessageCode AuctionCancelMessage::type() const { return message_type; }

std::string_view AuctionCancelMessage::name() const { return "Auction Cancel Message"; }

std::size_t AuctionCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionCancelMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    auction_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t AuctionCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionCancelMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(auction_id_));
    offset += 8;

    return offset;
}

std::size_t AuctionCancelMessage::encoded_size() const {
    return wire_size;
}

void AuctionCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionCancelMessage::clone() const {
    return std::make_unique<AuctionCancelMessage>(*this);
}

void AuctionCancelMessage::print(std::ostream& out) const {
    out << "AuctionCancelMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", auction_id=";
    out << auction_id_;
    out << '}';
}

bool AuctionCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionCancelMessage::operator==(const AuctionCancelMessage& other) const {
    return time_offset_ == other.time_offset_
        && auction_id_ == other.auction_id_;
}

bool AuctionCancelMessage::operator!=(const AuctionCancelMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
