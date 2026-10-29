#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/MdpsessionmgmtPayload.hpp"
#include "../messages/Message.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class Visitor;
class MdpsessionmgmtPayloadVisitor;

// Message of sbe schema mdpsessionmgmt (schema id 2)
class MdpsessionmgmtMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = SchemaId::Mdpsessionmgmt;

    MdpsessionmgmtMessage() = default;
    MdpsessionmgmtMessage(const MdpsessionmgmtMessage& other);
    MdpsessionmgmtMessage& operator=(const MdpsessionmgmtMessage& other);
    MdpsessionmgmtMessage(MdpsessionmgmtMessage&& other) noexcept = default;
    MdpsessionmgmtMessage& operator=(MdpsessionmgmtMessage&& other) noexcept = default;
    ~MdpsessionmgmtMessage() = default;

    // Mdpsessionmgmt Payload: Branch
    const MdpsessionmgmtPayload* mdpsessionmgmt_payload() const;
    MdpsessionmgmtPayload* mdpsessionmgmt_payload();
    void set_mdpsessionmgmt_payload(std::unique_ptr<MdpsessionmgmtPayload> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;
    void bind(const Frame& frame) override;
    std::optional<TemplateId> bound_template_id() const override;

    bool operator==(const MdpsessionmgmtMessage& other) const;
    bool operator!=(const MdpsessionmgmtMessage& other) const;

  private:
    std::unique_ptr<MdpsessionmgmtPayload> mdpsessionmgmt_payload_{};
    // The Template Id the frame handed it, which selects its mdpsessionmgmt_payload
    TemplateId template_id_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
