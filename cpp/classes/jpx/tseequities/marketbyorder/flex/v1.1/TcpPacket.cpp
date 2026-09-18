#include "TcpPacket.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

TcpPacket::TcpPacket(std::unique_ptr<TcpMessage> message) : message_(std::move(message)) {}

TcpPacket::TcpPacket(const TcpPacket& other)
  : tcp_packet_header_(other.tcp_packet_header_), message_(other.message_ ? other.message_->clone() : nullptr) {}

TcpPacket& TcpPacket::operator=(const TcpPacket& other) {
    if (this != &other) {
        tcp_packet_header_ = other.tcp_packet_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
    }
    return *this;
}

const TcpPacketHeader& TcpPacket::tcp_packet_header() const { return tcp_packet_header_; }
TcpPacketHeader& TcpPacket::tcp_packet_header() { return tcp_packet_header_; }
void TcpPacket::set_tcp_packet_header(const TcpPacketHeader& value) { tcp_packet_header_ = value; }

const TcpMessage* TcpPacket::message() const { return message_.get(); }
TcpMessage* TcpPacket::message() { return message_.get(); }
void TcpPacket::set_message(std::unique_ptr<TcpMessage> message) { message_ = std::move(message); }
std::unique_ptr<TcpMessage> TcpPacket::release() { return std::move(message_); }

std::size_t TcpPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += tcp_packet_header_.decode(data + offset, length - offset);

    const std::size_t packet_size = static_cast<std::size_t>(tcp_packet_header_.packet_length());
    wire::require("TcpPacket", packet_size, length);
    const std::size_t body = packet_size - offset;

    message_ = TcpMessageFactory::create(tcp_packet_header_.packet_type());
    offset += message_->decode(data + offset, body);

    return offset;
}

std::size_t TcpPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (message_ == nullptr) { throw EncodeError("TcpPacket", "the packet holds no message"); }
    wire::require_capacity("TcpPacket", encoded_size(), capacity);

    auto tcp_packet_header = tcp_packet_header_;
    tcp_packet_header.set_packet_length(static_cast<std::uint16_t>(encoded_size()));
    tcp_packet_header.set_packet_type(message_->type());

    offset += tcp_packet_header.encode(data + offset, capacity - offset);

    offset += message_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TcpPacket::encoded_size() const {
    std::size_t total = tcp_packet_header_.encoded_size();
    total += message_ ? message_->encoded_size() : 0;
    return total;
}

void TcpPacket::accept(TcpMessageVisitor& visitor) const {
    if (message_) { message_->accept(visitor); }
}

void TcpPacket::print(std::ostream& out) const {
    out << "TcpPacket{";
    out << "tcp_packet_header=";
    tcp_packet_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    out << '}';
}

bool TcpPacket::operator==(const TcpPacket& other) const {
    if (!(tcp_packet_header_ == other.tcp_packet_header_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool TcpPacket::operator!=(const TcpPacket& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const TcpPacket& packet) { packet.print(out); return out; }

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
