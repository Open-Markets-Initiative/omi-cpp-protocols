#include "ComplexCubeRfqMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

ComplexCubeRfqMessage::ComplexCubeRfqMessage(std::uint32_t source_time, std::uint32_t source_ns, std::uint32_t complex_index, std::uint32_t symbol_seq_num, Side side, const std::array<std::byte, 1>& reserved_1, std::uint16_t volume_2, std::int32_t price)
  : source_time_(source_time), source_ns_(source_ns), complex_index_(complex_index), symbol_seq_num_(symbol_seq_num), side_(side), reserved_1_(reserved_1), volume_2_(volume_2), price_(price) {}

std::uint32_t ComplexCubeRfqMessage::source_time() const { return source_time_; }
void ComplexCubeRfqMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t ComplexCubeRfqMessage::source_ns() const { return source_ns_; }
void ComplexCubeRfqMessage::set_source_ns(std::uint32_t value) { source_ns_ = value; }

std::uint32_t ComplexCubeRfqMessage::complex_index() const { return complex_index_; }
void ComplexCubeRfqMessage::set_complex_index(std::uint32_t value) { complex_index_ = value; }

std::uint32_t ComplexCubeRfqMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ComplexCubeRfqMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

Side ComplexCubeRfqMessage::side() const { return side_; }
void ComplexCubeRfqMessage::set_side(Side value) { side_ = value; }

const std::array<std::byte, 1>& ComplexCubeRfqMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& ComplexCubeRfqMessage::reserved_1() { return reserved_1_; }
void ComplexCubeRfqMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

std::uint16_t ComplexCubeRfqMessage::volume_2() const { return volume_2_; }
void ComplexCubeRfqMessage::set_volume_2(std::uint16_t value) { volume_2_ = value; }

std::int32_t ComplexCubeRfqMessage::price() const { return price_; }
void ComplexCubeRfqMessage::set_price(std::int32_t value) { price_ = value; }

MessageCode ComplexCubeRfqMessage::type() const { return message_type; }

std::string_view ComplexCubeRfqMessage::name() const { return "Complex Cube Rfq Message"; }

std::size_t ComplexCubeRfqMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ComplexCubeRfqMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    complex_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    volume_2_ = wire::read_u16_le(data + offset);
    offset += 2;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t ComplexCubeRfqMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexCubeRfqMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(complex_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(volume_2_));
    offset += 2;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    return offset;
}

std::size_t ComplexCubeRfqMessage::encoded_size() const {
    return wire_size;
}

void ComplexCubeRfqMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexCubeRfqMessage::clone() const {
    return std::make_unique<ComplexCubeRfqMessage>(*this);
}

void ComplexCubeRfqMessage::print(std::ostream& out) const {
    out << "ComplexCubeRfqMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_ns=";
    out << source_ns_;
    out << ", complex_index=";
    out << complex_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", side=";
    out << side_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", volume_2=";
    out << volume_2_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool ComplexCubeRfqMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexCubeRfqMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexCubeRfqMessage::operator==(const ComplexCubeRfqMessage& other) const {
    return source_time_ == other.source_time_
        && source_ns_ == other.source_ns_
        && complex_index_ == other.complex_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && side_ == other.side_
        && reserved_1_ == other.reserved_1_
        && volume_2_ == other.volume_2_
        && price_ == other.price_;
}

bool ComplexCubeRfqMessage::operator!=(const ComplexCubeRfqMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
