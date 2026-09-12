#include "SnapshotDataMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

SnapshotDataMessage::SnapshotDataMessage(const SnapshotDataMessage& other)
  : iex_tp_header_(other.iex_tp_header_), iex_tp_message_block_length_(other.iex_tp_message_block_length_), iex_tp_message_length_(other.iex_tp_message_length_), iex_tp_message_type_(other.iex_tp_message_type_), iex_tp_message_data_(other.iex_tp_message_data_ ? other.iex_tp_message_data_->clone() : nullptr) {}

SnapshotDataMessage& SnapshotDataMessage::operator=(const SnapshotDataMessage& other) {
    if (this != &other) {
        iex_tp_header_ = other.iex_tp_header_;
        iex_tp_message_block_length_ = other.iex_tp_message_block_length_;
        iex_tp_message_length_ = other.iex_tp_message_length_;
        iex_tp_message_type_ = other.iex_tp_message_type_;
        iex_tp_message_data_ = other.iex_tp_message_data_ ? other.iex_tp_message_data_->clone() : nullptr;
    }
    return *this;
}

char SnapshotDataMessage::iex_tp_header() const { return iex_tp_header_; }
void SnapshotDataMessage::set_iex_tp_header(char value) { iex_tp_header_ = value; }

std::uint16_t SnapshotDataMessage::iex_tp_message_block_length() const { return iex_tp_message_block_length_; }
void SnapshotDataMessage::set_iex_tp_message_block_length(std::uint16_t value) { iex_tp_message_block_length_ = value; }

std::uint16_t SnapshotDataMessage::iex_tp_message_length() const { return iex_tp_message_length_; }
void SnapshotDataMessage::set_iex_tp_message_length(std::uint16_t value) { iex_tp_message_length_ = value; }

IexTpMessageType SnapshotDataMessage::iex_tp_message_type() const { return iex_tp_message_type_; }
void SnapshotDataMessage::set_iex_tp_message_type(IexTpMessageType value) { iex_tp_message_type_ = value; }

const IexTpMessageData* SnapshotDataMessage::iex_tp_message_data() const { return iex_tp_message_data_.get(); }
IexTpMessageData* SnapshotDataMessage::iex_tp_message_data() { return iex_tp_message_data_.get(); }
void SnapshotDataMessage::set_iex_tp_message_data(std::unique_ptr<IexTpMessageData> value) { iex_tp_message_data_ = std::move(value); }

MessageCode SnapshotDataMessage::type() const { return message_type; }

std::string_view SnapshotDataMessage::name() const { return "Snapshot Data Message"; }

std::size_t SnapshotDataMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SnapshotDataMessage", offset + 1, length);
    iex_tp_header_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("SnapshotDataMessage", offset + 2, length);
    iex_tp_message_block_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("SnapshotDataMessage", offset + 2, length);
    iex_tp_message_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("SnapshotDataMessage", offset + 1, length);
    iex_tp_message_type_ = static_cast<IexTpMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = IexTpMessageDataFactory::create(iex_tp_message_type_);
        offset += selected->decode(data + offset, length - offset);
        iex_tp_message_data_ = std::move(selected);
    }

    return offset;
}

std::size_t SnapshotDataMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!iex_tp_message_data_) { throw EncodeError("SnapshotDataMessage", "no iex_tp_message_data"); }
    wire::require_capacity("SnapshotDataMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto iex_tp_message_type = iex_tp_message_type_;
    iex_tp_message_type = iex_tp_message_data_->type();

    wire::write_char(data + offset, iex_tp_header_);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(iex_tp_message_block_length_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(iex_tp_message_length_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(iex_tp_message_type));
    offset += 1;

    offset += iex_tp_message_data_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotDataMessage::encoded_size() const {
    return 1 + 2 + 2 + 1 + (iex_tp_message_data_ ? iex_tp_message_data_->encoded_size() : 0);
}

void SnapshotDataMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotDataMessage::clone() const {
    return std::make_unique<SnapshotDataMessage>(*this);
}

void SnapshotDataMessage::print(std::ostream& out) const {
    out << "SnapshotDataMessage{";
    out << "iex_tp_header=";
    print::character(out, iex_tp_header_);
    out << ", iex_tp_message_block_length=";
    out << iex_tp_message_block_length_;
    out << ", iex_tp_message_length=";
    out << iex_tp_message_length_;
    out << ", iex_tp_message_type=";
    out << iex_tp_message_type_;
    out << ", iex_tp_message_data=";
    if (iex_tp_message_data_) { iex_tp_message_data_->print(out); } else { out << "null"; }
    out << '}';
}

bool SnapshotDataMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotDataMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotDataMessage::operator==(const SnapshotDataMessage& other) const {
    return iex_tp_header_ == other.iex_tp_header_
        && iex_tp_message_block_length_ == other.iex_tp_message_block_length_
        && iex_tp_message_length_ == other.iex_tp_message_length_
        && iex_tp_message_type_ == other.iex_tp_message_type_
        && ((iex_tp_message_data_ == nullptr) == (other.iex_tp_message_data_ == nullptr) && (!iex_tp_message_data_ || iex_tp_message_data_->equals(*other.iex_tp_message_data_)));
}

bool SnapshotDataMessage::operator!=(const SnapshotDataMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deep::snap::v1_6
