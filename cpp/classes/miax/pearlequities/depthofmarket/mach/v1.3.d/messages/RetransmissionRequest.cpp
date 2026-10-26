#include "RetransmissionRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

RetransmissionRequest::RetransmissionRequest(std::uint64_t start_sequence_number, std::uint64_t end_sequence_number)
  : start_sequence_number_(start_sequence_number), end_sequence_number_(end_sequence_number) {}

std::uint64_t RetransmissionRequest::start_sequence_number() const { return start_sequence_number_; }
void RetransmissionRequest::set_start_sequence_number(std::uint64_t value) { start_sequence_number_ = value; }

std::uint64_t RetransmissionRequest::end_sequence_number() const { return end_sequence_number_; }
void RetransmissionRequest::set_end_sequence_number(std::uint64_t value) { end_sequence_number_ = value; }

TcpMessageCode RetransmissionRequest::type() const { return message_type; }

std::string_view RetransmissionRequest::name() const { return "Retransmission Request"; }

std::size_t RetransmissionRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetransmissionRequest", wire_size, length);

    start_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    end_sequence_number_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t RetransmissionRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetransmissionRequest", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(start_sequence_number_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(end_sequence_number_));
    offset += 8;

    return offset;
}

std::size_t RetransmissionRequest::encoded_size() const {
    return wire_size;
}

void RetransmissionRequest::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> RetransmissionRequest::clone() const {
    return std::make_unique<RetransmissionRequest>(*this);
}

void RetransmissionRequest::print(std::ostream& out) const {
    out << "RetransmissionRequest{";
    out << "start_sequence_number=";
    out << start_sequence_number_;
    out << ", end_sequence_number=";
    out << end_sequence_number_;
    out << '}';
}

bool RetransmissionRequest::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const RetransmissionRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool RetransmissionRequest::operator==(const RetransmissionRequest& other) const {
    return start_sequence_number_ == other.start_sequence_number_
        && end_sequence_number_ == other.end_sequence_number_;
}

bool RetransmissionRequest::operator!=(const RetransmissionRequest& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
