QT -= qt
QT -= core
QT -= gui

DEFINES += EDGETRIGGERED

HEADERS += \
    Socket/SocketClass.h \
    Socket/ServerSocketClass.h \
    Socket/ClientSocketClass.h \
    SocketWatcher/SubscriberServer.h \
    SocketWatcher/SocketWatcher.h \
    SocketWatcher/RegisterServer.h \
    SocketWatcher/PeerWatcher.h \
    SocketWatcher/PeerSocketClass.h \
    Streamer/SocketInfo.h \
    Streamer/DataHolder.h \
    Streamer/BufferedWriter.h \
    Streamer/BufferedReader.h \
    SortedIntegerArray.h \
    PeerNode.h \
    PeerList.h \
    VirtualPeerLoop.h \
    DataMultiplexer.h \
    CallBackClass.h \
    Socket/SocketBase.h \
    IPPack.h \
    HAMCore.h \
    NetworkDiagnostics.h
SOURCES += \
    Socket/SocketClass.cpp \
    Socket/ServerSocketClass.cpp \
    Socket/ClientSocketClass.cpp \
    SocketWatcher/SubscriberServer.cpp \
    SocketWatcher/SocketWatcher.cpp \
    SocketWatcher/RegisterServer.cpp \
    SocketWatcher/PeerWatcher.cpp \
    SocketWatcher/PeerSocketClass.cpp \
    Streamer/SocketInfo.cpp \
    Streamer/DataHolder.cpp \
    Streamer/BufferedWriter.cpp \
    Streamer/BufferedReader.cpp \
    SortedIntegerArray.cpp \
    PeerNode.cpp \
    PeerList.cpp \
    VirtualPeerLoop.cpp \
    main.cpp \
    DataMultiplexer.cpp \
    CallBackClass.cpp \
    Socket/SocketBase.cpp \
    HAMCore.cpp \
    IPPack.cpp \
    NetworkDiagnostics.cpp

#Expat_XML/include/ Expat_XML/src Expat_XML/

INCLUDEPATH = \
Socket \
SocketWatcher \
Streamer
