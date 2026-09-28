cmake_minimum_required(VERSION 3.20)
project(omi_cpp_protocols CXX)

# The modern parser uses C++23 (std::byteswap, etc.); a C++23 compiler (GCC 15+) is required.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Each translation unit under checks/ includes a protocol's aggregating headers, so
# compiling it fires the generated layout static_asserts. A clean build is the gate:
# it proves every parser (structs, types, messages) is well-formed and self-consistent.
add_library(protocols_check OBJECT
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.6_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.7_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.8_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v1.9_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.1_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.2_classes.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_advanced.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_modern.cpp
  checks/b3_b3derivatives_binaryumdf_sbe_v2.3_classes.cpp
  checks/iex_iexequities_deep_iextp_v1.06_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.06_modern.cpp
  checks/iex_iexequities_deep_iextp_v1.06_classes.cpp
  checks/iex_iexequities_deep_iextp_v1.08_advanced.cpp
  checks/iex_iexequities_deep_iextp_v1.08_modern.cpp
  checks/iex_iexequities_deep_iextp_v1.08_classes.cpp
  checks/iex_iexequities_deep_snap_v1.6_advanced.cpp
  checks/iex_iexequities_deep_snap_v1.6_modern.cpp
  checks/iex_iexequities_deep_snap_v1.6_classes.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.01_classes.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_advanced.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_modern.cpp
  checks/iex_iexequities_deepplus_iextp_v1.05_classes.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_advanced.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_modern.cpp
  checks/iex_iexequities_deepplus_snap_v1.06_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.56_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.56_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.56_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.64_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.64_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.64_classes.cpp
  checks/iex_iexequities_tops_iextp_v1.66_advanced.cpp
  checks/iex_iexequities_tops_iextp_v1.66_modern.cpp
  checks/iex_iexequities_tops_iextp_v1.66_classes.cpp
  checks/iex_iexequities_tops_snap_v1.6_advanced.cpp
  checks/iex_iexequities_tops_snap_v1.6_modern.cpp
  checks/iex_iexequities_tops_snap_v1.6_classes.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_advanced.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_modern.cpp
  checks/jpx_tseequities_marketbyorder_flex_v1.1_classes.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_advanced.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_modern.cpp
  checks/nasdaq_nsmequities_totalview_itch_v5.0.2023_classes.cpp
)
# The Classes libraries under cpp/classes/ — one static library per protocol, linked by the
# dump program and the classes test that decode through it. Each library precompiles the
# standard headers every one of its many small sources parses.
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.6 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/DeprecatedUnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/DeprecatedUnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/DeprecatedLegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/DeprecatedLegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/DeprecatedInstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/DeprecatedInstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/DeprecatedSecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/PriceBand20Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.6/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.7 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/DeprecatedUnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/DeprecatedUnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/DeprecatedLegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/DeprecatedLegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/DeprecatedInstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/DeprecatedInstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/DeprecatedSecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/PriceBand20Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.7/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.7 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.8 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/DeprecatedUnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/DeprecatedUnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/DeprecatedLegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/DeprecatedLegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/DeprecatedInstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/DeprecatedInstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/DeprecatedSecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/PriceBand20Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.8/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.8 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v1.9 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/bitfields/MatchEventIndicatorOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v1.9/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v1.9 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v2.1 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.1/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v2.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v2.2 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/OptPayoutType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.2/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v2.2 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_b3_b3derivatives_binaryumdf_sbe_v2.3 STATIC
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TemplateId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TradingSessionId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityTradingStatus.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityTradingEvent.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TradingSessionSubId.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityIdSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LotType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/Product.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/ExerciseStyle.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PutOrCall.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceTypeOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/GovernanceIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SecurityMatchType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LastFragment.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MultiLegModel.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MultiLegPriceMethod.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/ImpliedMarketIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OptPayoutType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LegSecurityType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/LegSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/InstrAttribType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/InstrAttribValue.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/NewsSource.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MdUpdateAction.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OpenCloseSettlFlag.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceBandType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceLimitType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceBandMidpointPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/TrdSubType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/OpenCloseSettlFlagOptional.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/PriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/SettlPriceType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/MdEntryType.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/enums/AggressorSide.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/PacketHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/FramingHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/MessageHeader.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SequenceMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/bitfields/MatchEventIndicator.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/EmptyBookMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ChannelReset11Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SecurityStatus3Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SecurityGroupPhase10Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/MaturityMonthYear.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/ContractSettlMonth.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/GroupSizeEncoding.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/UnderlyingsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/UnderlyingsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/LegsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/LegsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/InstrAttribsGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/InstrAttribsGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/SecurityDesc.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SecurityDefinitionMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/Headline.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/Text.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/UrlLink.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/News5Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/OpeningPrice15Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/TheoreticalOpeningPrice16Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ClosingPrice17Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/bitfields/ImbalanceCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/AuctionImbalance19Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/QuantityBand21Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/PriceBand22Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/HighPrice24Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/LowPrice25Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/bitfields/TradeCondition.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/LastTradePrice27Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SettlementPrice28Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/OpenInterest29Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SnapshotFullRefreshHeader30Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/OrderMbO50Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/DeleteOrderMbO51Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/MassDeleteOrdersMbO52Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/Trade53Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ForwardTrade54Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ExecutionSummary55Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/ExecutionStatistics56Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/TradeBust57Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/SnapshotFullRefreshOrdersMbO71Message.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/messages/UnknownMessage.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/Factory.cpp
  cpp/classes/b3/b3derivatives/binaryumdf/sbe/v2.3/Packet.cpp
)
target_include_directories(classes_b3_b3derivatives_binaryumdf_sbe_v2.3 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deep_iextp_v1.06 STATIC
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/Factory.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.06/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.06 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deep_iextp_v1.06 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deep_iextp_v1.08 STATIC
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/Factory.cpp
  cpp/classes/iex/iexequities/deep/iextp/v1.08/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.08 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deep_iextp_v1.08 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deep_snap_v1.6 STATIC
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/Detail.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/EventFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/PriceType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/PriceLevelBuyUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/PriceLevelSellUpdateMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/Factory.cpp
  cpp/classes/iex/iexequities/deep/snap/v1.6/Stream.cpp
)
target_include_directories(classes_iex_iexequities_deep_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deep_snap_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deepplus_iextp_v1.01 STATIC
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.01/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.01 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deepplus_iextp_v1.01 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deepplus_iextp_v1.05 STATIC
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/iextp/v1.05/Packet.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.05 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deepplus_iextp_v1.05 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_deepplus_snap_v1.06 STATIC
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/MessageType.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/Detail.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/enums/Side.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/AddOrderMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/bitfields/ModifyFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OrderModifyMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OrderDeleteMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/OrderExecutedMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/TradeMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/ClearBookMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/Factory.cpp
  cpp/classes/iex/iexequities/deepplus/snap/v1.06/Stream.cpp
)
target_include_directories(classes_iex_iexequities_deepplus_snap_v1.06 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_deepplus_snap_v1.06 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_iextp_v1.56 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.56/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.56/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.56 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_iextp_v1.56 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_iextp_v1.64 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/SecurityEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/SecurityEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.64/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.64 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_iextp_v1.64 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_iextp_v1.66 STATIC
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/structs/IextpHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/Factory.cpp
  cpp/classes/iex/iexequities/tops/iextp/v1.66/Packet.cpp
)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.66 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_iextp_v1.66 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_iex_iexequities_tops_snap_v1.6 STATIC
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/MessageType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/RejectReasonCode.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/IexTpMessageType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/SystemEvent.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/LuldTier.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/TradingStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/RetailLiquidityIndicator.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/OperationalHaltStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/ShortSalePriceTestStatus.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/Detail.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/PriceType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/AuctionType.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/enums/ImbalanceSide.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/structs/MessageHeader.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotRequestMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/ErrorResponseMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotStartMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SystemEventMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/SecurityDirectoryFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SecurityDirectoryMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradingStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/RetailLiquidityIndicatorMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/OperationalHaltStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/ShortSalePriceTestStatusMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/QuoteUpdateFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/QuoteUpdateMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/bitfields/SaleConditionFlags.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradeReportMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/OfficialPriceMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/TradeBreakMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/AuctionInformationMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotDataMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/SnapshotEndMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/UnknownMessage.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/messages/UnknownIexTpMessageData.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/Factory.cpp
  cpp/classes/iex/iexequities/tops/snap/v1.6/Stream.cpp
)
target_include_directories(classes_iex_iexequities_tops_snap_v1.6 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_iex_iexequities_tops_snap_v1.6 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_jpx_tseequities_marketbyorder_flex_v1.1 STATIC
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/MessageType.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/MarketStatus.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ShortSellingStatus.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/PricingMethod.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/TriggeredSide.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/Side.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/OrderCondition.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ModificationFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/AdoptedPricingMethod.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ResetStartEndFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/TestModeFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/CommunicationStartEndFlag.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/PacketType.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/enums/ResultCode.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/structs/PacketHeader.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/structs/MessageHeader.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/SecondsTimestampMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/TradingStatusMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/ExecutionSummaryMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/AddOrderMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/OrderExecutedMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/OrderDeleteMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/ResetMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/CommunicationControlMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/structs/TcpPacketHeader.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/LoginRequestMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/LoginResultMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/MessageResponseMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/EndOfMessageMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/UnknownMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/messages/UnknownTcpMessage.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/Factory.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/UdpPacket.cpp
  cpp/classes/jpx/tseequities/marketbyorder/flex/v1.1/TcpPacket.cpp
)
target_include_directories(classes_jpx_tseequities_marketbyorder_flex_v1.1 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
add_library(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 STATIC
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ClientPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ServerPacketType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RejectReasonCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/EventCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketCategory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/FinancialStatusIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RoundLotsOnly.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IssueClassification.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/Authenticity.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ShortSaleThresholdIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IpoFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/LuldReferencePriceTier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/EtpFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/InverseIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/TradingState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/RegShoAction.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/PrimaryMarketMaker.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketMakerMode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketParticipantState.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/BreachedLevel.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/IpoQuotationReleaseQualifier.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MarketCode.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/OperationalHaltAction.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/BuySellIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/Printable.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/CrossType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/ImbalanceDirection.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/PriceVariationIndicator.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/InterestFlag.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/OpenEligibilityStatus.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/enums/MessageType.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/ClientPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/DebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LoginRequestPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnsequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/ServerPacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/ServerPayloadDebugPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LoginAcceptedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LoginRejectedPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/SystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/StockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/StockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/RegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/MarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/MwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/MwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/IpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/LuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OperationalHaltMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/AddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/AddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/OrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/NonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/CrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/BrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/NetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/RetailPriceImprovementIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/DirectListingWithCapitalRaisePriceDiscoveryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/SequencedDataPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/PacketHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/structs/MessageHeader.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadSystemEventMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadStockDirectoryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadStockTradingActionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadMarketParticipantPositionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadMwcbDeclineLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadMwcbStatusLevelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadIpoQuotingPeriodUpdate.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadLuldAuctionCollarMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOperationalHaltMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadAddOrderNoMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadAddOrderWithMpidAttributionMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderExecutedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderExecutedWithPriceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderCancelMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderDeleteMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadOrderReplaceMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadNonCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadCrossTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadBrokenTradeMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadNetOrderImbalanceIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadRetailPriceImprovementIndicatorMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownServerMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownSequencedMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/messages/UnknownPacketMessage.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/Factory.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/ClientPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/ServerPacket.cpp
  cpp/classes/nasdaq/nsmequities/totalview/itch/v5.0.2023/Packet.cpp
)
target_include_directories(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 PUBLIC ${CMAKE_SOURCE_DIR})
target_precompile_headers(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE <cstddef> <cstdint> <memory> <ostream> <string> <string_view> <vector>)
# Programs under executables/ — one per protocol. Each reads the parser published under
# cpp/, included by a repository-root-relative path, so there is only ever one copy of a
# protocol's parser in the tree.
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.6)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.6)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.6)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.6)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.6 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.6/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.6)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.6 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.6)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.7)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.7)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.7)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.7)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.7 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.7/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.7)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.7 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.7)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.8)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.8)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.8)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.8)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.8 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.8/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.8)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.8 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.8)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v1.9)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v1.9)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v1.9)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.9)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v1.9 executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.9/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v1.9)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v1.9 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v1.9)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.1)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.1)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.1)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.1)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v2.1 executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.1/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.1)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v2.1 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.1)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.2)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.2)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.2)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.2)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v2.2 executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.2/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.2)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v2.2 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.2)
add_executable(statistics_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(statistics_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/b3/b3derivatives/binaryumdf/sbe/v2.3)
add_executable(extractor_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(extractor_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/b3/b3derivatives/binaryumdf/sbe/v2.3)
add_executable(dump_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(dump_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/b3/b3derivatives/binaryumdf/sbe/v2.3)
target_link_libraries(dump_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.3)
add_executable(verify_b3_b3derivatives_binaryumdf_sbe_v2.3 executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.3/main.cpp)
target_include_directories(verify_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/b3/b3derivatives/binaryumdf/sbe/v2.3)
target_link_libraries(verify_b3_b3derivatives_binaryumdf_sbe_v2.3 PRIVATE classes_b3_b3derivatives_binaryumdf_sbe_v2.3)
add_executable(statistics_iex_iexequities_deep_iextp_v1.06 executables/statistics/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.06)
add_executable(extractor_iex_iexequities_deep_iextp_v1.06 executables/extractor/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.06)
add_executable(dump_iex_iexequities_deep_iextp_v1.06 executables/dump/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.06)
target_link_libraries(dump_iex_iexequities_deep_iextp_v1.06 PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(verify_iex_iexequities_deep_iextp_v1.06 executables/verify/iex/iexequities/deep/iextp/v1.06/main.cpp)
target_include_directories(verify_iex_iexequities_deep_iextp_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deep/iextp/v1.06)
target_link_libraries(verify_iex_iexequities_deep_iextp_v1.06 PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(statistics_iex_iexequities_deep_iextp_v1.08 executables/statistics/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/iextp/v1.08)
add_executable(extractor_iex_iexequities_deep_iextp_v1.08 executables/extractor/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/iextp/v1.08)
add_executable(dump_iex_iexequities_deep_iextp_v1.08 executables/dump/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(dump_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/iextp/v1.08)
target_link_libraries(dump_iex_iexequities_deep_iextp_v1.08 PRIVATE classes_iex_iexequities_deep_iextp_v1.08)
add_executable(verify_iex_iexequities_deep_iextp_v1.08 executables/verify/iex/iexequities/deep/iextp/v1.08/main.cpp)
target_include_directories(verify_iex_iexequities_deep_iextp_v1.08 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deep/iextp/v1.08)
target_link_libraries(verify_iex_iexequities_deep_iextp_v1.08 PRIVATE classes_iex_iexequities_deep_iextp_v1.08)
add_executable(statistics_iex_iexequities_deep_snap_v1.6 executables/statistics/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deep/snap/v1.6)
add_executable(extractor_iex_iexequities_deep_snap_v1.6 executables/extractor/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deep/snap/v1.6)
add_executable(dump_iex_iexequities_deep_snap_v1.6 executables/dump/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deep/snap/v1.6)
target_link_libraries(dump_iex_iexequities_deep_snap_v1.6 PRIVATE classes_iex_iexequities_deep_snap_v1.6)
add_executable(verify_iex_iexequities_deep_snap_v1.6 executables/verify/iex/iexequities/deep/snap/v1.6/main.cpp)
target_include_directories(verify_iex_iexequities_deep_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deep/snap/v1.6)
target_link_libraries(verify_iex_iexequities_deep_snap_v1.6 PRIVATE classes_iex_iexequities_deep_snap_v1.6)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.01 executables/statistics/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.01)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.01 executables/extractor/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.01)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.01 executables/dump/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.01)
target_link_libraries(dump_iex_iexequities_deepplus_iextp_v1.01 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(verify_iex_iexequities_deepplus_iextp_v1.01 executables/verify/iex/iexequities/deepplus/iextp/v1.01/main.cpp)
target_include_directories(verify_iex_iexequities_deepplus_iextp_v1.01 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deepplus/iextp/v1.01)
target_link_libraries(verify_iex_iexequities_deepplus_iextp_v1.01 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(statistics_iex_iexequities_deepplus_iextp_v1.05 executables/statistics/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/iextp/v1.05)
add_executable(extractor_iex_iexequities_deepplus_iextp_v1.05 executables/extractor/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/iextp/v1.05)
add_executable(dump_iex_iexequities_deepplus_iextp_v1.05 executables/dump/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/iextp/v1.05)
target_link_libraries(dump_iex_iexequities_deepplus_iextp_v1.05 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.05)
add_executable(verify_iex_iexequities_deepplus_iextp_v1.05 executables/verify/iex/iexequities/deepplus/iextp/v1.05/main.cpp)
target_include_directories(verify_iex_iexequities_deepplus_iextp_v1.05 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deepplus/iextp/v1.05)
target_link_libraries(verify_iex_iexequities_deepplus_iextp_v1.05 PRIVATE classes_iex_iexequities_deepplus_iextp_v1.05)
add_executable(statistics_iex_iexequities_deepplus_snap_v1.06 executables/statistics/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(statistics_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/deepplus/snap/v1.06)
add_executable(extractor_iex_iexequities_deepplus_snap_v1.06 executables/extractor/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(extractor_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/deepplus/snap/v1.06)
add_executable(dump_iex_iexequities_deepplus_snap_v1.06 executables/dump/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(dump_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/deepplus/snap/v1.06)
target_link_libraries(dump_iex_iexequities_deepplus_snap_v1.06 PRIVATE classes_iex_iexequities_deepplus_snap_v1.06)
add_executable(verify_iex_iexequities_deepplus_snap_v1.06 executables/verify/iex/iexequities/deepplus/snap/v1.06/main.cpp)
target_include_directories(verify_iex_iexequities_deepplus_snap_v1.06 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/deepplus/snap/v1.06)
target_link_libraries(verify_iex_iexequities_deepplus_snap_v1.06 PRIVATE classes_iex_iexequities_deepplus_snap_v1.06)
add_executable(statistics_iex_iexequities_tops_iextp_v1.56 executables/statistics/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.56)
add_executable(extractor_iex_iexequities_tops_iextp_v1.56 executables/extractor/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.56)
add_executable(dump_iex_iexequities_tops_iextp_v1.56 executables/dump/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.56)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.56 PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(verify_iex_iexequities_tops_iextp_v1.56 executables/verify/iex/iexequities/tops/iextp/v1.56/main.cpp)
target_include_directories(verify_iex_iexequities_tops_iextp_v1.56 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/iextp/v1.56)
target_link_libraries(verify_iex_iexequities_tops_iextp_v1.56 PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(statistics_iex_iexequities_tops_iextp_v1.64 executables/statistics/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.64)
add_executable(extractor_iex_iexequities_tops_iextp_v1.64 executables/extractor/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.64)
add_executable(dump_iex_iexequities_tops_iextp_v1.64 executables/dump/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.64)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.64 PRIVATE classes_iex_iexequities_tops_iextp_v1.64)
add_executable(verify_iex_iexequities_tops_iextp_v1.64 executables/verify/iex/iexequities/tops/iextp/v1.64/main.cpp)
target_include_directories(verify_iex_iexequities_tops_iextp_v1.64 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/iextp/v1.64)
target_link_libraries(verify_iex_iexequities_tops_iextp_v1.64 PRIVATE classes_iex_iexequities_tops_iextp_v1.64)
add_executable(statistics_iex_iexequities_tops_iextp_v1.66 executables/statistics/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/iextp/v1.66)
add_executable(extractor_iex_iexequities_tops_iextp_v1.66 executables/extractor/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/iextp/v1.66)
add_executable(dump_iex_iexequities_tops_iextp_v1.66 executables/dump/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(dump_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/iextp/v1.66)
target_link_libraries(dump_iex_iexequities_tops_iextp_v1.66 PRIVATE classes_iex_iexequities_tops_iextp_v1.66)
add_executable(verify_iex_iexequities_tops_iextp_v1.66 executables/verify/iex/iexequities/tops/iextp/v1.66/main.cpp)
target_include_directories(verify_iex_iexequities_tops_iextp_v1.66 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/iextp/v1.66)
target_link_libraries(verify_iex_iexequities_tops_iextp_v1.66 PRIVATE classes_iex_iexequities_tops_iextp_v1.66)
add_executable(statistics_iex_iexequities_tops_snap_v1.6 executables/statistics/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(statistics_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/iex/iexequities/tops/snap/v1.6)
add_executable(extractor_iex_iexequities_tops_snap_v1.6 executables/extractor/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(extractor_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/iex/iexequities/tops/snap/v1.6)
add_executable(dump_iex_iexequities_tops_snap_v1.6 executables/dump/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(dump_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/iex/iexequities/tops/snap/v1.6)
target_link_libraries(dump_iex_iexequities_tops_snap_v1.6 PRIVATE classes_iex_iexequities_tops_snap_v1.6)
add_executable(verify_iex_iexequities_tops_snap_v1.6 executables/verify/iex/iexequities/tops/snap/v1.6/main.cpp)
target_include_directories(verify_iex_iexequities_tops_snap_v1.6 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/iex/iexequities/tops/snap/v1.6)
target_link_libraries(verify_iex_iexequities_tops_snap_v1.6 PRIVATE classes_iex_iexequities_tops_snap_v1.6)
add_executable(statistics_jpx_tseequities_marketbyorder_flex_v1.1 executables/statistics/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(statistics_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/jpx/tseequities/marketbyorder/flex/v1.1)
add_executable(extractor_jpx_tseequities_marketbyorder_flex_v1.1 executables/extractor/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(extractor_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/jpx/tseequities/marketbyorder/flex/v1.1)
add_executable(dump_jpx_tseequities_marketbyorder_flex_v1.1 executables/dump/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(dump_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/jpx/tseequities/marketbyorder/flex/v1.1)
target_link_libraries(dump_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE classes_jpx_tseequities_marketbyorder_flex_v1.1)
add_executable(verify_jpx_tseequities_marketbyorder_flex_v1.1 executables/verify/jpx/tseequities/marketbyorder/flex/v1.1/main.cpp)
target_include_directories(verify_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/jpx/tseequities/marketbyorder/flex/v1.1)
target_link_libraries(verify_jpx_tseequities_marketbyorder_flex_v1.1 PRIVATE classes_jpx_tseequities_marketbyorder_flex_v1.1)
add_executable(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/statistics/nasdaq/nsmequities/totalview/itch/v5.0.2023)
add_executable(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/extractor/nasdaq/nsmequities/totalview/itch/v5.0.2023)
add_executable(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/dump/nasdaq/nsmequities/totalview/itch/v5.0.2023)
target_link_libraries(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2023)
add_executable(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2023/main.cpp)
target_include_directories(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap executables/verify/nasdaq/nsmequities/totalview/itch/v5.0.2023)
target_link_libraries(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2023)
# Corpus-driven tests, one family per format under tests/, each through the surface that
# format's program uses: modern through the packet iterator, advanced through the session
# layer, classes through the Packet's decode and encode. The test programs are built by
# every build, so a clean build compiles them the way it compiles checks/ — a generated
# test that does not build is a generator fault and shows up without a capture in sight.
add_executable(modern_iex_iexequities_deep_iextp_v1.06_test tests/modern/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(modern_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deep_iextp_v1.06_test tests/advanced/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(advanced_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deep_iextp_v1.06_test tests/classes/iex_iexequities_deep_iextp_v1.06.cpp)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.06_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deep_iextp_v1.06_test PRIVATE classes_iex_iexequities_deep_iextp_v1.06)
add_executable(modern_iex_iexequities_deep_iextp_v1.08_test tests/modern/iex_iexequities_deep_iextp_v1.08.cpp)
target_include_directories(modern_iex_iexequities_deep_iextp_v1.08_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deep_iextp_v1.08_test tests/advanced/iex_iexequities_deep_iextp_v1.08.cpp)
target_include_directories(advanced_iex_iexequities_deep_iextp_v1.08_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deep_iextp_v1.08_test tests/classes/iex_iexequities_deep_iextp_v1.08.cpp)
target_include_directories(classes_iex_iexequities_deep_iextp_v1.08_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deep_iextp_v1.08_test PRIVATE classes_iex_iexequities_deep_iextp_v1.08)
add_executable(modern_iex_iexequities_deepplus_iextp_v1.01_test tests/modern/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(modern_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deepplus_iextp_v1.01_test tests/advanced/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(advanced_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deepplus_iextp_v1.01_test tests/classes/iex_iexequities_deepplus_iextp_v1.01.cpp)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deepplus_iextp_v1.01_test PRIVATE classes_iex_iexequities_deepplus_iextp_v1.01)
add_executable(modern_iex_iexequities_deepplus_iextp_v1.05_test tests/modern/iex_iexequities_deepplus_iextp_v1.05.cpp)
target_include_directories(modern_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_deepplus_iextp_v1.05_test tests/advanced/iex_iexequities_deepplus_iextp_v1.05.cpp)
target_include_directories(advanced_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_deepplus_iextp_v1.05_test tests/classes/iex_iexequities_deepplus_iextp_v1.05.cpp)
target_include_directories(classes_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_deepplus_iextp_v1.05_test PRIVATE classes_iex_iexequities_deepplus_iextp_v1.05)
add_executable(modern_iex_iexequities_tops_iextp_v1.56_test tests/modern/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.56_test tests/advanced/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.56_test tests/classes/iex_iexequities_tops_iextp_v1.56.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.56_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.56_test PRIVATE classes_iex_iexequities_tops_iextp_v1.56)
add_executable(modern_iex_iexequities_tops_iextp_v1.64_test tests/modern/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.64_test tests/advanced/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.64_test tests/classes/iex_iexequities_tops_iextp_v1.64.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.64_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.64_test PRIVATE classes_iex_iexequities_tops_iextp_v1.64)
add_executable(modern_iex_iexequities_tops_iextp_v1.66_test tests/modern/iex_iexequities_tops_iextp_v1.66.cpp)
target_include_directories(modern_iex_iexequities_tops_iextp_v1.66_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_iex_iexequities_tops_iextp_v1.66_test tests/advanced/iex_iexequities_tops_iextp_v1.66.cpp)
target_include_directories(advanced_iex_iexequities_tops_iextp_v1.66_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_iex_iexequities_tops_iextp_v1.66_test tests/classes/iex_iexequities_tops_iextp_v1.66.cpp)
target_include_directories(classes_iex_iexequities_tops_iextp_v1.66_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_iex_iexequities_tops_iextp_v1.66_test PRIVATE classes_iex_iexequities_tops_iextp_v1.66)
add_executable(modern_jpx_tseequities_marketbyorder_flex_v1.1_test tests/modern/jpx_tseequities_marketbyorder_flex_v1.1.cpp)
target_include_directories(modern_jpx_tseequities_marketbyorder_flex_v1.1_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_jpx_tseequities_marketbyorder_flex_v1.1_test tests/classes/jpx_tseequities_marketbyorder_flex_v1.1.cpp)
target_include_directories(classes_jpx_tseequities_marketbyorder_flex_v1.1_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_jpx_tseequities_marketbyorder_flex_v1.1_test PRIVATE classes_jpx_tseequities_marketbyorder_flex_v1.1)
add_executable(modern_nasdaq_nsmequities_totalview_itch_v5.0.2023_test tests/modern/nasdaq_nsmequities_totalview_itch_v5.0.2023.cpp)
target_include_directories(modern_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023_test tests/advanced/nasdaq_nsmequities_totalview_itch_v5.0.2023.cpp)
target_include_directories(advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
add_executable(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test tests/classes/nasdaq_nsmequities_totalview_itch_v5.0.2023.cpp)
target_include_directories(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE ${CMAKE_SOURCE_DIR} executables/pcap)
target_link_libraries(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test PRIVATE classes_nasdaq_nsmequities_totalview_itch_v5.0.2023)

# Running them reads the captures each protocol declares, and each program is run on its
# protocol's first declared capture. Point OMI_PACKETS_DIR at the corpus checkout:
#
#   cmake -S . -B build -DOMI_PACKETS_DIR=/path/to/packets
#   cmake --build build --parallel && ctest --test-dir build
set(OMI_PACKETS_DIR "" CACHE PATH "Packet corpus checkout holding the capture samples")

if(OMI_PACKETS_DIR)
  enable_testing()

  add_test(NAME modern_iex_iexequities_deep_iextp_v1.06 COMMAND modern_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(modern_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deep_iextp_v1.06 COMMAND advanced_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(advanced_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deep_iextp_v1.06 COMMAND classes_iex_iexequities_deep_iextp_v1.06_test)
  set_tests_properties(classes_iex_iexequities_deep_iextp_v1.06 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_deep_iextp_v1.08 COMMAND modern_iex_iexequities_deep_iextp_v1.08_test)
  set_tests_properties(modern_iex_iexequities_deep_iextp_v1.08 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deep_iextp_v1.08 COMMAND advanced_iex_iexequities_deep_iextp_v1.08_test)
  set_tests_properties(advanced_iex_iexequities_deep_iextp_v1.08 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deep_iextp_v1.08 COMMAND classes_iex_iexequities_deep_iextp_v1.08_test)
  set_tests_properties(classes_iex_iexequities_deep_iextp_v1.08 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_deepplus_iextp_v1.01 COMMAND modern_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(modern_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deepplus_iextp_v1.01 COMMAND advanced_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(advanced_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deepplus_iextp_v1.01 COMMAND classes_iex_iexequities_deepplus_iextp_v1.01_test)
  set_tests_properties(classes_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_deepplus_iextp_v1.05 COMMAND modern_iex_iexequities_deepplus_iextp_v1.05_test)
  set_tests_properties(modern_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_deepplus_iextp_v1.05 COMMAND advanced_iex_iexequities_deepplus_iextp_v1.05_test)
  set_tests_properties(advanced_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_deepplus_iextp_v1.05 COMMAND classes_iex_iexequities_deepplus_iextp_v1.05_test)
  set_tests_properties(classes_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.56 COMMAND modern_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.56 COMMAND advanced_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.56 COMMAND classes_iex_iexequities_tops_iextp_v1.56_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.56 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.64 COMMAND modern_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.64 COMMAND advanced_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.64 COMMAND classes_iex_iexequities_tops_iextp_v1.64_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.64 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_iex_iexequities_tops_iextp_v1.66 COMMAND modern_iex_iexequities_tops_iextp_v1.66_test)
  set_tests_properties(modern_iex_iexequities_tops_iextp_v1.66 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_iex_iexequities_tops_iextp_v1.66 COMMAND advanced_iex_iexequities_tops_iextp_v1.66_test)
  set_tests_properties(advanced_iex_iexequities_tops_iextp_v1.66 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_iex_iexequities_tops_iextp_v1.66 COMMAND classes_iex_iexequities_tops_iextp_v1.66_test)
  set_tests_properties(classes_iex_iexequities_tops_iextp_v1.66 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND modern_jpx_tseequities_marketbyorder_flex_v1.1_test)
  set_tests_properties(modern_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND classes_jpx_tseequities_marketbyorder_flex_v1.1_test)
  set_tests_properties(classes_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME modern_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND modern_nasdaq_nsmequities_totalview_itch_v5.0.2023_test)
  set_tests_properties(modern_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023_test)
  set_tests_properties(advanced_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND classes_nasdaq_nsmequities_totalview_itch_v5.0.2023_test)
  set_tests_properties(classes_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES ENVIRONMENT "OMI_PACKETS_DIR=${OMI_PACKETS_DIR}")

  add_test(NAME statistics_iex_iexequities_deep_iextp_v1.06 COMMAND statistics_iex_iexequities_deep_iextp_v1.06 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.06_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deep_iextp_v1.06)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.06_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deep_iextp_v1.06_samples)
  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.06 COMMAND extractor_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deep_iextp_v1.06)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deep_iextp_v1.06_samples)

  add_test(NAME dump_iex_iexequities_deep_iextp_v1.06 COMMAND dump_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_deep_iextp_v1.06 COMMAND verify_iex_iexequities_deep_iextp_v1.06 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.06/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_deep_iextp_v1.06 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_iex_iexequities_deep_iextp_v1.08 COMMAND statistics_iex_iexequities_deep_iextp_v1.08 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.08_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deep_iextp_v1.08)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.08_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deep_iextp_v1.08_samples)
  add_test(NAME extractor_iex_iexequities_deep_iextp_v1.08 COMMAND extractor_iex_iexequities_deep_iextp_v1.08 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deep_iextp_v1.08)
  set_tests_properties(extractor_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deep_iextp_v1.08_samples)

  add_test(NAME dump_iex_iexequities_deep_iextp_v1.08 COMMAND dump_iex_iexequities_deep_iextp_v1.08 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_deep_iextp_v1.08 COMMAND verify_iex_iexequities_deep_iextp_v1.08 ${OMI_PACKETS_DIR}/Iex/IexEquities.Deep.IexTp.v1.08/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_deep_iextp_v1.08 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_iex_iexequities_deepplus_iextp_v1.01 COMMAND statistics_iex_iexequities_deepplus_iextp_v1.01 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap)
  set_tests_properties(statistics_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "TradeBreakMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.01_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deepplus_iextp_v1.01)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.01_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deepplus_iextp_v1.01_samples)
  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.01 COMMAND extractor_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deepplus_iextp_v1.01)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deepplus_iextp_v1.01_samples)

  add_test(NAME dump_iex_iexequities_deepplus_iextp_v1.01 COMMAND dump_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap)
  set_tests_properties(dump_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "TradeBreakMessage")

  add_test(NAME verify_iex_iexequities_deepplus_iextp_v1.01 COMMAND verify_iex_iexequities_deepplus_iextp_v1.01 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.01/B_TradeBreak.pcap)
  set_tests_properties(verify_iex_iexequities_deepplus_iextp_v1.01 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_iex_iexequities_deepplus_iextp_v1.05 COMMAND statistics_iex_iexequities_deepplus_iextp_v1.05 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.05_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_deepplus_iextp_v1.05)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.05_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_deepplus_iextp_v1.05_samples)
  add_test(NAME extractor_iex_iexequities_deepplus_iextp_v1.05 COMMAND extractor_iex_iexequities_deepplus_iextp_v1.05 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_deepplus_iextp_v1.05)
  set_tests_properties(extractor_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_deepplus_iextp_v1.05_samples)

  add_test(NAME dump_iex_iexequities_deepplus_iextp_v1.05 COMMAND dump_iex_iexequities_deepplus_iextp_v1.05 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap)
  set_tests_properties(dump_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderMessage")

  add_test(NAME verify_iex_iexequities_deepplus_iextp_v1.05 COMMAND verify_iex_iexequities_deepplus_iextp_v1.05 ${OMI_PACKETS_DIR}/Iex/IexEquities.DeepPlus.IexTp.v1.05/AddOrderMessage.pcap)
  set_tests_properties(verify_iex_iexequities_deepplus_iextp_v1.05 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.56 COMMAND statistics_iex_iexequities_tops_iextp_v1.56 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.56_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.56)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.56_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.56_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.56 COMMAND extractor_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.56)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.56_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.56 COMMAND dump_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "QuoteUpdateMessage")

  add_test(NAME verify_iex_iexequities_tops_iextp_v1.56 COMMAND verify_iex_iexequities_tops_iextp_v1.56 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.56/QuoteUpdateMessage.pcap)
  set_tests_properties(verify_iex_iexequities_tops_iextp_v1.56 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.64 COMMAND statistics_iex_iexequities_tops_iextp_v1.64 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.64_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.64)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.64_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.64_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.64 COMMAND extractor_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.64)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.64_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.64 COMMAND dump_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_tops_iextp_v1.64 COMMAND verify_iex_iexequities_tops_iextp_v1.64 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.64/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_tops_iextp_v1.64 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_iex_iexequities_tops_iextp_v1.66 COMMAND statistics_iex_iexequities_tops_iextp_v1.66 -i ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap)
  set_tests_properties(statistics_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.66_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_iex_iexequities_tops_iextp_v1.66)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.66_directory PROPERTIES FIXTURES_SETUP extractor_iex_iexequities_tops_iextp_v1.66_samples)
  add_test(NAME extractor_iex_iexequities_tops_iextp_v1.66 COMMAND extractor_iex_iexequities_tops_iextp_v1.66 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap ${CMAKE_BINARY_DIR}/samples/iex_iexequities_tops_iextp_v1.66)
  set_tests_properties(extractor_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_iex_iexequities_tops_iextp_v1.66_samples)

  add_test(NAME dump_iex_iexequities_tops_iextp_v1.66 COMMAND dump_iex_iexequities_tops_iextp_v1.66 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap)
  set_tests_properties(dump_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "AuctionInformationMessage")

  add_test(NAME verify_iex_iexequities_tops_iextp_v1.66 COMMAND verify_iex_iexequities_tops_iextp_v1.66 ${OMI_PACKETS_DIR}/Iex/IexEquities.Tops.IexTp.v1.66/AuctionInformationMessage.pcap)
  set_tests_properties(verify_iex_iexequities_tops_iextp_v1.66 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND statistics_jpx_tseequities_marketbyorder_flex_v1.1 -i ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap)
  set_tests_properties(statistics_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "CommunicationControlMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_jpx_tseequities_marketbyorder_flex_v1.1_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_jpx_tseequities_marketbyorder_flex_v1.1)
  set_tests_properties(extractor_jpx_tseequities_marketbyorder_flex_v1.1_directory PROPERTIES FIXTURES_SETUP extractor_jpx_tseequities_marketbyorder_flex_v1.1_samples)
  add_test(NAME extractor_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND extractor_jpx_tseequities_marketbyorder_flex_v1.1 ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap ${CMAKE_BINARY_DIR}/samples/jpx_tseequities_marketbyorder_flex_v1.1)
  set_tests_properties(extractor_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_jpx_tseequities_marketbyorder_flex_v1.1_samples)

  add_test(NAME dump_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND dump_jpx_tseequities_marketbyorder_flex_v1.1 ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap)
  set_tests_properties(dump_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "CommunicationControlMessage")

  add_test(NAME verify_jpx_tseequities_marketbyorder_flex_v1.1 COMMAND verify_jpx_tseequities_marketbyorder_flex_v1.1 ${OMI_PACKETS_DIR}/Jpx/TseEquities.MarketByOrder.Flex.v1.1/CommunicationControlMessage.pcap)
  set_tests_properties(verify_jpx_tseequities_marketbyorder_flex_v1.1 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")

  add_test(NAME statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 -i ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap)
  set_tests_properties(statistics_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderNoMpidAttributionMessage \\([^)]*\\) +[1-9]")

  add_test(NAME extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_directory COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/samples/extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023)
  set_tests_properties(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_directory PROPERTIES FIXTURES_SETUP extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_samples)
  add_test(NAME extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap ${CMAKE_BINARY_DIR}/samples/nasdaq_nsmequities_totalview_itch_v5.0.2023)
  set_tests_properties(extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "sampled [1-9]" FIXTURES_REQUIRED extractor_nasdaq_nsmequities_totalview_itch_v5.0.2023_samples)

  add_test(NAME dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap)
  set_tests_properties(dump_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "AddOrderNoMpidAttributionMessage")

  add_test(NAME verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 COMMAND verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 ${OMI_PACKETS_DIR}/Nasdaq/NsmEquities.TotalView.Itch.v5.0.2023/AddOrderNoMPID.pcap)
  set_tests_properties(verify_nasdaq_nsmequities_totalview_itch_v5.0.2023 PROPERTIES PASS_REGULAR_EXPRESSION "\nPASS")
endif()
