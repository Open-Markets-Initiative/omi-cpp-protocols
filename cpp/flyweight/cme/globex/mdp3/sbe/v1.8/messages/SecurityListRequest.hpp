#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SubscriptionReqType.hpp"
#include "../structs/SecurityListRequestSecurityGroups.hpp"
#include "../structs/SecurityListRequestRelatedSymbolGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// SecurityListRequest
class SecurityListRequest {
  public:
    static constexpr const char* name = "SecurityListRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityListRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityListRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    std::size_t encoded_size() const { return security_list_request_related_symbol_groups_end(); }

    std::uint32_t md_req_id() const { return wire::read_u32_le(at(0)); }

    SubscriptionReqType subscription_req_type() const { return static_cast<SubscriptionReqType>(wire::read_u8(at(4))); }

    SecurityListRequestSecurityGroups security_list_request_security_groups() const { return SecurityListRequestSecurityGroups{ bytes_.subspan(5) }; }

    SecurityListRequestRelatedSymbolGroups security_list_request_related_symbol_groups() const {
        wire::require("SecurityListRequest", security_list_request_security_groups_end() + SecurityListRequestRelatedSymbolGroups::minimum_size, bytes_.size());
        return SecurityListRequestRelatedSymbolGroups{ bytes_.subspan(security_list_request_security_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "SecurityListRequest{";
        out << "md_req_id=";
        out << md_req_id();
        out << ", subscription_req_type=";
        out << subscription_req_type();
        out << ", security_list_request_security_groups=";
        security_list_request_security_groups().print(out);
        out << ", security_list_request_related_symbol_groups=";
        security_list_request_related_symbol_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_list_request_security_groups_end() const { return 5 + security_list_request_security_groups().encoded_size(); }
    std::size_t security_list_request_related_symbol_groups_end() const { return security_list_request_security_groups_end() + security_list_request_related_symbol_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityListRequest& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
