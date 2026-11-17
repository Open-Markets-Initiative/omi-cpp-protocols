// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginRequest.cpp
#include "LoginRequest.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

LoginRequest::LoginRequest(const std::string& esesm_version, const std::string& username, const std::string& computer_id, const std::string& application_protocol, std::uint8_t number_of_matching_engines, const std::vector<RequestedMatchingEngine>& requested_matching_engine)
  : esesm_version_(esesm_version), username_(username), computer_id_(computer_id), application_protocol_(application_protocol), number_of_matching_engines_(number_of_matching_engines), requested_matching_engine_(requested_matching_engine) {}

const std::string& LoginRequest::esesm_version() const { return esesm_version_; }
std::string& LoginRequest::esesm_version() { return esesm_version_; }
void LoginRequest::set_esesm_version(const std::string& value) { esesm_version_ = value; }

const std::string& LoginRequest::username() const { return username_; }
std::string& LoginRequest::username() { return username_; }
void LoginRequest::set_username(const std::string& value) { username_ = value; }

const std::string& LoginRequest::computer_id() const { return computer_id_; }
std::string& LoginRequest::computer_id() { return computer_id_; }
void LoginRequest::set_computer_id(const std::string& value) { computer_id_ = value; }

const std::string& LoginRequest::application_protocol() const { return application_protocol_; }
std::string& LoginRequest::application_protocol() { return application_protocol_; }
void LoginRequest::set_application_protocol(const std::string& value) { application_protocol_ = value; }

std::uint8_t LoginRequest::number_of_matching_engines() const { return number_of_matching_engines_; }
void LoginRequest::set_number_of_matching_engines(std::uint8_t value) { number_of_matching_engines_ = value; }

const std::vector<RequestedMatchingEngine>& LoginRequest::requested_matching_engine() const { return requested_matching_engine_; }
std::vector<RequestedMatchingEngine>& LoginRequest::requested_matching_engine() { return requested_matching_engine_; }
void LoginRequest::set_requested_matching_engine(const std::vector<RequestedMatchingEngine>& value) { requested_matching_engine_ = value; }

TcpMessageCode LoginRequest::type() const { return message_type; }

std::string_view LoginRequest::name() const { return "Login Request"; }

std::size_t LoginRequest::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("LoginRequest", offset + 5, length);
    esesm_version_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::require("LoginRequest", offset + 5, length);
    username_ = wire::read_text(data + offset, 5, ' ');
    offset += 5;

    wire::require("LoginRequest", offset + 8, length);
    computer_id_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    wire::require("LoginRequest", offset + 8, length);
    application_protocol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    wire::require("LoginRequest", offset + 1, length);
    number_of_matching_engines_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(number_of_matching_engines_);
        requested_matching_engine_.clear();
        requested_matching_engine_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            RequestedMatchingEngine entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            requested_matching_engine_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t LoginRequest::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginRequest", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto number_of_matching_engines = number_of_matching_engines_;
    number_of_matching_engines = static_cast<std::uint8_t>(requested_matching_engine_.size());

    wire::write_text(data + offset, 5, ' ', esesm_version_);
    offset += 5;

    wire::write_text(data + offset, 5, ' ', username_);
    offset += 5;

    wire::write_text(data + offset, 8, ' ', computer_id_);
    offset += 8;

    wire::write_text(data + offset, 8, ' ', application_protocol_);
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_matching_engines));
    offset += 1;

    for (const auto& entry : requested_matching_engine_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LoginRequest::encoded_size() const {
    return 5 + 5 + 8 + 8 + 1 + wire::encoded_size_of(requested_matching_engine_);
}

void LoginRequest::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginRequest::clone() const {
    return std::make_unique<LoginRequest>(*this);
}

void LoginRequest::print(std::ostream& out) const {
    out << "LoginRequest{";
    out << "esesm_version=";
    print::text(out, esesm_version_);
    out << ", username=";
    print::text(out, username_);
    out << ", computer_id=";
    print::text(out, computer_id_);
    out << ", application_protocol=";
    print::text(out, application_protocol_);
    out << ", number_of_matching_engines=";
    out << static_cast<int>(number_of_matching_engines_);
    out << ", requested_matching_engine=";
    print::sequence(out, requested_matching_engine_);
    out << '}';
}

bool LoginRequest::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginRequest*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginRequest::operator==(const LoginRequest& other) const {
    return esesm_version_ == other.esesm_version_
        && username_ == other.username_
        && computer_id_ == other.computer_id_
        && application_protocol_ == other.application_protocol_
        && number_of_matching_engines_ == other.number_of_matching_engines_
        && requested_matching_engine_ == other.requested_matching_engine_;
}

bool LoginRequest::operator!=(const LoginRequest& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
