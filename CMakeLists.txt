cmake_minimum_required(VERSION 3.6)
project(UdpTask)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Drawer.cpp Drawer.h Communicator.cpp Communicator.h Perifery.cpp Perifery.h HardwareEndpoints.h Shape.cpp Shape.h Line.cpp Line.h Color.cpp Color.h Point.cpp Point.h Rectangle.cpp Rectangle.h Polygon.cpp Polygon.h Ellipse.cpp Ellipse.h TextBox.cpp TextBox.h DisplayHandler.cpp DisplayHandler.h LightUnit.cpp LightUnit.h Message.cpp Message.h Broadcaster.cpp Broadcaster.h global_const.h StateMessage.cpp StateMessage.h)
add_executable(UdpTask ${SOURCE_FILES})