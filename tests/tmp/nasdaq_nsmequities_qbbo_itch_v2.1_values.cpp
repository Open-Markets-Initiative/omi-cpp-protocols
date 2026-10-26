// Nasdaq.NsmEquities.Qbbo.Itch.v2.1 canonical values, through the Tmp header: every value the Tmp reading hands
// over from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/tmp/nasdaq/nsmequities/qbbo/itch/v2.1/nasdaq_nsmequities_qbbo_itch_v2_1.hpp"

// Nasdaq NsmEquities Qbbo Itch 2.1: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

/////////////////////////////////////////////////////////////////////
// Reading
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // Thrown when the bytes end before what they must hold
    struct short_read : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    inline void require(std::size_t needed, std::size_t available) {
        if (needed > available) {
            throw short_read(std::to_string(needed) + " bytes needed, " + std::to_string(available) + " available");
        }
    }

    // The bytes left for a member when the members after it take some: refused when fewer remain
    inline std::size_t leaving(std::size_t available, std::size_t taken) {
        require(taken, available);
        return available - taken;
    }

    // Hand the handler a value, when it takes one
    template <typename Handler, typename T>
    constexpr void call(Handler& handler, const T& value) {
        if constexpr (requires { handler(value); }) { handler(value); }
    }

    // A type laid over its bytes, handed to the handler
    template <typename T, typename Handler>
    const T& read(const std::byte* data, std::size_t length, Handler& handler) {
        require(T::size, length);
        const auto& value = *reinterpret_cast<const T*>(data);
        call(handler, value);
        return value;
    }

    // A field as a rule reads it: an enum by the code the wire holds, a field by its value, and a
    // bit - which its bitfield answers as a value - as it is
    template <typename T>
    constexpr auto rule(const T& field) noexcept {
        if constexpr (requires { field.raw(); }) { return field.raw(); }
        else if constexpr (requires { field.value(); }) { return field.value(); }
        else { return field; }
    }

    // A field an optional member may hold, read as its type's zero when the member is absent
    template <typename T>
    struct maybe {
        const T* field;

        constexpr auto value() const noexcept {
            using type = decltype(field->value());
            return field != nullptr ? field->value() : type{};
        }

        constexpr auto raw() const noexcept requires requires(const T& held) { held.raw(); } {
            using type = decltype(field->raw());
            return field != nullptr ? field->raw() : type{};
        }

        // a bit of an optional bitfield, nothing when the bitfield is absent
        template <typename Bit>
        constexpr auto get() const noexcept requires requires(const T& held) { held.template get<Bit>(); } {
            using type = std::remove_cvref_t<decltype(field->template get<Bit>())>;
            return field != nullptr ? type{ field->template get<Bit>() } : type{};
        }
    };

    // A type laid over its bytes without handing it on: a frame's length, read before the frame is
    template <typename T>
    const T& at(const std::byte* data) noexcept {
        return *reinterpret_cast<const T*>(data);
    }

    // A type laid over bytes ahead of the walk, at a place every byte before it fixes, which a rule
    // reads before the walk reaches it: a branch's code in the header its messages begin with
    template <typename T>
    const T& ahead(const std::byte* data, std::size_t length, std::size_t at) {
        require(at + T::size, length);
        return *reinterpret_cast<const T*>(data + at);
    }

    // A type laid over its bytes and handed to the handler; what it returns is the bytes it took
    template <typename T, typename Handler>
    std::size_t take(const std::byte* data, std::size_t length, Handler& handler) {
        read<T>(data, length, handler);
        return T::size;
    }

    // The characters before a terminating zero, which the bytes must hold
    inline std::size_t terminated(const std::byte* data, std::size_t length) {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == std::byte{ 0 }) { return index; }
        }
        throw short_read("no terminator in " + std::to_string(length) + " bytes");
    }

    // The bytes of a frame ending on a terminator, the terminator included; none while the bytes
    // do not hold it yet
    inline std::size_t through(const std::byte* data, std::size_t length, std::byte terminator) noexcept {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == terminator) { return index + 1; }
        }
        return 0;
    }

    // Bytes a branch's code selects no message for, handed to the handler when it takes them
    template <typename Handler>
    void unknown(Handler& handler, const std::byte* data, std::size_t length) {
        if constexpr (requires { handler.unknown(data, length); }) { handler.unknown(data, length); }
    }

    // How many a count or a length states: a number, or digits of text
    template <typename T>
        requires std::is_integral_v<T>
    constexpr std::size_t count(T value) noexcept { return static_cast<std::size_t>(value); }

    inline std::size_t count(char digit) {
        if (digit < '0' || digit > '9') { throw short_read(std::string("'") + digit + "' is not a digit"); }
        return static_cast<std::size_t>(digit - '0');
    }

    inline std::size_t count(std::string_view digits) {
        std::size_t value = 0;
        for (const char digit : digits) {
            if (digit == ' ') { continue; }
            if (digit < '0' || digit > '9') { throw short_read("\"" + std::string(digits) + "\" is not a number"); }
            value = value * 10 + static_cast<std::size_t>(digit - '0');
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Parsing
/////////////////////////////////////////////////////////////////////

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_directory_message_ = tmp::read<stock_directory_message>(data + offset, bound - offset, handler); offset += stock_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_trading_action_message_ = tmp::read<stock_trading_action_message>(data + offset, bound - offset, handler); offset += stock_trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Y')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reg_sho_restriction_message_ = tmp::read<reg_sho_restriction_message>(data + offset, bound - offset, handler); offset += reg_sho_restriction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'V')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_decline_level_message_ = tmp::read<mwcb_decline_level_message>(data + offset, bound - offset, handler); offset += mwcb_decline_level_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'W')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& mwcb_breach_message_ = tmp::read<mwcb_breach_message>(data + offset, bound - offset, handler); offset += mwcb_breach_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'h')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& operational_halt_message_ = tmp::read<operational_halt_message>(data + offset, bound - offset, handler); offset += operational_halt_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& bbo_quotation_message_ = tmp::read<bbo_quotation_message>(data + offset, bound - offset, handler); offset += bbo_quotation_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'N')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& price_improvement_message_ = tmp::read<price_improvement_message>(data + offset, bound - offset, handler); offset += price_improvement_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'K')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& ipo_quoting_period_update_message_ = tmp::read<ipo_quoting_period_update_message>(data + offset, bound - offset, handler); offset += ipo_quoting_period_update_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) + 2);
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) - 1);
        tmp::require(offset + size, bound);
        parse_payload(data + offset, size, handler, message_header_.template get<message_type>());
        offset += size;
    }
    return bound;
}

// Messages: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_messages([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_count& message_count_) {
    if (static_cast<bool>(tmp::rule(message_count_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_count_) == 65535)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            std::size_t count = static_cast<std::size_t>(tmp::rule(message_count_));
            while (count-- > 0) {
                offset += parse_message(data + offset, bound - offset, handler);
            }
        }
        return offset;
    }
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    offset += parse_messages(data + offset, bound - offset, handler, packet_header_.template get<message_count>());
    return offset;
}


} // namespace nasdaq::nsmequities::qbbo::itch::v2_1

namespace protocol = ::nasdaq::nsmequities::qbbo::itch::v2_1;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::session>(); }) { values["packet.packetheader.session"] = canonical::text(std::string(header.template get<protocol::session>().value()), '\0', false); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values["packet.packetheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.messages.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".messageheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
    }

    void operator()(const protocol::system_event_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.systemeventmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.template get<protocol::event_code>().value()), ' ', false); }
    }

    void operator()(const protocol::stock_directory_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.stockdirectorymessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.stockdirectorymessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.stockdirectorymessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.stockdirectorymessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_category>(); }) { values[entry + ".payload.stockdirectorymessage.marketcategory"] = canonical::text(canonical::character(message.template get<protocol::market_category>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::financial_status_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.financialstatusindicator"] = canonical::text(canonical::character(message.template get<protocol::financial_status_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { values[entry + ".payload.stockdirectorymessage.roundlotsize"] = canonical::number(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::round_lots_only>(); }) { values[entry + ".payload.stockdirectorymessage.roundlotsonly"] = canonical::text(canonical::character(message.template get<protocol::round_lots_only>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_classification>(); }) { values[entry + ".payload.stockdirectorymessage.issueclassification"] = canonical::text(canonical::character(message.template get<protocol::issue_classification>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::issue_subtype>(); }) { values[entry + ".payload.stockdirectorymessage.issuesubtype"] = canonical::text(std::string(message.template get<protocol::issue_subtype>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::authenticity>(); }) { values[entry + ".payload.stockdirectorymessage.authenticity"] = canonical::text(canonical::character(message.template get<protocol::authenticity>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::short_sale_threshold_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.shortsalethresholdindicator"] = canonical::text(canonical::character(message.template get<protocol::short_sale_threshold_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_flag>(); }) { values[entry + ".payload.stockdirectorymessage.ipoflag"] = canonical::text(canonical::character(message.template get<protocol::ipo_flag>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::luld_reference_price_tier>(); }) { values[entry + ".payload.stockdirectorymessage.luldreferencepricetier"] = canonical::text(canonical::character(message.template get<protocol::luld_reference_price_tier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::etp_flag>(); }) { values[entry + ".payload.stockdirectorymessage.etpflag"] = canonical::text(canonical::character(message.template get<protocol::etp_flag>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::etp_leverage_factor>(); }) { values[entry + ".payload.stockdirectorymessage.etpleveragefactor"] = canonical::number(message.template get<protocol::etp_leverage_factor>().value()); }
        if constexpr (requires { message.template get<protocol::inverse_indicator>(); }) { values[entry + ".payload.stockdirectorymessage.inverseindicator"] = canonical::text(canonical::character(message.template get<protocol::inverse_indicator>().value()), ' ', false); }
    }

    void operator()(const protocol::stock_trading_action_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.stocktradingactionmessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.stocktradingactionmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.stocktradingactionmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.stocktradingactionmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.stocktradingactionmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::current_trading_state>(); }) { values[entry + ".payload.stocktradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message.template get<protocol::current_trading_state>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reason>(); }) { values[entry + ".payload.stocktradingactionmessage.reason"] = canonical::text(std::string(message.template get<protocol::reason>().value()), ' ', false); }
    }

    void operator()(const protocol::reg_sho_restriction_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.regshorestrictionmessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.regshorestrictionmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.regshorestrictionmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.regshorestrictionmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reg_sho_action>(); }) { values[entry + ".payload.regshorestrictionmessage.regshoaction"] = canonical::text(canonical::character(message.template get<protocol::reg_sho_action>().value()), ' ', false); }
    }

    void operator()(const protocol::mwcb_decline_level_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbdeclinelevelmessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::level_1>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level1"] = canonical::scaled(message.template get<protocol::level_1>().value(), -8); }
        if constexpr (requires { message.template get<protocol::level_2>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level2"] = canonical::scaled(message.template get<protocol::level_2>().value(), -8); }
        if constexpr (requires { message.template get<protocol::level_3>(); }) { values[entry + ".payload.mwcbdeclinelevelmessage.level3"] = canonical::scaled(message.template get<protocol::level_3>().value(), -8); }
    }

    void operator()(const protocol::mwcb_breach_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.mwcbbreachmessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.mwcbbreachmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.mwcbbreachmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::breached_level>(); }) { values[entry + ".payload.mwcbbreachmessage.breachedlevel"] = canonical::text(canonical::character(message.template get<protocol::breached_level>().value()), ' ', false); }
    }

    void operator()(const protocol::operational_halt_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.operationalhaltmessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.operationalhaltmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.operationalhaltmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.operationalhaltmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::market_code>(); }) { values[entry + ".payload.operationalhaltmessage.marketcode"] = canonical::text(canonical::character(message.template get<protocol::market_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::operational_halt_action>(); }) { values[entry + ".payload.operationalhaltmessage.operationalhaltaction"] = canonical::text(canonical::character(message.template get<protocol::operational_halt_action>().value()), ' ', false); }
    }

    void operator()(const protocol::bbo_quotation_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.bboquotationmessage";
        if constexpr (requires { message.template get<protocol::tracking_number>(); }) { values[entry + ".payload.bboquotationmessage.trackingnumber"] = canonical::number(message.template get<protocol::tracking_number>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.bboquotationmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.bboquotationmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::security_class>(); }) { values[entry + ".payload.bboquotationmessage.securityclass"] = canonical::text(canonical::character(message.template get<protocol::security_class>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::best_bid_price>(); }) { values[entry + ".payload.bboquotationmessage.bestbidprice"] = canonical::scaled(message.template get<protocol::best_bid_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::best_bid_size>(); }) { values[entry + ".payload.bboquotationmessage.bestbidsize"] = canonical::number(message.template get<protocol::best_bid_size>().value()); }
        if constexpr (requires { message.template get<protocol::best_offer_price>(); }) { values[entry + ".payload.bboquotationmessage.bestofferprice"] = canonical::scaled(message.template get<protocol::best_offer_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::best_offer_size>(); }) { values[entry + ".payload.bboquotationmessage.bestoffersize"] = canonical::number(message.template get<protocol::best_offer_size>().value()); }
    }

    void operator()(const protocol::price_improvement_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.priceimprovementmessage";
        if constexpr (requires { message.template get<protocol::tracking>(); }) { values[entry + ".payload.priceimprovementmessage.tracking"] = canonical::number(message.template get<protocol::tracking>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.priceimprovementmessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.priceimprovementmessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::interest_flag>(); }) { values[entry + ".payload.priceimprovementmessage.interestflag"] = canonical::text(canonical::character(message.template get<protocol::interest_flag>().value()), ' ', false); }
    }

    void operator()(const protocol::ipo_quoting_period_update_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.ipoquotingperiodupdatemessage";
        if constexpr (requires { message.template get<protocol::tracking>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.tracking"] = canonical::number(message.template get<protocol::tracking>().value()); }
        if constexpr (requires { message.template get<protocol::time_stamp>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.timestamp"] = canonical::number(message.template get<protocol::time_stamp>().value()); }
        if constexpr (requires { message.template get<protocol::stock>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.stock"] = canonical::text(std::string(message.template get<protocol::stock>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_time>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasetime"] = canonical::number(message.template get<protocol::ipo_quotation_release_time>().value()); }
        if constexpr (requires { message.template get<protocol::ipo_quotation_release_qualifier>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.ipoquotationreleasequalifier"] = canonical::text(canonical::character(message.template get<protocol::ipo_quotation_release_qualifier>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::ipo_price>(); }) { values[entry + ".payload.ipoquotingperiodupdatemessage.ipoprice"] = canonical::scaled(message.template get<protocol::ipo_price>().value(), -4); }
    }
};

// The values the Tmp reading reads from one datagram, by indexed address. A datagram it cannot read
// is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Tmp and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Nasdaq.NsmEquities.Qbbo.Itch.v2.1 (tmp values)\n");
    int failures = 0;
    failures += check("BboQuotationMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/BboQuotationMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/BboQuotationMessage.values");
    failures += check("RegShoRestrictionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/RegShoRestrictionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/RegShoRestrictionMessage.values");
    failures += check("StockTradingActionMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/StockTradingActionMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/StockTradingActionMessage.values");
    failures += check("SystemEventMessage", "Nasdaq/NsmEquities.Qbbo.Itch.v2.1/SystemEventMessage.pcap", "nasdaq/nsmequities/qbbo/itch/v2.1/SystemEventMessage.values");
    return failures == 0 ? 0 : 1;
}