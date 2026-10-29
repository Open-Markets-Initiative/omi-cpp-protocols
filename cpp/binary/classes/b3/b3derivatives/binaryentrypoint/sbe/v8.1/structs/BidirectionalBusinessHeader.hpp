#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// BidirectionalBusinessHeader
class BidirectionalBusinessHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 19;

    BidirectionalBusinessHeader() = default;
    BidirectionalBusinessHeader(std::uint32_t session_id, std::uint32_t msg_seq_num, std::optional<std::chrono::nanoseconds> sending_time, std::uint8_t poss_resend, std::uint8_t market_segment_id_optional, char padding);

    // Session Id: sessionID
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Msg Seq Num: msgSeqNum
    std::uint32_t msg_seq_num() const;
    void set_msg_seq_num(std::uint32_t value);

    // Sending Time: sendingTime
    std::optional<std::chrono::nanoseconds> sending_time() const;
    void set_sending_time(std::optional<std::chrono::nanoseconds> value);

    // Poss Resend: possResend
    std::uint8_t poss_resend() const;
    void set_poss_resend(std::uint8_t value);

    // Market Segment Id Optional: marketSegmentID
    std::uint8_t market_segment_id_optional() const;
    void set_market_segment_id_optional(std::uint8_t value);

    // Padding: padding
    char padding() const;
    void set_padding(char value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BidirectionalBusinessHeader& other) const;
    bool operator!=(const BidirectionalBusinessHeader& other) const;

  private:
    std::uint32_t session_id_{};
    std::uint32_t msg_seq_num_{};
    std::optional<std::chrono::nanoseconds> sending_time_{};
    std::uint8_t poss_resend_{};
    std::uint8_t market_segment_id_optional_{};
    char padding_{};
};

std::ostream& operator<<(std::ostream& out, const BidirectionalBusinessHeader& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
