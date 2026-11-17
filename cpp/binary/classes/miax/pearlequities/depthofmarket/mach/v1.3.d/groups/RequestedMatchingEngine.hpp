// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: groups/RequestedMatchingEngine.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The trading session and sequence number the client asks of one matching engine, repeated
// once for each the login request counts
class RequestedMatchingEngine {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 9;

    RequestedMatchingEngine() = default;
    RequestedMatchingEngine(std::uint8_t requested_trading_session_id, std::uint64_t requested_sequence_number);

    // Requested Trading Session Id: Specifies the Matching Engine trading session the client
    // would like to log into, or zero to log into the currently active trading session
    std::uint8_t requested_trading_session_id() const;
    void set_requested_trading_session_id(std::uint8_t value);

    // Requested Sequence Number: Specifies client requested sequence number for the Matching
    // Engine
    std::uint64_t requested_sequence_number() const;
    void set_requested_sequence_number(std::uint64_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RequestedMatchingEngine& other) const;
    bool operator!=(const RequestedMatchingEngine& other) const;

  private:
    std::uint8_t requested_trading_session_id_{};
    std::uint64_t requested_sequence_number_{};
};

std::ostream& operator<<(std::ostream& out, const RequestedMatchingEngine& value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
