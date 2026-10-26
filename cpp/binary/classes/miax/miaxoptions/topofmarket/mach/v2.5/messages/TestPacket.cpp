#include "TestPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

TestPacket::TestPacket(const std::string& test_text)
  : test_text_(test_text) {}

const std::string& TestPacket::test_text() const { return test_text_; }
std::string& TestPacket::test_text() { return test_text_; }
void TestPacket::set_test_text(const std::string& value) { test_text_ = value; }

TcpMessageCode TestPacket::type() const { return message_type; }

std::string_view TestPacket::name() const { return "Test Packet"; }

std::size_t TestPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    {
        const std::size_t count = length - offset;
        wire::require("TestPacket", offset + count, length);
        test_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t TestPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TestPacket", encoded_size(), capacity);

    wire::require_capacity("encode", offset + test_text_.size(), capacity);
    wire::write_text(data + offset, test_text_.size(), ' ', test_text_);
    offset += test_text_.size();

    return offset;
}

std::size_t TestPacket::encoded_size() const {
    return test_text_.size();
}

void TestPacket::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> TestPacket::clone() const {
    return std::make_unique<TestPacket>(*this);
}

void TestPacket::print(std::ostream& out) const {
    out << "TestPacket{";
    out << "test_text=";
    print::text(out, test_text_);
    out << '}';
}

bool TestPacket::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const TestPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool TestPacket::operator==(const TestPacket& other) const {
    return test_text_ == other.test_text_;
}

bool TestPacket::operator!=(const TestPacket& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
