#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "Settings.hpp"
#include "../pcap/Parser.hpp"
#include "cpp/binary/modern/miax/miaxoptions/complextopofmarket/mach/v1.1/definitions.hpp"

namespace statistics {

// Miax Mach C++ statistics
struct Statistics {

    miax::miaxoptions::complextopofmarket::mach::v1_1::MachMessageIterator mach_message;
    packet::Parser& parser;
    const statistics::Options& options;

    // counters
    uint64_t total_packets = 0;
    uint64_t unknown_packets = 0;
    uint64_t total_messages = 0;
    uint64_t unknown_messages = 0;
    uint64_t heartbeats = 0;

    // message counters
    uint64_t application_message = 0;
    uint64_t system_time_message = 0;
    uint64_t series_update = 0;
    uint64_t complex_strategy_definition_message = 0;
    uint64_t system_state_message = 0;
    uint64_t compact_complex_top_of_market_bid_message = 0;
    uint64_t compact_complex_top_of_market_offer_message = 0;
    uint64_t wide_complex_top_of_market_bid_message = 0;
    uint64_t wide_complex_top_of_market_offer_message = 0;
    uint64_t compact_complex_double_sided_top_of_market_message = 0;
    uint64_t wide_complex_double_sided_top_of_market_message = 0;
    uint64_t strategy_trade_message = 0;
    uint64_t underlying_trading_status_message = 0;

    explicit Statistics(const statistics::Options& options, packet::Parser& parser)
     : parser{ parser }, options{ options } {}

    // process a frame: every tree carrying its transport reads it
    void udp() {
        const auto& frame = parser.frame();

        if (frame.is_udp()) {
            walk_mach_message(frame);
        }
    }

    // walk the Packet tree's datagrams
    void walk_mach_message(const packet::Frame& frame) {
        mach_message.initialize(frame.payload, frame.payload_len);

        while (mach_message.next()) {
            if (mach_message.packet_type == 0 || mach_message.packet_type == 1 || mach_message.packet_type == 2) {
                ++heartbeats;
                continue;
            }

            process_mach_message(mach_message.message, mach_message.packet_type);
        }
    }

    // count a message of the Packet tree
    void process_mach_message(const std::byte* pointer, const std::uint8_t packet_type) {
        switch (packet_type) {
            case 3:
                ++total_messages;
                ++application_message;
                {
                    const auto* sub_header = miax::miaxoptions::complextopofmarket::mach::v1_1::ApplicationMessage::parse(pointer);
                    const char message_type = sub_header->message_type.get();
                    switch (message_type) {
                        case '1':
                            ++system_time_message;
                            break;
                        case 'P':
                            ++series_update;
                            break;
                        case 'C':
                            ++complex_strategy_definition_message;
                            break;
                        case 'S':
                            ++system_state_message;
                            break;
                        case 'b':
                            ++compact_complex_top_of_market_bid_message;
                            break;
                        case 'o':
                            ++compact_complex_top_of_market_offer_message;
                            break;
                        case 'e':
                            ++wide_complex_top_of_market_bid_message;
                            break;
                        case 'f':
                            ++wide_complex_top_of_market_offer_message;
                            break;
                        case 'm':
                            ++compact_complex_double_sided_top_of_market_message;
                            break;
                        case 'w':
                            ++wide_complex_double_sided_top_of_market_message;
                            break;
                        case 't':
                            ++strategy_trade_message;
                            break;
                        case 'H':
                            ++underlying_trading_status_message;
                            break;
                        default:
                            ++unknown_messages;
                            break;
                    }
                }
                break;

            default:
                ++total_messages;
                ++unknown_messages;
                if (options.verbose) {
                    std::cerr << "Unknown packet_type: " << static_cast<int>(packet_type) << std::endl;
                }
                break;
        }
    }

    // report statistics
    void report() {
        std::cout << std::endl;
        std::cout << "Statistics Report" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << "Total packets:   " << total_packets << std::endl;
        std::cout << "Unknown packets: " << unknown_packets << std::endl;
        std::cout << "Total messages:  " << total_messages << std::endl;
        std::cout << "Unknown types:   " << unknown_messages << std::endl;
        std::cout << "Heartbeats:      " << heartbeats << std::endl;

        std::cout << std::endl;
        std::cout << "Message Counts:" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "  ApplicationMessage (3)                           " << application_message << std::endl;
        std::cout << "  SystemTimeMessage (1)                            " << system_time_message << std::endl;
        std::cout << "  SeriesUpdate (P)                                 " << series_update << std::endl;
        std::cout << "  ComplexStrategyDefinitionMessage (C)             " << complex_strategy_definition_message << std::endl;
        std::cout << "  SystemStateMessage (S)                           " << system_state_message << std::endl;
        std::cout << "  CompactComplexTopOfMarketBidMessage (b)          " << compact_complex_top_of_market_bid_message << std::endl;
        std::cout << "  CompactComplexTopOfMarketOfferMessage (o)        " << compact_complex_top_of_market_offer_message << std::endl;
        std::cout << "  WideComplexTopOfMarketBidMessage (e)             " << wide_complex_top_of_market_bid_message << std::endl;
        std::cout << "  WideComplexTopOfMarketOfferMessage (f)           " << wide_complex_top_of_market_offer_message << std::endl;
        std::cout << "  CompactComplexDoubleSidedTopOfMarketMessage (m)  " << compact_complex_double_sided_top_of_market_message << std::endl;
        std::cout << "  WideComplexDoubleSidedTopOfMarketMessage (w)     " << wide_complex_double_sided_top_of_market_message << std::endl;
        std::cout << "  StrategyTradeMessage (t)                         " << strategy_trade_message << std::endl;
        std::cout << "  UnderlyingTradingStatusMessage (H)               " << underlying_trading_status_message << std::endl;
    }
};
}
