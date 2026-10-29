#include "UnderlyingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

UnderlyingStatusMessage::UnderlyingStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t underlying_index, std::uint32_t underlying_seq_num, SecurityStatus security_status, char halt_condition, const std::array<std::byte, 2>& reserved_2)
  : source_time_(source_time), source_time_ns_(source_time_ns), underlying_index_(underlying_index), underlying_seq_num_(underlying_seq_num), security_status_(security_status), halt_condition_(halt_condition), reserved_2_(reserved_2) {}

std::uint32_t UnderlyingStatusMessage::source_time() const { return source_time_; }
void UnderlyingStatusMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t UnderlyingStatusMessage::source_time_ns() const { return source_time_ns_; }
void UnderlyingStatusMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t UnderlyingStatusMessage::underlying_index() const { return underlying_index_; }
void UnderlyingStatusMessage::set_underlying_index(std::uint32_t value) { underlying_index_ = value; }

std::uint32_t UnderlyingStatusMessage::underlying_seq_num() const { return underlying_seq_num_; }
void UnderlyingStatusMessage::set_underlying_seq_num(std::uint32_t value) { underlying_seq_num_ = value; }

SecurityStatus UnderlyingStatusMessage::security_status() const { return security_status_; }
void UnderlyingStatusMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

char UnderlyingStatusMessage::halt_condition() const { return halt_condition_; }
void UnderlyingStatusMessage::set_halt_condition(char value) { halt_condition_ = value; }

const std::array<std::byte, 2>& UnderlyingStatusMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& UnderlyingStatusMessage::reserved_2() { return reserved_2_; }
void UnderlyingStatusMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode UnderlyingStatusMessage::type() const { return message_type; }

std::string_view UnderlyingStatusMessage::name() const { return "Underlying Status Message"; }

std::size_t UnderlyingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingStatusMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    underlying_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    underlying_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    security_status_ = static_cast<SecurityStatus>(wire::read_char(data + offset));
    offset += 1;

    halt_condition_ = wire::read_char(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t UnderlyingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(underlying_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(underlying_seq_num_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(security_status_));
    offset += 1;

    wire::write_char(data + offset, halt_condition_);
    offset += 1;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t UnderlyingStatusMessage::encoded_size() const {
    return wire_size;
}

void UnderlyingStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> UnderlyingStatusMessage::clone() const {
    return std::make_unique<UnderlyingStatusMessage>(*this);
}

void UnderlyingStatusMessage::print(std::ostream& out) const {
    out << "UnderlyingStatusMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", underlying_index=";
    out << underlying_index_;
    out << ", underlying_seq_num=";
    out << underlying_seq_num_;
    out << ", security_status=";
    out << security_status_;
    out << ", halt_condition=";
    print::character(out, halt_condition_);
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << '}';
}

bool UnderlyingStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const UnderlyingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnderlyingStatusMessage::operator==(const UnderlyingStatusMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && underlying_index_ == other.underlying_index_
        && underlying_seq_num_ == other.underlying_seq_num_
        && security_status_ == other.security_status_
        && halt_condition_ == other.halt_condition_
        && reserved_2_ == other.reserved_2_;
}

bool UnderlyingStatusMessage::operator!=(const UnderlyingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
