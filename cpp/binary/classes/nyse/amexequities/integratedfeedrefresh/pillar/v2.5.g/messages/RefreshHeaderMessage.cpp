#include "RefreshHeaderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

RefreshHeaderMessage::RefreshHeaderMessage(std::uint16_t current_refresh_pkt, std::uint16_t total_refresh_pkts, const std::optional<FullRefreshHeader>& full_refresh_header)
  : current_refresh_pkt_(current_refresh_pkt), total_refresh_pkts_(total_refresh_pkts), full_refresh_header_(full_refresh_header) {}

std::uint16_t RefreshHeaderMessage::current_refresh_pkt() const { return current_refresh_pkt_; }
void RefreshHeaderMessage::set_current_refresh_pkt(std::uint16_t value) { current_refresh_pkt_ = value; }

std::uint16_t RefreshHeaderMessage::total_refresh_pkts() const { return total_refresh_pkts_; }
void RefreshHeaderMessage::set_total_refresh_pkts(std::uint16_t value) { total_refresh_pkts_ = value; }

const std::optional<FullRefreshHeader>& RefreshHeaderMessage::full_refresh_header() const { return full_refresh_header_; }
std::optional<FullRefreshHeader>& RefreshHeaderMessage::full_refresh_header() { return full_refresh_header_; }
void RefreshHeaderMessage::set_full_refresh_header(const std::optional<FullRefreshHeader>& value) { full_refresh_header_ = value; }

MessageCode RefreshHeaderMessage::type() const { return message_type; }

std::string_view RefreshHeaderMessage::name() const { return "Refresh Header Message"; }

std::size_t RefreshHeaderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("RefreshHeaderMessage", offset + 2, length);
    current_refresh_pkt_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("RefreshHeaderMessage", offset + 2, length);
    total_refresh_pkts_ = wire::read_u16_le(data + offset);
    offset += 2;

    if (current_refresh_pkt_ == 1) {
        FullRefreshHeader value;
        offset += value.decode(data + offset, length - offset);
        full_refresh_header_ = std::move(value);
    } else {
        full_refresh_header_.reset();
    }

    return offset;
}

std::size_t RefreshHeaderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RefreshHeaderMessage", encoded_size(), capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(current_refresh_pkt_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(total_refresh_pkts_));
    offset += 2;

    if (full_refresh_header_) {
        offset += full_refresh_header_->encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t RefreshHeaderMessage::encoded_size() const {
    return 2 + 2 + (full_refresh_header_ ? full_refresh_header_->encoded_size() : 0);
}

void RefreshHeaderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RefreshHeaderMessage::clone() const {
    return std::make_unique<RefreshHeaderMessage>(*this);
}

void RefreshHeaderMessage::print(std::ostream& out) const {
    out << "RefreshHeaderMessage{";
    out << "current_refresh_pkt=";
    out << current_refresh_pkt_;
    out << ", total_refresh_pkts=";
    out << total_refresh_pkts_;
    out << ", full_refresh_header=";
    print::optional(out, full_refresh_header_);
    out << '}';
}

bool RefreshHeaderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RefreshHeaderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RefreshHeaderMessage::operator==(const RefreshHeaderMessage& other) const {
    return current_refresh_pkt_ == other.current_refresh_pkt_
        && total_refresh_pkts_ == other.total_refresh_pkts_
        && full_refresh_header_ == other.full_refresh_header_;
}

bool RefreshHeaderMessage::operator!=(const RefreshHeaderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g
