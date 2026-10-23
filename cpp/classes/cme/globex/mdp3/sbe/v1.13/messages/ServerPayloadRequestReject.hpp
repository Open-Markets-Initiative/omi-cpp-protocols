#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/MdReqRejReason.hpp"
#include "../messages/ServerTcpMessage.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// RequestReject
class ServerPayloadRequestReject : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::RequestReject;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 105;

    ServerPayloadRequestReject() = default;
    ServerPayloadRequestReject(std::optional<std::uint32_t> md_req_id_optional, MdReqRejReason md_req_rej_reason, const std::string& text);

    // Md Req Id Optional: Unique identifier for Market Data Request
    std::optional<std::uint32_t> md_req_id_optional() const;
    void set_md_req_id_optional(std::optional<std::uint32_t> value);

    // Md Req Rej Reason: Market Data Request Reject reason code
    MdReqRejReason md_req_rej_reason() const;
    void set_md_req_rej_reason(MdReqRejReason value);

    // Text: Reject reason details
    const std::string& text() const;
    std::string& text();
    void set_text(const std::string& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadRequestReject& other) const;
    bool operator!=(const ServerPayloadRequestReject& other) const;

  private:
    std::optional<std::uint32_t> md_req_id_optional_{};
    MdReqRejReason md_req_rej_reason_{};
    std::string text_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
