#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/CancelOnDisconnectType.hpp"
#include "../messages/Message.hpp"
#include "../structs/Credentials.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// EstablishMessage
class EstablishMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::EstablishMessage;

    EstablishMessage() = default;
    EstablishMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds timestamp, std::uint64_t keep_alive_interval, std::uint32_t next_seq_no, CancelOnDisconnectType cancel_on_disconnect_type, const std::array<std::byte, 1>& offset_33_padding_1, std::uint64_t cod_timeout_window, const Credentials& credentials);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Session Ver Id: sessionVerID
    std::uint64_t session_ver_id() const;
    void set_session_ver_id(std::uint64_t value);

    // Timestamp: timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Keep Alive Interval: keepAliveInterval
    std::uint64_t keep_alive_interval() const;
    void set_keep_alive_interval(std::uint64_t value);

    // Next Seq No: nextSeqNo
    std::uint32_t next_seq_no() const;
    void set_next_seq_no(std::uint32_t value);

    // Cancel On Disconnect Type: cancelOnDisconnectType
    CancelOnDisconnectType cancel_on_disconnect_type() const;
    void set_cancel_on_disconnect_type(CancelOnDisconnectType value);

    // Offset 33 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_33_padding_1() const;
    std::array<std::byte, 1>& offset_33_padding_1();
    void set_offset_33_padding_1(const std::array<std::byte, 1>& value);

    // Cod Timeout Window: codTimeoutWindow
    std::uint64_t cod_timeout_window() const;
    void set_cod_timeout_window(std::uint64_t value);

    // Credentials: credentials data struct
    const Credentials& credentials() const;
    Credentials& credentials();
    void set_credentials(const Credentials& value);

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

    bool operator==(const EstablishMessage& other) const;
    bool operator!=(const EstablishMessage& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint64_t session_ver_id_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t keep_alive_interval_{};
    std::uint32_t next_seq_no_{};
    CancelOnDisconnectType cancel_on_disconnect_type_{};
    std::array<std::byte, 1> offset_33_padding_1_{};
    std::uint64_t cod_timeout_window_{};
    Credentials credentials_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
