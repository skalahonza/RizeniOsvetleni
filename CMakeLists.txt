cmake_minimum_required(VERSION 3.6)
project(UdpTask)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Updater.cpp Updater.h Perifery.cpp
        Perifery.h HardwareEndpoints.h Shape.cpp Shape.h Line.cpp Line.h
        Color.cpp Color.h Point.cpp Point.h Rectangle.cpp Rectangle.h
        Polygon.cpp Polygon.h Ellipse.cpp Ellipse.h TextBox.cpp TextBox.h
        DisplayHandler.cpp DisplayHandler.h LightUnit.cpp LightUnit.h
        Message.cpp Message.h Broadcaster.cpp Broadcaster.h global_const.h
        StateMessage.cpp StateMessage.h Listener.cpp Listener.h
        font_prop14x16.h font_rom8x16.h font_types.h NetTools.cpp NetTools.h UpdateMessage.cpp UpdateMessage.h)
add_executable(UdpTask ${SOURCE_FILES})