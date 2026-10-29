#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

PacketHeader::PacketHeader(const std::string& market_day_identifier, FeedIdentifier feed_identifier, std::uint64_t sequence, std::uint16_t count)
  : market_day_identifier_(market_day_identifier), feed_identifier_(feed_identifier), sequence_(sequence), count_(count) {}

const std::string& PacketHeader::market_day_identifier() const { return market_day_identifier_; }
std::string& PacketHeader::market_day_identifier() { return market_day_identifier_; }
void PacketHeader::set_market_day_identifier(const std::string& value) { market_day_identifier_ = value; }

FeedIdentifier PacketHeader::feed_identifier() const { return feed_identifier_; }
void PacketHeader::set_feed_identifier(FeedIdentifier value) { feed_identifier_ = value; }

std::uint64_t PacketHeader::sequence() const { return sequence_; }
void PacketHeader::set_sequence(std::uint64_t value) { sequence_ = value; }

std::uint16_t PacketHeader::count() const { return count_; }
void PacketHeader::set_count(std::uint16_t value) { count_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    market_day_identifier_ = wire::read_text(data + offset, 9, '\0');
    offset += 9;

    feed_identifier_ = static_cast<FeedIdentifier>(wire::read_char(data + offset));
    offset += 1;

    sequence_ = wire::read_u64_le(data + offset);
    offset += 8;

    count_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    wire::write_text(data + offset, 9, '\0', market_day_identifier_);
    offset += 9;

    wire::write_char(data + offset, static_cast<char>(feed_identifier_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(sequence_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(count_));
    offset += 2;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "market_day_identifier=";
    print::text(out, market_day_identifier_);
    out << ", feed_identifier=";
    out << feed_identifier_;
    out << ", sequence=";
    out << sequence_;
    out << ", count=";
    out << count_;
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return market_day_identifier_ == other.market_day_identifier_
        && feed_identifier_ == other.feed_identifier_
        && sequence_ == other.sequence_
        && count_ == other.count_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
