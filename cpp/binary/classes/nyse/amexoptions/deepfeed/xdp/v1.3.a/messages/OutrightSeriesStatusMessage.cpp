#include "OutrightSeriesStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

OutrightSeriesStatusMessage::OutrightSeriesStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t symbol_seq_num, SecurityStatus security_status, char halt_condition, const std::array<std::byte, 2>& reserved_2)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), symbol_seq_num_(symbol_seq_num), security_status_(security_status), halt_condition_(halt_condition), reserved_2_(reserved_2) {}

std::uint32_t OutrightSeriesStatusMessage::source_time() const { return source_time_; }
void OutrightSeriesStatusMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OutrightSeriesStatusMessage::source_time_ns() const { return source_time_ns_; }
void OutrightSeriesStatusMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OutrightSeriesStatusMessage::series_index() const { return series_index_; }
void OutrightSeriesStatusMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OutrightSeriesStatusMessage::symbol_seq_num() const { return symbol_seq_num_; }
void OutrightSeriesStatusMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

SecurityStatus OutrightSeriesStatusMessage::security_status() const { return security_status_; }
void OutrightSeriesStatusMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

char OutrightSeriesStatusMessage::halt_condition() const { return halt_condition_; }
void OutrightSeriesStatusMessage::set_halt_condition(char value) { halt_condition_ = value; }

const std::array<std::byte, 2>& OutrightSeriesStatusMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& OutrightSeriesStatusMessage::reserved_2() { return reserved_2_; }
void OutrightSeriesStatusMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode OutrightSeriesStatusMessage::type() const { return message_type; }

std::string_view OutrightSeriesStatusMessage::name() const { return "Outright Series Status Message"; }

std::size_t OutrightSeriesStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OutrightSeriesStatusMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
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

std::size_t OutrightSeriesStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OutrightSeriesStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
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

std::size_t OutrightSeriesStatusMessage::encoded_size() const {
    return wire_size;
}

void OutrightSeriesStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OutrightSeriesStatusMessage::clone() const {
    return std::make_unique<OutrightSeriesStatusMessage>(*this);
}

void OutrightSeriesStatusMessage::print(std::ostream& out) const {
    out << "OutrightSeriesStatusMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
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

bool OutrightSeriesStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OutrightSeriesStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OutrightSeriesStatusMessage::operator==(const OutrightSeriesStatusMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && security_status_ == other.security_status_
        && halt_condition_ == other.halt_condition_
        && reserved_2_ == other.reserved_2_;
}

bool OutrightSeriesStatusMessage::operator!=(const OutrightSeriesStatusMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
