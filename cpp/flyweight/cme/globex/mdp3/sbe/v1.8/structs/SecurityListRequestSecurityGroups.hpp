#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSize.hpp"
#include "../groups/SecurityListRequestSecurityGroup.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// NoSecurityGroups Block
class SecurityListRequestSecurityGroups {
  public:
    static constexpr const char* name = "SecurityListRequestSecurityGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityListRequestSecurityGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityListRequestSecurityGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return security_list_request_security_group_end(); }

    GroupSize group_size() const { return GroupSize{ bytes_.subspan(0) }; }

    view::entries<SecurityListRequestSecurityGroup> security_list_request_security_group() const { return view::entries<SecurityListRequestSecurityGroup>{ bytes_.subspan(3), wire::count(group_size().num_in_group()), wire::count(group_size().block_length()) }; }

    void print(std::ostream& out) const {
        out << "SecurityListRequestSecurityGroups{";
        out << "group_size=";
        group_size().print(out);
        out << ", security_list_request_security_group=";
        print::sequence(out, security_list_request_security_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_list_request_security_group_end() const { return 3 + security_list_request_security_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityListRequestSecurityGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
