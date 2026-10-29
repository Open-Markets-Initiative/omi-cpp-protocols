#include "ServerPayloadQuoteRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

ServerPayloadQuoteRequest::ServerPayloadQuoteRequest(std::chrono::nanoseconds transact_time, const std::string& quote_req_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& padding_3, const RelatedSymGroups& related_sym_groups)
  : transact_time_(transact_time), quote_req_id_(quote_req_id), match_event_indicator_(match_event_indicator), padding_3_(padding_3), related_sym_groups_(related_sym_groups) {}

std::chrono::nanoseconds ServerPayloadQuoteRequest::transact_time() const { return transact_time_; }
void ServerPayloadQuoteRequest::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const std::string& ServerPayloadQuoteRequest::quote_req_id() const { return quote_req_id_; }
std::string& ServerPayloadQuoteRequest::quote_req_id() { return quote_req_id_; }
void ServerPayloadQuoteRequest::set_quote_req_id(const std::string& value) { quote_req_id_ = value; }

const MatchEventIndicator& ServerPayloadQuoteRequest::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadQuoteRequest::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadQuoteRequest::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 3>& ServerPayloadQuoteRequest::padding_3() const { return padding_3_; }
std::array<std::byte, 3>& ServerPayloadQuoteRequest::padding_3() { return padding_3_; }
void ServerPayloadQuoteRequest::set_padding_3(const std::array<std::byte, 3>& value) { padding_3_ = value; }

const RelatedSymGroups& ServerPayloadQuoteRequest::related_sym_groups() const { return related_sym_groups_; }
RelatedSymGroups& ServerPayloadQuoteRequest::related_sym_groups() { return related_sym_groups_; }
void ServerPayloadQuoteRequest::set_related_sym_groups(const RelatedSymGroups& value) { related_sym_groups_ = value; }

ServerTcpMessageCode ServerPayloadQuoteRequest::type() const { return message_type; }

std::string_view ServerPayloadQuoteRequest::name() const { return "Quote Request"; }

std::size_t ServerPayloadQuoteRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadQuoteRequest", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ServerPayloadQuoteRequest", offset + 23, length);
    quote_req_id_ = wire::read_text(data + offset, 23, '\0');
    offset += 23;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadQuoteRequest", offset + 3, length);
    wire::read_bytes(data + offset, padding_3_.data(), 3);
    offset += 3;

    offset += related_sym_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadQuoteRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadQuoteRequest", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_text(data + offset, 23, '\0', quote_req_id_);
    offset += 23;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_3_.data(), 3);
    offset += 3;

    offset += related_sym_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadQuoteRequest::encoded_size() const {
    return 8 + 23 + match_event_indicator_.encoded_size() + 3 + related_sym_groups_.encoded_size();
}

void ServerPayloadQuoteRequest::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadQuoteRequest::clone() const {
    return std::make_unique<ServerPayloadQuoteRequest>(*this);
}

void ServerPayloadQuoteRequest::print(std::ostream& out) const {
    out << "ServerPayloadQuoteRequest{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", quote_req_id=";
    print::text(out, quote_req_id_);
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", padding_3=";
    print::hex(out, padding_3_.data(), padding_3_.size());
    out << ", related_sym_groups=";
    related_sym_groups_.print(out);
    out << '}';
}

bool ServerPayloadQuoteRequest::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadQuoteRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadQuoteRequest::operator==(const ServerPayloadQuoteRequest& other) const {
    return transact_time_ == other.transact_time_
        && quote_req_id_ == other.quote_req_id_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_3_ == other.padding_3_
        && related_sym_groups_ == other.related_sym_groups_;
}

bool ServerPayloadQuoteRequest::operator!=(const ServerPayloadQuoteRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_5
