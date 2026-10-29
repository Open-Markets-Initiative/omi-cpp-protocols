#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/RequestAckSecurityGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// NoSecurityGroups Block
class RequestAckSecurityGroups {
  public:

    RequestAckSecurityGroups() = default;
    RequestAckSecurityGroups(const GroupSize& group_size, const std::vector<RequestAckSecurityGroup>& request_ack_security_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Request Ack Security Group: Number of SecurityGroups acknowledged
    const std::vector<RequestAckSecurityGroup>& request_ack_security_group() const;
    std::vector<RequestAckSecurityGroup>& request_ack_security_group();
    void set_request_ack_security_group(const std::vector<RequestAckSecurityGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RequestAckSecurityGroups& other) const;
    bool operator!=(const RequestAckSecurityGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<RequestAckSecurityGroup> request_ack_security_group_{};
};

std::ostream& operator<<(std::ostream& out, const RequestAckSecurityGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_5
