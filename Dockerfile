# Ubuntu 20.04
# Opencv 4.5.5

ARG BASE_IMAGE=ubuntu:20.04
FROM ${BASE_IMAGE} as base

SHELL ["/bin/bash", "-c"]

# timezone
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Seoul

# Essentials
RUN apt update -y && apt upgrade -y && apt-get install -y --no-install-recommends \
    pkg-config \
    wget \
    sudo \
    build-essential \
    unzip \
    libjpeg-dev libpng-dev \
    apt-utils \
    libboost-all-dev \
    qt5-default \
    libtbb-dev


# Cmake
RUN cd /tmp && \
    wget --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.22.6/cmake-3.22.6-linux-x86_64.sh && \
    chmod +x cmake-3.22.6-linux-x86_64.sh && \
    ./cmake-3.22.6-linux-x86_64.sh --prefix=/usr/local --exclude=subdir --skip-license && \
    rm ./cmake-3.22.6-linux-x86_64.sh

# Opencv
WORKDIR /tmp/opencv_build
ARG OPENCV_VERSION=4.5.5
RUN wget --no-check-certificate https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip && \
    unzip ${OPENCV_VERSION}.zip && rm ${OPENCV_VERSION}.zip && \
    wget --no-check-certificate https://github.com/opencv/opencv_contrib/archive/${OPENCV_VERSION}.zip && \
    unzip ${OPENCV_VERSION}.zip && rm ${OPENCV_VERSION}.zip && \
    mkdir opencv-${OPENCV_VERSION}/build && cd opencv-${OPENCV_VERSION}/build && \
    cmake \
        -DCAMKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DBUILD_DOCS=OFF \
        -DBUILD_TESTS=OFF \
        -DBUILD_PERF_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_opencv_apps=OFF \
        -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-${OPENCV_VERSION}/modules \
        -DENABLE_PRECOMPILED_HEADERS=OFF \
        -DENABLE_CXX11=ON \
        -DOPENCV_GENERATE_PKGCONFIG=ON \
        -DWITH_QT=ON .. && \
    make -j"$(nproc)" && make install && \
    sh -c 'echo '/usr/local/lib' > /etc/ld.so.conf.d/opencv.conf' && \
    ldconfig && \
    rm -rf /tmp/opencv_build
