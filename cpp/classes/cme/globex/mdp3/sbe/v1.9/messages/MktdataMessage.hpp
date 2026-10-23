#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../messages/MktdataPayload.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

class Visitor;
class MktdataPayloadVisitor;

// Message of sbe schema mktdata (schema id 1)
class MktdataMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = SchemaId::Mktdata;

    MktdataMessage() = default;
    MktdataMessage(const MktdataMessage& other);
    MktdataMessage& operator=(const MktdataMessage& other);
    MktdataMessage(MktdataMessage&& other) noexcept = default;
    MktdataMessage& operator=(MktdataMessage&& other) noexcept = default;
    ~MktdataMessage() = default;

    // Mktdata Payload: Branch
    const MktdataPayload* mktdata_payload() const;
    MktdataPayload* mktdata_payload();
    void set_mktdata_payload(std::unique_ptr<MktdataPayload> value);

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

    bool operator==(const MktdataMessage& other) const;
    bool operator!=(const MktdataMessage& other) const;

  private:
    std::unique_ptr<MktdataPayload> mktdata_payload_{};
    // The Template Id the frame handed it, which selects its mktdata_payload
    TemplateId template_id_{};
};

} // namespace cme::globex::mdp3::sbe::v1_9
