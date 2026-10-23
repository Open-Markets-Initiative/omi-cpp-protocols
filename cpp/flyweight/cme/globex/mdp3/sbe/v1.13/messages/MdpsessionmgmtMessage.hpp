#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TemplateId.hpp"
#include "../messages/Negotiate.hpp"
#include "../messages/NegotiationReject.hpp"
#include "../messages/NegotiationResponse.hpp"
#include "../messages/Terminate.hpp"
#include "../messages/MarketDataRequest.hpp"
#include "../messages/RequestAck.hpp"
#include "../messages/RequestReject.hpp"
#include "../messages/SecurityListRequest.hpp"
#include "../messages/SecurityStatusRequest.hpp"
#include "../messages/SubscriberHeartbeat.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Message of sbe schema mdpsessionmgmt (schema id 2)
class MdpsessionmgmtMessage {
  public:
    static constexpr const char* name = "MdpsessionmgmtMessage";

    // the bytes it reads, which it does not own: they must outlive it
    // and the fields of the frame around it a branch in it switches on
    MdpsessionmgmtMessage(std::span<const std::byte> bytes, TemplateId template_id) noexcept
      : bytes_{ bytes }, template_id_{ template_id } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdpsessionmgmtMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    std::size_t encoded_size() const { return mdpsessionmgmt_payload_end(); }

    // the bytes the message it selects is read from
    std::span<const std::byte> mdpsessionmgmt_payload_bytes() const {
        wire::require("MdpsessionmgmtMessage", 0, bytes_.size());
        return bytes_.subspan(0);
    }

    // the message its template_id selects, handed to the handler as its view
    template <typename Handler>
    void mdpsessionmgmt_payload(Handler& handler) const {
        const auto bytes = mdpsessionmgmt_payload_bytes();
        switch (template_id_) {
            case TemplateId::Negotiate: {
                wire::require(Negotiate::name, Negotiate::minimum_size, bytes.size());
                const Negotiate message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::NegotiationReject: {
                wire::require(NegotiationReject::name, NegotiationReject::minimum_size, bytes.size());
                const NegotiationReject message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::NegotiationResponse: {
                wire::require(NegotiationResponse::name, NegotiationResponse::minimum_size, bytes.size());
                const NegotiationResponse message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::Terminate: {
                wire::require(Terminate::name, Terminate::minimum_size, bytes.size());
                const Terminate message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::MarketDataRequest: {
                wire::require(MarketDataRequest::name, MarketDataRequest::minimum_size, bytes.size());
                const MarketDataRequest message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::RequestAck: {
                wire::require(RequestAck::name, RequestAck::minimum_size, bytes.size());
                const RequestAck message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::RequestReject: {
                wire::require(RequestReject::name, RequestReject::minimum_size, bytes.size());
                const RequestReject message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SecurityListRequest: {
                wire::require(SecurityListRequest::name, SecurityListRequest::minimum_size, bytes.size());
                const SecurityListRequest message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SecurityStatusRequest: {
                wire::require(SecurityStatusRequest::name, SecurityStatusRequest::minimum_size, bytes.size());
                const SecurityStatusRequest message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TemplateId::SubscriberHeartbeat: {
                wire::require(SubscriberHeartbeat::name, SubscriberHeartbeat::minimum_size, bytes.size());
                const SubscriberHeartbeat message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(template_id_, bytes); }) { handler.on_unknown(template_id_, bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t mdpsessionmgmt_payload_size() const {
        const auto bytes = mdpsessionmgmt_payload_bytes();
        switch (template_id_) {
            case TemplateId::Negotiate: return Negotiate{ bytes }.encoded_size();
            case TemplateId::NegotiationReject: return NegotiationReject{ bytes }.encoded_size();
            case TemplateId::NegotiationResponse: return NegotiationResponse{ bytes }.encoded_size();
            case TemplateId::Terminate: return Terminate{ bytes }.encoded_size();
            case TemplateId::MarketDataRequest: return MarketDataRequest{ bytes }.encoded_size();
            case TemplateId::RequestAck: return RequestAck{ bytes }.encoded_size();
            case TemplateId::RequestReject: return RequestReject{ bytes }.encoded_size();
            case TemplateId::SecurityListRequest: return SecurityListRequest{ bytes }.encoded_size();
            case TemplateId::SecurityStatusRequest: return SecurityStatusRequest{ bytes }.encoded_size();
            case TemplateId::SubscriberHeartbeat: return SubscriberHeartbeat{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void mdpsessionmgmt_payload_print(std::ostream& out) const {
        const auto bytes = mdpsessionmgmt_payload_bytes();
        switch (template_id_) {
            case TemplateId::Negotiate: Negotiate{ bytes }.print(out); return;
            case TemplateId::NegotiationReject: NegotiationReject{ bytes }.print(out); return;
            case TemplateId::NegotiationResponse: NegotiationResponse{ bytes }.print(out); return;
            case TemplateId::Terminate: Terminate{ bytes }.print(out); return;
            case TemplateId::MarketDataRequest: MarketDataRequest{ bytes }.print(out); return;
            case TemplateId::RequestAck: RequestAck{ bytes }.print(out); return;
            case TemplateId::RequestReject: RequestReject{ bytes }.print(out); return;
            case TemplateId::SecurityListRequest: SecurityListRequest{ bytes }.print(out); return;
            case TemplateId::SecurityStatusRequest: SecurityStatusRequest{ bytes }.print(out); return;
            case TemplateId::SubscriberHeartbeat: SubscriberHeartbeat{ bytes }.print(out); return;
            default:
                out << "UnknownMdpsessionmgmtPayload{type=" << template_id_ << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "MdpsessionmgmtMessage{";
        out << "mdpsessionmgmt_payload=";
        mdpsessionmgmt_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t mdpsessionmgmt_payload_end() const { return 0 + mdpsessionmgmt_payload_size(); }

    std::span<const std::byte> bytes_;
    // the Template Id the frame handed it, which selects its mdpsessionmgmt_payload
    TemplateId template_id_;
};

inline std::ostream& operator<<(std::ostream& out, const MdpsessionmgmtMessage& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
