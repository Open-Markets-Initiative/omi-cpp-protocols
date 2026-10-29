#include "ComplexStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

ComplexStatusMessage::ComplexStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, SecurityStatus security_status, char halt_condition, const std::array<std::byte, 2>& reserved_2)
  : source_time_(source_time), source_time_ns_(source_time_ns), complex_index_(complex_index), symbol_seq_num_(symbol_seq_num), security_status_(security_status), halt_condition_(halt_condition), reserved_2_(reserved_2) {}

std::uint32_t ComplexStatusMessage::source_time() const { return source_time_; }
void ComplexStatusMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t ComplexStatusMessage::source_time_ns() const { return source_time_ns_; }
void ComplexStatusMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t ComplexStatusMessage::complex_index() const { return complex_index_; }
void ComplexStatusMessage::set_complex_index(std::uint32_t value) { complex_index_ = value; }

std::uint32_t ComplexStatusMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ComplexStatusMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

SecurityStatus ComplexStatusMessage::security_status() const { return security_status_; }
void ComplexStatusMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

char ComplexStatusMessage::halt_condition() const { return halt_condition_; }
void ComplexStatusMessage::set_halt_condition(char value) { halt_condition_ = value; }

const std::array<std::byte, 2>& ComplexStatusMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& ComplexStatusMessage::reserved_2() { return reserved_2_; }
void ComplexStatusMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode ComplexStatusMessage::type() const { return message_type; }

std::string_view ComplexStatusMessage::name() const { return "Complex Status Message"; }

std::size_t ComplexStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ComplexStatusMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    complex_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    security_status_ = static_cast<SecurityStatus>(wire::read_char(data + offset));
    offset += 1;

    halt_condition_ = wire::read_char(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t ComplexStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(complex_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(security_status_));
    offset += 1;

    wire::write_char(data + offset, halt_condition_);
    offset += 1;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t ComplexStatusMessage::encoded_size() const {
    return wire_size;
}

void ComplexStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexStatusMessage::clone() const {
    return std::make_unique<ComplexStatusMessage>(*this);
}

void ComplexStatusMessage::print(std::ostream& out) const {
    out << "ComplexStatusMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", complex_index=";
    out << complex_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", security_status=";
    out << security_status_;
    out << ", halt_condition=";
    print::character(out, halt_condition_);
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << '}';
}

bool ComplexStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexStatusMessage::operator==(const ComplexStatusMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && complex_index_ == other.complex_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && security_status_ == other.security_status_
        && halt_condition_ == other.halt_condition_
        && reserved_2_ == other.reserved_2_;
}

bool ComplexStatusMessage::operator!=(const ComplexStatusMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
