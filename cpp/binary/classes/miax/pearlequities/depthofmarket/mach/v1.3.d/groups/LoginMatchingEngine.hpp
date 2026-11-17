// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: groups/LoginMatchingEngine.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/LoginStatus.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The login status, trading session and highest sequence number of one matching engine,
// repeated once for each the login response counts
class LoginMatchingEngine {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 10;

    LoginMatchingEngine() = default;
    LoginMatchingEngine(LoginStatus login_status, std::uint8_t trading_session_id, std::uint64_t highest_sequence_number);

    // Login Status: Login Status
    LoginStatus login_status() const;
    void set_login_status(LoginStatus value);

    // Trading Session Id: The current trading session ID of the corresponding Matching Engine
    std::uint8_t trading_session_id() const;
    void set_trading_session_id(std::uint8_t value);

    // Highest Sequence Number: The highest sequence number the server currently has for the
    // client from the Matching Engine
    std::uint64_t highest_sequence_number() const;
    void set_highest_sequence_number(std::uint64_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const LoginMatchingEngine& other) const;
    bool operator!=(const LoginMatchingEngine& other) const;

  private:
    LoginStatus login_status_{};
    std::uint8_t trading_session_id_{};
    std::uint64_t highest_sequence_number_{};
};

std::ostream& operator<<(std::ostream& out, const LoginMatchingEngine& value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
