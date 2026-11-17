// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: groups/RequestedMatchingEngine.cpp
#include "RequestedMatchingEngine.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

RequestedMatchingEngine::RequestedMatchingEngine(std::uint8_t requested_trading_session_id, std::uint64_t requested_sequence_number)
  : requested_trading_session_id_(requested_trading_session_id), requested_sequence_number_(requested_sequence_number) {}

std::uint8_t RequestedMatchingEngine::requested_trading_session_id() const { return requested_trading_session_id_; }
void RequestedMatchingEngine::set_requested_trading_session_id(std::uint8_t value) { requested_trading_session_id_ = value; }

std::uint64_t RequestedMatchingEngine::requested_sequence_number() const { return requested_sequence_number_; }
void RequestedMatchingEngine::set_requested_sequence_number(std::uint64_t value) { requested_sequence_number_ = value; }

std::size_t RequestedMatchingEngine::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RequestedMatchingEngine", wire_size, length);

    requested_trading_session_id_ = wire::read_u8(data + offset);
    offset += 1;

    requested_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t RequestedMatchingEngine::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RequestedMatchingEngine", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(requested_trading_session_id_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(requested_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t RequestedMatchingEngine::encoded_size() const {
    return wire_size;
}

void RequestedMatchingEngine::print(std::ostream& out) const {
    out << "RequestedMatchingEngine{";
    out << "requested_trading_session_id=";
    out << static_cast<int>(requested_trading_session_id_);
    out << ", requested_sequence_number=";
    out << requested_sequence_number_;
    out << '}';
}

bool RequestedMatchingEngine::operator==(const RequestedMatchingEngine& other) const {
    return requested_trading_session_id_ == other.requested_trading_session_id_
        && requested_sequence_number_ == other.requested_sequence_number_;
}

bool RequestedMatchingEngine::operator!=(const RequestedMatchingEngine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RequestedMatchingEngine& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
