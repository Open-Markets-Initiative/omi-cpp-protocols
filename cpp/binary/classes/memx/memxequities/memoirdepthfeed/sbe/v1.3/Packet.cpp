#include "Packet.hpp"

#include "Factory.hpp"
#include "Visitor.hpp"
#include "common/Print.hpp"
#include "common/Wire.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

Packet::Packet(std::unique_ptr<Message> message) : message_(std::move(message)) {}

Packet::Packet(const Packet& other)
  : common_header_(other.common_header_), message_(other.message_ ? other.message_->clone() : nullptr) {}

Packet& Packet::operator=(const Packet& other) {
    if (this != &other) {
        common_header_ = other.common_header_;
        message_ = other.message_ ? other.message_->clone() : nullptr;
    }
    return *this;
}

const CommonHeader& Packet::common_header() const { return common_header_; }
CommonHeader& Packet::common_header() { return common_header_; }
void Packet::set_common_header(const CommonHeader& value) { common_header_ = value; }

const Message* Packet::message() const { return message_.get(); }
Message* Packet::message() { return message_.get(); }
void Packet::set_message(std::unique_ptr<Message> message) { message_ = std::move(message); }
std::unique_ptr<Message> Packet::release() { return std::move(message_); }

std::size_t Packet::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += common_header_.decode(data + offset, length - offset);

    const std::size_t body = length - offset;

    message_ = Factory::create(common_header_.message_type());
    offset += message_->decode(data + offset, body);

    return offset;
}

std::size_t Packet::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (message_ == nullptr) { throw EncodeError("Packet", "the packet holds no message"); }
    wire::require_capacity("Packet", encoded_size(), capacity);

    auto common_header = common_header_;
    common_header.set_message_type(message_->type());

    offset += common_header.encode(data + offset, capacity - offset);

    offset += message_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t Packet::encoded_size() const {
    std::size_t total = common_header_.encoded_size();
    total += message_ ? message_->encoded_size() : 0;
    return total;
}

void Packet::accept(Visitor& visitor) const {
    if (message_) { message_->accept(visitor); }
}

void Packet::print(std::ostream& out) const {
    out << "Packet{";
    out << "common_header=";
    common_header_.print(out);
    out << ", ";
    out << "message=";
    if (message_) { message_->print(out); } else { out << "null"; }
    out << '}';
}

bool Packet::operator==(const Packet& other) const {
    if (!(common_header_ == other.common_header_)) { return false; }
    if (!message_ || !other.message_) { return !message_ && !other.message_; }
    return message_->equals(*other.message_);
}

bool Packet::operator!=(const Packet& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& out, const Packet& packet) { packet.print(out); return out; }

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
