#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SubscriptionReqType.hpp"
#include "../enums/MdReqIdStatus.hpp"
#include "../structs/RequestAckSecurityGroups.hpp"
#include "../structs/RequestAckRelatedSymbolGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// RequestAck
class ServerPayloadRequestAck {
  public:
    static constexpr const char* name = "ServerPayloadRequestAck";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadRequestAck(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadRequestAck has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 6;
    std::size_t encoded_size() const { return request_ack_related_symbol_groups_end(); }

    std::uint32_t md_req_id() const { return wire::read_u32_le(at(0)); }

    SubscriptionReqType subscription_req_type() const { return static_cast<SubscriptionReqType>(wire::read_u8(at(4))); }

    MdReqIdStatus md_req_id_status() const { return static_cast<MdReqIdStatus>(wire::read_u8(at(5))); }

    RequestAckSecurityGroups request_ack_security_groups() const { return RequestAckSecurityGroups{ bytes_.subspan(6) }; }

    RequestAckRelatedSymbolGroups request_ack_related_symbol_groups() const {
        wire::require("ServerPayloadRequestAck", request_ack_security_groups_end() + RequestAckRelatedSymbolGroups::minimum_size, bytes_.size());
        return RequestAckRelatedSymbolGroups{ bytes_.subspan(request_ack_security_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "ServerPayloadRequestAck{";
        out << "md_req_id=";
        out << md_req_id();
        out << ", subscription_req_type=";
        out << subscription_req_type();
        out << ", md_req_id_status=";
        out << md_req_id_status();
        out << ", request_ack_security_groups=";
        request_ack_security_groups().print(out);
        out << ", request_ack_related_symbol_groups=";
        request_ack_related_symbol_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t request_ack_security_groups_end() const { return 6 + request_ack_security_groups().encoded_size(); }
    std::size_t request_ack_related_symbol_groups_end() const { return request_ack_security_groups_end() + request_ack_related_symbol_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadRequestAck& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
