#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class TcpMessageVisitor;

// Test packets are intended to provide human readable text that may aid in debugging problems
class TestPacket : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = SesmPacketType::TestPacket;

    TestPacket() = default;
    TestPacket(const std::string& test_text);

    // Test Text: Free form human readable text
    const std::string& test_text() const;
    std::string& test_text();
    void set_test_text(const std::string& value);

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

    bool operator==(const TestPacket& other) const;
    bool operator!=(const TestPacket& other) const;

  private:
    std::string test_text_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
