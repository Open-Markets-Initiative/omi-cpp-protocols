#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/ClientAppName.hpp"
#include "../structs/ClientAppVersion.hpp"
#include "../structs/ClientIp.hpp"
#include "../structs/Credentials.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// NegotiateMessage
class NegotiateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::NegotiateMessage;

    NegotiateMessage() = default;
    NegotiateMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds timestamp, std::uint32_t entering_firm, std::optional<std::uint32_t> onbehalf_firm, const Credentials& credentials, const ClientIp& client_ip, const ClientAppName& client_app_name, const ClientAppVersion& client_app_version);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Session Ver Id: sessionVerID
    std::uint64_t session_ver_id() const;
    void set_session_ver_id(std::uint64_t value);

    // Timestamp: timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Entering Firm: enteringFirm
    std::uint32_t entering_firm() const;
    void set_entering_firm(std::uint32_t value);

    // Onbehalf Firm: onbehalfFirm
    std::optional<std::uint32_t> onbehalf_firm() const;
    void set_onbehalf_firm(std::optional<std::uint32_t> value);

    // Credentials: credentials data struct
    const Credentials& credentials() const;
    Credentials& credentials();
    void set_credentials(const Credentials& value);

    // Client Ip: clientIP data struct
    const ClientIp& client_ip() const;
    ClientIp& client_ip();
    void set_client_ip(const ClientIp& value);

    // Client App Name: clientAppName data struct
    const ClientAppName& client_app_name() const;
    ClientAppName& client_app_name();
    void set_client_app_name(const ClientAppName& value);

    // Client App Version: clientAppVersion data struct
    const ClientAppVersion& client_app_version() const;
    ClientAppVersion& client_app_version();
    void set_client_app_version(const ClientAppVersion& value);

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

    bool operator==(const NegotiateMessage& other) const;
    bool operator!=(const NegotiateMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint64_t session_ver_id_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t entering_firm_{};
    std::optional<std::uint32_t> onbehalf_firm_{};
    Credentials credentials_{};
    ClientIp client_ip_{};
    ClientAppName client_app_name_{};
    ClientAppVersion client_app_version_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
