#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/SecurityListRequestSecurityGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// NoSecurityGroups Block
class SecurityListRequestSecurityGroups {
  public:

    SecurityListRequestSecurityGroups() = default;
    SecurityListRequestSecurityGroups(const GroupSize& group_size, const std::vector<SecurityListRequestSecurityGroup>& security_list_request_security_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Security List Request Security Group: Number of SecurityGroups specified in subscription
    // request. Should be equal 0, when subscription is requested for all groups on the segment
    // or individual Security IDs are listed in the criteria for subscription
    const std::vector<SecurityListRequestSecurityGroup>& security_list_request_security_group() const;
    std::vector<SecurityListRequestSecurityGroup>& security_list_request_security_group();
    void set_security_list_request_security_group(const std::vector<SecurityListRequestSecurityGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityListRequestSecurityGroups& other) const;
    bool operator!=(const SecurityListRequestSecurityGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<SecurityListRequestSecurityGroup> security_list_request_security_group_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityListRequestSecurityGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_5
