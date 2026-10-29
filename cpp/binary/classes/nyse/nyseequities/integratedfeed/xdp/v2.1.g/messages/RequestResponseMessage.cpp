#include "RequestResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

RequestResponseMessage::RequestResponseMessage(std::uint32_t request_seq_num, std::uint32_t begin_seq_num, std::uint32_t end_seq_num, const std::string& source_id, std::uint8_t product_id, std::uint8_t channel_id, Status status)
  : request_seq_num_(request_seq_num), begin_seq_num_(begin_seq_num), end_seq_num_(end_seq_num), source_id_(source_id), product_id_(product_id), channel_id_(channel_id), status_(status) {}

std::uint32_t RequestResponseMessage::request_seq_num() const { return request_seq_num_; }
void RequestResponseMessage::set_request_seq_num(std::uint32_t value) { request_seq_num_ = value; }

std::uint32_t RequestResponseMessage::begin_seq_num() const { return begin_seq_num_; }
void RequestResponseMessage::set_begin_seq_num(std::uint32_t value) { begin_seq_num_ = value; }

std::uint32_t RequestResponseMessage::end_seq_num() const { return end_seq_num_; }
void RequestResponseMessage::set_end_seq_num(std::uint32_t value) { end_seq_num_ = value; }

const std::string& RequestResponseMessage::source_id() const { return source_id_; }
std::string& RequestResponseMessage::source_id() { return source_id_; }
void RequestResponseMessage::set_source_id(const std::string& value) { source_id_ = value; }

std::uint8_t RequestResponseMessage::product_id() const { return product_id_; }
void RequestResponseMessage::set_product_id(std::uint8_t value) { product_id_ = value; }

std::uint8_t RequestResponseMessage::channel_id() const { return channel_id_; }
void RequestResponseMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

Status RequestResponseMessage::status() const { return status_; }
void RequestResponseMessage::set_status(Status value) { status_ = value; }

MessageCode RequestResponseMessage::type() const { return message_type; }

std::string_view RequestResponseMessage::name() const { return "Request Response Message"; }

std::size_t RequestResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RequestResponseMessage", wire_size, length);

    request_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    begin_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    end_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_id_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    product_id_ = wire::read_u8(data + offset);
    offset += 1;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    status_ = static_cast<Status>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RequestResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RequestResponseMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(request_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(begin_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(end_seq_num_));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', source_id_);
    offset += 10;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(status_));
    offset += 1;

    return offset;
}

std::size_t RequestResponseMessage::encoded_size() const {
    return wire_size;
}

void RequestResponseMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RequestResponseMessage::clone() const {
    return std::make_unique<RequestResponseMessage>(*this);
}

void RequestResponseMessage::print(std::ostream& out) const {
    out << "RequestResponseMessage{";
    out << "request_seq_num=";
    out << request_seq_num_;
    out << ", begin_seq_num=";
    out << begin_seq_num_;
    out << ", end_seq_num=";
    out << end_seq_num_;
    out << ", source_id=";
    print::text(out, source_id_);
    out << ", product_id=";
    out << static_cast<int>(product_id_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << ", status=";
    out << status_;
    out << '}';
}

bool RequestResponseMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RequestResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RequestResponseMessage::operator==(const RequestResponseMessage& other) const {
    return request_seq_num_ == other.request_seq_num_
        && begin_seq_num_ == other.begin_seq_num_
        && end_seq_num_ == other.end_seq_num_
        && source_id_ == other.source_id_
        && product_id_ == other.product_id_
        && channel_id_ == other.channel_id_
        && status_ == other.status_;
}

bool RequestResponseMessage::operator!=(const RequestResponseMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
