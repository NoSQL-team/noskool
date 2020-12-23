FROM ubuntu:focal

ENV TZ=Europe/Minsk
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && \
    apt-get install gcc -y && \
    apt-get install g++ -y && \
    apt-get install make -y && \
    apt-get install wget -y && \
    apt-get install libssl-dev -y
RUN mkdir libtmp && cd libtmp && \
    wget https://github.com/Kitware/CMake/releases/download/v3.19.1/cmake-3.19.1.tar.gz && \
    tar -zxvf cmake-3.19.1.tar.gz && cd cmake-3.19.1 && \
    ./bootstrap && make && make install && cd ..

RUN apt-get install libboost-all-dev -y

ADD ./project/includes /app/project/includes
ADD ./project/src /app/project/src
ADD ./client.cpp /app
ADD ./echo_server.cpp /app
ADD ./main.cpp /app
ADD ./CMakeLists.txt /app

RUN cd /app/ && mkdir tmp && cd tmp && cmake .. && make

ADD ./queue_settings.ini /

CMD ["/bin/sh", "-c", "/app/tmp/ServerQueue >&1"]