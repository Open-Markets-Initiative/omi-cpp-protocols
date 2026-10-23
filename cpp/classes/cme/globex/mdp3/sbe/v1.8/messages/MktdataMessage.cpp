#include "MktdataMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"
#include "../UdpPacket.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

MktdataMessage::MktdataMessage(const MktdataMessage& other)
  : mktdata_payload_(other.mktdata_payload_ ? other.mktdata_payload_->clone() : nullptr), template_id_(other.template_id_) {}

MktdataMessage& MktdataMessage::operator=(const MktdataMessage& other) {
    if (this != &other) {
        mktdata_payload_ = other.mktdata_payload_ ? other.mktdata_payload_->clone() : nullptr;
        template_id_ = other.template_id_;
    }
    return *this;
}

const MktdataPayload* MktdataMessage::mktdata_payload() const { return mktdata_payload_.get(); }
MktdataPayload* MktdataMessage::mktdata_payload() { return mktdata_payload_.get(); }
void MktdataMessage::set_mktdata_payload(std::unique_ptr<MktdataPayload> value) { mktdata_payload_ = std::move(value); }

MessageCode MktdataMessage::type() const { return message_type; }

std::string_view MktdataMessage::name() const { return "Mktdata Message"; }

void MktdataMessage::bind(const Frame& frame) {
    template_id_ = frame.message_header().template_id();
}

std::optional<TemplateId> MktdataMessage::bound_template_id() const {
    if (mktdata_payload_) { return mktdata_payload_->type(); }
    return std::nullopt;
}

std::size_t MktdataMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    {
        auto selected = MktdataPayloadFactory::create(template_id_);
        offset += selected->decode(data + offset, length - offset);
        mktdata_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t MktdataMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!mktdata_payload_) { throw EncodeError("MktdataMessage", "no mktdata_payload"); }
    wire::require_capacity("MktdataMessage", encoded_size(), capacity);

    offset += mktdata_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MktdataMessage::encoded_size() const {
    return (mktdata_payload_ ? mktdata_payload_->encoded_size() : 0);
}

void MktdataMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MktdataMessage::clone() const {
    return std::make_unique<MktdataMessage>(*this);
}

void MktdataMessage::print(std::ostream& out) const {
    out << "MktdataMessage{";
    out << "mktdata_payload=";
    if (mktdata_payload_) { mktdata_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool MktdataMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MktdataMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MktdataMessage::operator==(const MktdataMessage& other) const {
    return ((mktdata_payload_ == nullptr) == (other.mktdata_payload_ == nullptr) && (!mktdata_payload_ || mktdata_payload_->equals(*other.mktdata_payload_)));
}

bool MktdataMessage::operator!=(const MktdataMessage& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
