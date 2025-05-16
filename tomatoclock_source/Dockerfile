# 使用官方的Ubuntu镜像作为父镜像
FROM ubuntu:22.04

# 安装中文支持
RUN apt-get update && apt-get install -y locales fonts-wqy-zenhei
RUN locale-gen zh_CN.UTF-8

# 环境变量
ENV LANG zh_CN.UTF-8
ENV LANGUAGE zh_CN:zh
ENV LC_ALL zh_CN.UTF-8

# 其他安装和配置指令
# 设置环境变量以避免在安装软件包时出现交互式提示
ENV DEBIAN_FRONTEND=noninteractive

# 安装必要的依赖项
RUN apt-get update && apt-get install -y \
    build-essential \
    qtbase5-dev \
    qtdeclarative5-dev \
    qt5-qmake \
    qttools5-dev-tools \
    qttools5-dev \
    libgl1-mesa-dev \
    git \
    libxcb-keysyms1-dev \
    libxcb-image0-dev \
    libxcb-shm0-dev \
    libxcb-icccm4-dev \
    libxcb-sync0-dev \
    libxcb-xfixes0-dev \
    libxcb-shape0-dev \
    libxcb-randr0-dev \
    libxcb-render-util0-dev \
    libfontconfig1-dev \
    libfreetype6-dev \
    libx11-dev \
    libxext-dev \
    libxfixes-dev \
    libxi-dev \
    libxrender-dev \
    libxcb1-dev \
    libx11-xcb-dev \
    libxcb-glx0-dev \
    x11vnc \
    xauth \
    mesa-common-dev \
    libglu1-mesa-dev \
    libxkbcommon-dev \
    libxcb-xkb-dev \
    libxslt1-dev \
    libxkbcommon-x11-0
#音频的相关依赖
RUN apt-get update && apt-get install -y qtmultimedia5-dev
# 为应用程序创建目录
RUN mkdir -p /app

# 设置工作目录
WORKDIR /app

# 将应用程序源代码复制到容器中
COPY . /app

# 运行 qmake 生成 Makefile
RUN qmake -o Makefile tomatoclock_source.pro -spec linux-g++ "CONFIG+=debug" "CONFIG+=qml_debug"

# 编译应用程序
RUN make

# 定义运行应用程序的命令
CMD ["./tomatoclock_source"]
