#pragma once

#include <cstddef>
#include <ostream>
#include <string>

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of SecurityGroups acknowledged
class RequestAckSecurityGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 6;

    RequestAckSecurityGroup() = default;
    RequestAckSecurityGroup(const std::string& security_group);

    // Security Group: Security Group
    const std::string& security_group() const;
    std::string& security_group();
    void set_security_group(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RequestAckSecurityGroup& other) const;
    bool operator!=(const RequestAckSecurityGroup& other) const;

  private:
    std::string security_group_{};
};

std::ostream& operator<<(std::ostream& out, const RequestAckSecurityGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
