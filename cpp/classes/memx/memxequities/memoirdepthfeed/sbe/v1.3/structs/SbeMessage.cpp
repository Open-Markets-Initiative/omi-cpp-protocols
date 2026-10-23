#include "SbeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

SbeMessage::SbeMessage(const SbeMessage& other)
  : sbe_header_(other.sbe_header_), payload_(other.payload_ ? other.payload_->clone() : nullptr) {}

SbeMessage& SbeMessage::operator=(const SbeMessage& other) {
    if (this != &other) {
        sbe_header_ = other.sbe_header_;
        payload_ = other.payload_ ? other.payload_->clone() : nullptr;
    }
    return *this;
}

const SbeHeader& SbeMessage::sbe_header() const { return sbe_header_; }
SbeHeader& SbeMessage::sbe_header() { return sbe_header_; }
void SbeMessage::set_sbe_header(const SbeHeader& value) { sbe_header_ = value; }

const Payload* SbeMessage::payload() const { return payload_.get(); }
Payload* SbeMessage::payload() { return payload_.get(); }
void SbeMessage::set_payload(std::unique_ptr<Payload> value) { payload_ = std::move(value); }

std::size_t SbeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += sbe_header_.decode(data + offset, length - offset);

    {
        auto selected = PayloadFactory::create(sbe_header_.template_id());
        offset += selected->decode(data + offset, length - offset);
        payload_ = std::move(selected);
    }

    return offset;
}

std::size_t SbeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!payload_) { throw EncodeError("SbeMessage", "no payload"); }
    wire::require_capacity("SbeMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto sbe_header = sbe_header_;
    sbe_header.set_template_id(payload_->type());

    offset += sbe_header.encode(data + offset, capacity - offset);

    offset += payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SbeMessage::encoded_size() const {
    return sbe_header_.encoded_size() + (payload_ ? payload_->encoded_size() : 0);
}

void SbeMessage::print(std::ostream& out) const {
    out << "SbeMessage{";
    out << "sbe_header=";
    sbe_header_.print(out);
    out << ", payload=";
    if (payload_) { payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool SbeMessage::operator==(const SbeMessage& other) const {
    return sbe_header_ == other.sbe_header_
        && ((payload_ == nullptr) == (other.payload_ == nullptr) && (!payload_ || payload_->equals(*other.payload_)));
}

bool SbeMessage::operator!=(const SbeMessage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SbeMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
