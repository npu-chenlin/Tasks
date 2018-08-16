set(SYSTEM_FOUND 1)

IF(WIN32)
    set(SYSTEM_LIBRARIES Iphlpapi wsock32 Ws2_32 Vfw32 Winmm Comctl32)
ELSE(WIN32)
    set(SYSTEM_LIBRARIES pthread dl)
ENDIF(WIN32)
