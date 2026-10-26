#include "QuoteRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

QuoteRequest::QuoteRequest(std::chrono::nanoseconds transact_time, const std::string& quote_req_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& padding_3, const RelatedSymGroups& related_sym_groups)
  : transact_time_(transact_time), quote_req_id_(quote_req_id), match_event_indicator_(match_event_indicator), padding_3_(padding_3), related_sym_groups_(related_sym_groups) {}

std::chrono::nanoseconds QuoteRequest::transact_time() const { return transact_time_; }
void QuoteRequest::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const std::string& QuoteRequest::quote_req_id() const { return quote_req_id_; }
std::string& QuoteRequest::quote_req_id() { return quote_req_id_; }
void QuoteRequest::set_quote_req_id(const std::string& value) { quote_req_id_ = value; }

const MatchEventIndicator& QuoteRequest::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& QuoteRequest::match_event_indicator() { return match_event_indicator_; }
void QuoteRequest::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 3>& QuoteRequest::padding_3() const { return padding_3_; }
std::array<std::byte, 3>& QuoteRequest::padding_3() { return padding_3_; }
void QuoteRequest::set_padding_3(const std::array<std::byte, 3>& value) { padding_3_ = value; }

const RelatedSymGroups& QuoteRequest::related_sym_groups() const { return related_sym_groups_; }
RelatedSymGroups& QuoteRequest::related_sym_groups() { return related_sym_groups_; }
void QuoteRequest::set_related_sym_groups(const RelatedSymGroups& value) { related_sym_groups_ = value; }

MktdataPayloadCode QuoteRequest::type() const { return message_type; }

std::string_view QuoteRequest::name() const { return "Quote Request"; }

std::size_t QuoteRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("QuoteRequest", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("QuoteRequest", offset + 23, length);
    quote_req_id_ = wire::read_text(data + offset, 23, '\0');
    offset += 23;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("QuoteRequest", offset + 3, length);
    wire::read_bytes(data + offset, padding_3_.data(), 3);
    offset += 3;

    offset += related_sym_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t QuoteRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteRequest", encoded_size(), capacity);

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

std::size_t QuoteRequest::encoded_size() const {
    return 8 + 23 + match_event_indicator_.encoded_size() + 3 + related_sym_groups_.encoded_size();
}

void QuoteRequest::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> QuoteRequest::clone() const {
    return std::make_unique<QuoteRequest>(*this);
}

void QuoteRequest::print(std::ostream& out) const {
    out << "QuoteRequest{";
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

bool QuoteRequest::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const QuoteRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteRequest::operator==(const QuoteRequest& other) const {
    return transact_time_ == other.transact_time_
        && quote_req_id_ == other.quote_req_id_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_3_ == other.padding_3_
        && related_sym_groups_ == other.related_sym_groups_;
}

bool QuoteRequest::operator!=(const QuoteRequest& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
