#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/ClientTcpMessage.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ClientTcpMessageVisitor;

// Negotiate
class ClientPayloadNegotiate : public ClientTcpMessage {
  public:
    // The code that selects this message
    static constexpr ClientTcpMessageCode message_type = TemplateId::Negotiate;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 78;

    ClientPayloadNegotiate() = default;
    ClientPayloadNegotiate(const std::string& hmac_signature, const std::string& access_key_id, std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, const std::string& session, const std::string& firm);

    // Hmac Signature: Contains the HMAC signature
    const std::string& hmac_signature() const;
    std::string& hmac_signature();
    void set_hmac_signature(const std::string& value);

    // Access Key Id: Contains the AccessKeyID assigned to this session on this port
    const std::string& access_key_id() const;
    std::string& access_key_id();
    void set_access_key_id(const std::string& value);

    // Uuid: Session Identifier defined as type long uInt64, recommended to use timestamp as
    // number of microseconds since Unix epoch
    std::uint64_t uuid() const;
    void set_uuid(std::uint64_t value);

    // Request Timestamp: Time of request, recommended to use timestamp as number of
    // nanoseconds since Unix epoch
    std::chrono::nanoseconds request_timestamp() const;
    void set_request_timestamp(std::chrono::nanoseconds value);

    // Session: Session ID
    const std::string& session() const;
    std::string& session();
    void set_session(const std::string& value);

    // Firm: Firm ID
    const std::string& firm() const;
    std::string& firm();
    void set_firm(const std::string& value);

    // ClientTcpMessage
    ClientTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ClientTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ClientTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ClientTcpMessage& other) const override;

    bool operator==(const ClientPayloadNegotiate& other) const;
    bool operator!=(const ClientPayloadNegotiate& other) const;

  private:
    std::string hmac_signature_{};
    std::string access_key_id_{};
    std::uint64_t uuid_{};
    std::chrono::nanoseconds request_timestamp_{};
    std::string session_{};
    std::string firm_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
