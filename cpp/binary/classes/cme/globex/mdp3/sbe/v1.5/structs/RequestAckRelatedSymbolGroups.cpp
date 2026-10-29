#include "RequestAckRelatedSymbolGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

RequestAckRelatedSymbolGroups::RequestAckRelatedSymbolGroups(const GroupSize& group_size, const std::vector<RequestAckRelatedSymbolGroup>& request_ack_related_symbol_group)
  : group_size_(group_size), request_ack_related_symbol_group_(request_ack_related_symbol_group) {}

const GroupSize& RequestAckRelatedSymbolGroups::group_size() const { return group_size_; }
GroupSize& RequestAckRelatedSymbolGroups::group_size() { return group_size_; }
void RequestAckRelatedSymbolGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<RequestAckRelatedSymbolGroup>& RequestAckRelatedSymbolGroups::request_ack_related_symbol_group() const { return request_ack_related_symbol_group_; }
std::vector<RequestAckRelatedSymbolGroup>& RequestAckRelatedSymbolGroups::request_ack_related_symbol_group() { return request_ack_related_symbol_group_; }
void RequestAckRelatedSymbolGroups::set_request_ack_related_symbol_group(const std::vector<RequestAckRelatedSymbolGroup>& value) { request_ack_related_symbol_group_ = value; }

std::size_t RequestAckRelatedSymbolGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        request_ack_related_symbol_group_.clear();
        request_ack_related_symbol_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            RequestAckRelatedSymbolGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("RequestAckRelatedSymbolGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            request_ack_related_symbol_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t RequestAckRelatedSymbolGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RequestAckRelatedSymbolGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(request_ack_related_symbol_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(RequestAckRelatedSymbolGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : request_ack_related_symbol_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t RequestAckRelatedSymbolGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(request_ack_related_symbol_group_);
}

void RequestAckRelatedSymbolGroups::print(std::ostream& out) const {
    out << "RequestAckRelatedSymbolGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", request_ack_related_symbol_group=";
    print::sequence(out, request_ack_related_symbol_group_);
    out << '}';
}

bool RequestAckRelatedSymbolGroups::operator==(const RequestAckRelatedSymbolGroups& other) const {
    return group_size_ == other.group_size_
        && request_ack_related_symbol_group_ == other.request_ack_related_symbol_group_;
}

bool RequestAckRelatedSymbolGroups::operator!=(const RequestAckRelatedSymbolGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RequestAckRelatedSymbolGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
