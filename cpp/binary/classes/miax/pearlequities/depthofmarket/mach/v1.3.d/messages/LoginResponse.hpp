// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginResponse.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../groups/LoginMatchingEngine.hpp"
#include "../messages/TcpMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class TcpMessageVisitor;

// The ESesM server sends a Login response packet in response to a Login request packet from
// the client
class LoginResponse : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = EsesmPacketType::LoginResponse;

    LoginResponse() = default;
    LoginResponse(std::uint8_t number_of_matching_engines, const std::vector<LoginMatchingEngine>& login_matching_engine);

    // Number Of Matching Engines: Count of all Matching Engines for the exchange
    std::uint8_t number_of_matching_engines() const;
    void set_number_of_matching_engines(std::uint8_t value);

    // Login Matching Engine: The login status, trading session and highest sequence number of
    // one matching engine, repeated once for each the login response counts
    const std::vector<LoginMatchingEngine>& login_matching_engine() const;
    std::vector<LoginMatchingEngine>& login_matching_engine();
    void set_login_matching_engine(const std::vector<LoginMatchingEngine>& value);

    // TcpMessage
    TcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TcpMessageVisitor& visitor) const override;
    std::unique_ptr<TcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TcpMessage& other) const override;

    bool operator==(const LoginResponse& other) const;
    bool operator!=(const LoginResponse& other) const;

  private:
    std::uint8_t number_of_matching_engines_{};
    std::vector<LoginMatchingEngine> login_matching_engine_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
