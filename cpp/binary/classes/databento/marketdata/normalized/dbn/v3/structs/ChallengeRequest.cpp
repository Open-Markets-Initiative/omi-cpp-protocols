// Databento.MarketData.Normalized.Dbn.v3: structs/ChallengeRequest.cpp
#include "ChallengeRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

ChallengeRequest::ChallengeRequest(const std::string& control_fields)
  : control_fields_(control_fields) {}

const std::string& ChallengeRequest::control_fields() const { return control_fields_; }
std::string& ChallengeRequest::control_fields() { return control_fields_; }
void ChallengeRequest::set_control_fields(const std::string& value) { control_fields_ = value; }

std::size_t ChallengeRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    {
        const std::size_t count = wire::terminated_length(data + offset, length - offset, 0);
        control_fields_ = wire::read_text(data + offset, count, '\0');
        offset += count + 1;
    }

    return offset;
}

std::size_t ChallengeRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ChallengeRequest", encoded_size(), capacity);

    wire::require_capacity("encode", offset + control_fields_.size() + 1, capacity);
    wire::write_text(data + offset, control_fields_.size(), '\0', control_fields_);
    offset += control_fields_.size();
    wire::write_u8(data + offset, 0);
    offset += 1;

    return offset;
}

std::size_t ChallengeRequest::encoded_size() const {
    return (control_fields_.size() + 1);
}

void ChallengeRequest::print(std::ostream& out) const {
    out << "ChallengeRequest{";
    out << "control_fields=";
    print::text(out, control_fields_);
    out << '}';
}

bool ChallengeRequest::operator==(const ChallengeRequest& other) const {
    return control_fields_ == other.control_fields_;
}

bool ChallengeRequest::operator!=(const ChallengeRequest& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ChallengeRequest& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
