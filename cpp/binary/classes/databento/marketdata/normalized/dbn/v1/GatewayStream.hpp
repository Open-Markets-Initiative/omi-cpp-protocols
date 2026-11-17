// Databento.MarketData.Normalized.Dbn.v1: GatewayStream.hpp
#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "messages/GatewayMessage.hpp"
#include "structs/AuthenticationResponse.hpp"
#include "structs/ChallengeRequest.hpp"
#include "structs/Greeting.hpp"
#include "structs/Metadata.hpp"
#include "structs/RecordHeader.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class GatewayMessageVisitor;

// The frame around one message: the record header and the message they select.
// Decode and encode here cover the headers; the packet decodes and encodes the message.
class GatewayFrame {
  public:
    GatewayFrame() = default;
    explicit GatewayFrame(std::unique_ptr<GatewayMessage> message);
    GatewayFrame(const GatewayFrame& other);
    GatewayFrame& operator=(const GatewayFrame& other);
    GatewayFrame(GatewayFrame&& other) noexcept = default;
    GatewayFrame& operator=(GatewayFrame&& other) noexcept = default;
    ~GatewayFrame() = default;

    // Record Header: DBN common header of every record
    const RecordHeader& record_header() const;
    RecordHeader& record_header();
    void set_record_header(const RecordHeader& value);

    // The message this frame carries, or null before one is set
    const GatewayMessage* message() const;
    GatewayMessage* message();
    void set_message(std::unique_ptr<GatewayMessage> message);
    std::unique_ptr<GatewayMessage> release();

    // Bytes inside the frame's declared size after its message ends, which the model does not
    // describe. They are kept as they came and written back, so the frame still encodes to the
    // bytes it was read from.
    const std::vector<std::byte>& trailer() const;
    std::vector<std::byte>& trailer();

    // The frame headers only
    std::size_t decode(const std::byte* data, std::size_t length);
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    // Same headers, the same trailer and, both present, the same message
    bool operator==(const GatewayFrame& other) const;
    bool operator!=(const GatewayFrame& other) const;

  private:
    RecordHeader record_header_{};
    std::unique_ptr<GatewayMessage> message_;
    std::vector<std::byte> trailer_;
};

// A run of bytes off a TCP connection, read into the frames it holds. A read stops at
// the first frame the bytes do not hold in full and reports how many it consumed, so the
// caller keeps the remainder and presents it again with more bytes behind it.
class GatewayStream {
  public:
    GatewayStream() = default;

    // Greeting: The message sent by the gateway immediately after a client connects
    // (lsg_version: the live gateway version)
    const Greeting& greeting() const;
    Greeting& greeting();
    void set_greeting(const Greeting& value);

    // Challenge Request: The gateway sends this message immediately following the greeting
    // message to authenticate the client (cram: a randomly-generated challenge string)
    const ChallengeRequest& challenge_request() const;
    ChallengeRequest& challenge_request();
    void set_challenge_request(const ChallengeRequest& value);

    // Authentication Response: The gateway sends this response following the client's
    // authentication request (success, and error or session_id)
    const AuthenticationResponse& authentication_response() const;
    AuthenticationResponse& authentication_response();
    void set_authentication_response(const AuthenticationResponse& value);

    // Metadata: DBN metadata header, once at the start of a file or stream
    const Metadata& metadata() const;
    Metadata& metadata();
    void set_metadata(const Metadata& value);

    // The frames, each holding one message
    const std::vector<GatewayFrame>& frames() const;
    std::vector<GatewayFrame>& frames();
    // Append a frame holding this message; the frame headers are derived on encode
    void add(std::unique_ptr<GatewayMessage> message);

    // Read every whole frame in the bytes at data, and return how many bytes that took.
    // What is left is a frame the run does not hold in full: keep it and read it again
    // with the bytes that follow. Throws DecodeError only on a frame that cannot be read.
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write a whole packet to the bytes at data, and return how many were written; throws EncodeError
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    std::size_t encoded_size() const;
    // Hand every message, in order, to the visitor
    void accept(GatewayMessageVisitor& visitor) const;
    void print(std::ostream& out) const;

    bool operator==(const GatewayStream& other) const;
    bool operator!=(const GatewayStream& other) const;

  private:
    Greeting greeting_{};
    ChallengeRequest challenge_request_{};
    AuthenticationResponse authentication_response_{};
    Metadata metadata_{};
    std::vector<GatewayFrame> frames_;
};

std::ostream& operator<<(std::ostream& out, const GatewayFrame& frame);
std::ostream& operator<<(std::ostream& out, const GatewayStream& packet);

} // namespace databento::marketdata::normalized::dbn::v1
