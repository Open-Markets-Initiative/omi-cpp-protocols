#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/Greeting.hpp"
#include "../structs/ChallengeRequest.hpp"
#include "../structs/AuthenticationResponse.hpp"
#include "../structs/Metadata.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

// The gateway's control messages, then the DBN stream: its metadata, then records
class GatewayStream {
  public:
    static constexpr const char* name = "GatewayStream";

    // the bytes it reads, which it does not own: they must outlive it
    explicit GatewayStream(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every GatewayStream has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    std::size_t encoded_size() const { return metadata_end(); }

    Greeting greeting() const { return Greeting{ bytes_.subspan(0) }; }

    ChallengeRequest challenge_request() const {
        wire::require("GatewayStream", greeting_end() + ChallengeRequest::minimum_size, bytes_.size());
        return ChallengeRequest{ bytes_.subspan(greeting_end()) };
    }

    AuthenticationResponse authentication_response() const {
        wire::require("GatewayStream", challenge_request_end() + AuthenticationResponse::minimum_size, bytes_.size());
        return AuthenticationResponse{ bytes_.subspan(challenge_request_end()) };
    }

    Metadata metadata() const {
        wire::require("GatewayStream", authentication_response_end() + Metadata::minimum_size, bytes_.size());
        return Metadata{ bytes_.subspan(authentication_response_end()) };
    }

    void print(std::ostream& out) const {
        out << "GatewayStream{";
        out << "greeting=";
        greeting().print(out);
        out << ", challenge_request=";
        challenge_request().print(out);
        out << ", authentication_response=";
        authentication_response().print(out);
        out << ", metadata=";
        metadata().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t greeting_end() const { return 0 + greeting().encoded_size(); }
    std::size_t challenge_request_end() const { return greeting_end() + challenge_request().encoded_size(); }
    std::size_t authentication_response_end() const { return challenge_request_end() + authentication_response().encoded_size(); }
    std::size_t metadata_end() const { return authentication_response_end() + metadata().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const GatewayStream& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
