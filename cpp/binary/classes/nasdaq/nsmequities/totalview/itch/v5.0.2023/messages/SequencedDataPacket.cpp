#include "SequencedDataPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

SequencedDataPacket::SequencedDataPacket(const SequencedDataPacket& other)
  : sequenced_message_type_(other.sequenced_message_type_), sequenced_message_(other.sequenced_message_ ? other.sequenced_message_->clone() : nullptr) {}

SequencedDataPacket& SequencedDataPacket::operator=(const SequencedDataPacket& other) {
    if (this != &other) {
        sequenced_message_type_ = other.sequenced_message_type_;
        sequenced_message_ = other.sequenced_message_ ? other.sequenced_message_->clone() : nullptr;
    }
    return *this;
}

char SequencedDataPacket::sequenced_message_type() const { return sequenced_message_type_; }
void SequencedDataPacket::set_sequenced_message_type(char value) { sequenced_message_type_ = value; }

const SequencedMessage* SequencedDataPacket::sequenced_message() const { return sequenced_message_.get(); }
SequencedMessage* SequencedDataPacket::sequenced_message() { return sequenced_message_.get(); }
void SequencedDataPacket::set_sequenced_message(std::unique_ptr<SequencedMessage> value) { sequenced_message_ = std::move(value); }

ServerMessageCode SequencedDataPacket::type() const { return message_type; }

std::string_view SequencedDataPacket::name() const { return "Sequenced Data Packet"; }

std::size_t SequencedDataPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SequencedDataPacket", offset + 1, length);
    sequenced_message_type_ = wire::read_char(data + offset);
    offset += 1;

    {
        auto selected = SequencedMessageFactory::create(sequenced_message_type_);
        offset += selected->decode(data + offset, length - offset);
        sequenced_message_ = std::move(selected);
    }

    return offset;
}

std::size_t SequencedDataPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!sequenced_message_) { throw EncodeError("SequencedDataPacket", "no sequenced_message"); }
    wire::require_capacity("SequencedDataPacket", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto sequenced_message_type = sequenced_message_type_;
    sequenced_message_type = sequenced_message_->type();

    wire::write_char(data + offset, sequenced_message_type);
    offset += 1;

    offset += sequenced_message_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SequencedDataPacket::encoded_size() const {
    return 1 + (sequenced_message_ ? sequenced_message_->encoded_size() : 0);
}

void SequencedDataPacket::accept(ServerMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerMessage> SequencedDataPacket::clone() const {
    return std::make_unique<SequencedDataPacket>(*this);
}

void SequencedDataPacket::print(std::ostream& out) const {
    out << "SequencedDataPacket{";
    out << "sequenced_message_type=";
    print::character(out, sequenced_message_type_);
    out << ", sequenced_message=";
    if (sequenced_message_) { sequenced_message_->print(out); } else { out << "null"; }
    out << '}';
}

bool SequencedDataPacket::equals(const ServerMessage& other) const {
    const auto* that = dynamic_cast<const SequencedDataPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool SequencedDataPacket::operator==(const SequencedDataPacket& other) const {
    return sequenced_message_type_ == other.sequenced_message_type_
        && ((sequenced_message_ == nullptr) == (other.sequenced_message_ == nullptr) && (!sequenced_message_ || sequenced_message_->equals(*other.sequenced_message_)));
}

bool SequencedDataPacket::operator!=(const SequencedDataPacket& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
