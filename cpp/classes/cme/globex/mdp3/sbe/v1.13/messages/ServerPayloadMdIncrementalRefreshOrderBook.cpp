#include "ServerPayloadMdIncrementalRefreshOrderBook.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ServerPayloadMdIncrementalRefreshOrderBook::ServerPayloadMdIncrementalRefreshOrderBook(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const IncrementalRefreshOrderBookGroups& incremental_refresh_order_book_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), padding_2_(padding_2), incremental_refresh_order_book_groups_(incremental_refresh_order_book_groups) {}

std::chrono::nanoseconds ServerPayloadMdIncrementalRefreshOrderBook::transact_time() const { return transact_time_; }
void ServerPayloadMdIncrementalRefreshOrderBook::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& ServerPayloadMdIncrementalRefreshOrderBook::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadMdIncrementalRefreshOrderBook::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadMdIncrementalRefreshOrderBook::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 2>& ServerPayloadMdIncrementalRefreshOrderBook::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& ServerPayloadMdIncrementalRefreshOrderBook::padding_2() { return padding_2_; }
void ServerPayloadMdIncrementalRefreshOrderBook::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

const IncrementalRefreshOrderBookGroups& ServerPayloadMdIncrementalRefreshOrderBook::incremental_refresh_order_book_groups() const { return incremental_refresh_order_book_groups_; }
IncrementalRefreshOrderBookGroups& ServerPayloadMdIncrementalRefreshOrderBook::incremental_refresh_order_book_groups() { return incremental_refresh_order_book_groups_; }
void ServerPayloadMdIncrementalRefreshOrderBook::set_incremental_refresh_order_book_groups(const IncrementalRefreshOrderBookGroups& value) { incremental_refresh_order_book_groups_ = value; }

ServerTcpMessageCode ServerPayloadMdIncrementalRefreshOrderBook::type() const { return message_type; }

std::string_view ServerPayloadMdIncrementalRefreshOrderBook::name() const { return "Md Incremental Refresh Order Book"; }

std::size_t ServerPayloadMdIncrementalRefreshOrderBook::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadMdIncrementalRefreshOrderBook", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdIncrementalRefreshOrderBook", offset + 2, length);
    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_order_book_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadMdIncrementalRefreshOrderBook::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadMdIncrementalRefreshOrderBook", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_order_book_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadMdIncrementalRefreshOrderBook::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 2 + incremental_refresh_order_book_groups_.encoded_size();
}

void ServerPayloadMdIncrementalRefreshOrderBook::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadMdIncrementalRefreshOrderBook::clone() const {
    return std::make_unique<ServerPayloadMdIncrementalRefreshOrderBook>(*this);
}

void ServerPayloadMdIncrementalRefreshOrderBook::print(std::ostream& out) const {
    out << "ServerPayloadMdIncrementalRefreshOrderBook{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << ", incremental_refresh_order_book_groups=";
    incremental_refresh_order_book_groups_.print(out);
    out << '}';
}

bool ServerPayloadMdIncrementalRefreshOrderBook::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadMdIncrementalRefreshOrderBook*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadMdIncrementalRefreshOrderBook::operator==(const ServerPayloadMdIncrementalRefreshOrderBook& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_2_ == other.padding_2_
        && incremental_refresh_order_book_groups_ == other.incremental_refresh_order_book_groups_;
}

bool ServerPayloadMdIncrementalRefreshOrderBook::operator!=(const ServerPayloadMdIncrementalRefreshOrderBook& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
