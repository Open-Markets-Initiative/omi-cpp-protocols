#include "MdpsessionmgmtMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"
#include "../UdpPacket.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

MdpsessionmgmtMessage::MdpsessionmgmtMessage(const MdpsessionmgmtMessage& other)
  : mdpsessionmgmt_payload_(other.mdpsessionmgmt_payload_ ? other.mdpsessionmgmt_payload_->clone() : nullptr), template_id_(other.template_id_) {}

MdpsessionmgmtMessage& MdpsessionmgmtMessage::operator=(const MdpsessionmgmtMessage& other) {
    if (this != &other) {
        mdpsessionmgmt_payload_ = other.mdpsessionmgmt_payload_ ? other.mdpsessionmgmt_payload_->clone() : nullptr;
        template_id_ = other.template_id_;
    }
    return *this;
}

const MdpsessionmgmtPayload* MdpsessionmgmtMessage::mdpsessionmgmt_payload() const { return mdpsessionmgmt_payload_.get(); }
MdpsessionmgmtPayload* MdpsessionmgmtMessage::mdpsessionmgmt_payload() { return mdpsessionmgmt_payload_.get(); }
void MdpsessionmgmtMessage::set_mdpsessionmgmt_payload(std::unique_ptr<MdpsessionmgmtPayload> value) { mdpsessionmgmt_payload_ = std::move(value); }

MessageCode MdpsessionmgmtMessage::type() const { return message_type; }

std::string_view MdpsessionmgmtMessage::name() const { return "Mdpsessionmgmt Message"; }

void MdpsessionmgmtMessage::bind(const Frame& frame) {
    template_id_ = frame.message_header().template_id();
}

std::optional<TemplateId> MdpsessionmgmtMessage::bound_template_id() const {
    if (mdpsessionmgmt_payload_) { return mdpsessionmgmt_payload_->type(); }
    return std::nullopt;
}

std::size_t MdpsessionmgmtMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    {
        auto selected = MdpsessionmgmtPayloadFactory::create(template_id_);
        offset += selected->decode(data + offset, length - offset);
        mdpsessionmgmt_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t MdpsessionmgmtMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!mdpsessionmgmt_payload_) { throw EncodeError("MdpsessionmgmtMessage", "no mdpsessionmgmt_payload"); }
    wire::require_capacity("MdpsessionmgmtMessage", encoded_size(), capacity);

    offset += mdpsessionmgmt_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MdpsessionmgmtMessage::encoded_size() const {
    return (mdpsessionmgmt_payload_ ? mdpsessionmgmt_payload_->encoded_size() : 0);
}

void MdpsessionmgmtMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MdpsessionmgmtMessage::clone() const {
    return std::make_unique<MdpsessionmgmtMessage>(*this);
}

void MdpsessionmgmtMessage::print(std::ostream& out) const {
    out << "MdpsessionmgmtMessage{";
    out << "mdpsessionmgmt_payload=";
    if (mdpsessionmgmt_payload_) { mdpsessionmgmt_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool MdpsessionmgmtMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MdpsessionmgmtMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MdpsessionmgmtMessage::operator==(const MdpsessionmgmtMessage& other) const {
    return ((mdpsessionmgmt_payload_ == nullptr) == (other.mdpsessionmgmt_payload_ == nullptr) && (!mdpsessionmgmt_payload_ || mdpsessionmgmt_payload_->equals(*other.mdpsessionmgmt_payload_)));
}

bool MdpsessionmgmtMessage::operator!=(const MdpsessionmgmtMessage& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
