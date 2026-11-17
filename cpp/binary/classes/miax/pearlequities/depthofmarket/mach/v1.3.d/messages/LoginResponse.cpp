// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/LoginResponse.cpp
#include "LoginResponse.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

LoginResponse::LoginResponse(std::uint8_t number_of_matching_engines, const std::vector<LoginMatchingEngine>& login_matching_engine)
  : number_of_matching_engines_(number_of_matching_engines), login_matching_engine_(login_matching_engine) {}

std::uint8_t LoginResponse::number_of_matching_engines() const { return number_of_matching_engines_; }
void LoginResponse::set_number_of_matching_engines(std::uint8_t value) { number_of_matching_engines_ = value; }

const std::vector<LoginMatchingEngine>& LoginResponse::login_matching_engine() const { return login_matching_engine_; }
std::vector<LoginMatchingEngine>& LoginResponse::login_matching_engine() { return login_matching_engine_; }
void LoginResponse::set_login_matching_engine(const std::vector<LoginMatchingEngine>& value) { login_matching_engine_ = value; }

TcpMessageCode LoginResponse::type() const { return message_type; }

std::string_view LoginResponse::name() const { return "Login Response"; }

std::size_t LoginResponse::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("LoginResponse", offset + 1, length);
    number_of_matching_engines_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(number_of_matching_engines_);
        login_matching_engine_.clear();
        login_matching_engine_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            LoginMatchingEngine entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            login_matching_engine_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t LoginResponse::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginResponse", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto number_of_matching_engines = number_of_matching_engines_;
    number_of_matching_engines = static_cast<std::uint8_t>(login_matching_engine_.size());

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_matching_engines));
    offset += 1;

    for (const auto& entry : login_matching_engine_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LoginResponse::encoded_size() const {
    return 1 + wire::encoded_size_of(login_matching_engine_);
}

void LoginResponse::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> LoginResponse::clone() const {
    return std::make_unique<LoginResponse>(*this);
}

void LoginResponse::print(std::ostream& out) const {
    out << "LoginResponse{";
    out << "number_of_matching_engines=";
    out << static_cast<int>(number_of_matching_engines_);
    out << ", login_matching_engine=";
    print::sequence(out, login_matching_engine_);
    out << '}';
}

bool LoginResponse::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const LoginResponse*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginResponse::operator==(const LoginResponse& other) const {
    return number_of_matching_engines_ == other.number_of_matching_engines_
        && login_matching_engine_ == other.login_matching_engine_;
}

bool LoginResponse::operator!=(const LoginResponse& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
