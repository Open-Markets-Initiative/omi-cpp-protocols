// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/details/SecurityDefinitionMessageWriter.hpp
#pragma once

#include "../SecurityDefinitionMessage.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

class security_definition_message_group_writer;
class security_definition_message_after_security_type;
class security_definition_message_after_symbol;
class security_definition_message_after_target_location_id;
class security_definition_message_after_currency_code;
class security_definition_message_after_underlying_symbol;
class security_definition_message_after_underlying_type;
class security_definition_message_security_definition_leg_writer;

// Stub builder — siblings > 1 not yet implemented. Group: packet.message.payload.securitydefinitionmessage.securitydefinitionleg
class security_definition_message_security_definition_leg_writer {
    public:
    security_definition_message_security_definition_leg_writer() = default;
    security_definition_message_security_definition_leg_writer(std::byte*, std::byte*, std::byte*) {}
    security_definition_message_security_definition_leg_writer& add_entry(const security_definition_message_security_definition_leg_entry&) { return *this; }
    std::byte* finish() { return nullptr; }
};

class security_definition_message_after_security_type {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_security_type(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_after_symbol symbol(std::string_view v);
};

class security_definition_message_after_symbol {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_symbol(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_after_target_location_id target_location_id(std::string_view v);
};

class security_definition_message_after_target_location_id {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_target_location_id(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_after_currency_code currency_code(std::string_view v);
};

class security_definition_message_after_currency_code {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_currency_code(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_after_underlying_symbol underlying_symbol(std::string_view v);
};

class security_definition_message_after_underlying_symbol {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_underlying_symbol(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_after_underlying_type underlying_type(std::string_view v);
};

class security_definition_message_after_underlying_type {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_underlying_type(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_security_definition_leg_writer start_security_definition_leg() {
        return { msg_start_, pos_, end_ };
    }
};

class security_definition_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_after_security_type security_type(std::string_view v) {
        if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
        std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
        return { msg_start_, next_pos, end_ };
    }
};

inline security_definition_message_after_symbol security_definition_message_after_security_type::symbol(std::string_view v) {
    if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
    std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
    return { msg_start_, next_pos, end_ };
}

inline security_definition_message_after_target_location_id security_definition_message_after_symbol::target_location_id(std::string_view v) {
    if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
    std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
    return { msg_start_, next_pos, end_ };
}

inline security_definition_message_after_currency_code security_definition_message_after_target_location_id::currency_code(std::string_view v) {
    if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
    std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
    return { msg_start_, next_pos, end_ };
}

inline security_definition_message_after_underlying_symbol security_definition_message_after_currency_code::underlying_symbol(std::string_view v) {
    if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
    std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
    return { msg_start_, next_pos, end_ };
}

inline security_definition_message_after_underlying_type security_definition_message_after_underlying_symbol::underlying_type(std::string_view v) {
    if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
    std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
    return { msg_start_, next_pos, end_ };
}



inline security_definition_message_group_writer start_group_write(security_definition_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + security_definition_message::tail_capacity };
}
}
