# C-React-SSR-Example

C언어와 React를 이용한 Server Side Rendering 예제입니다.

velog: <https://velog.io/@tbvjaos510/C언어와-React로-SSR을-만들어-보자>

## Stack

* C
* CMake
* VCPKG
* Javascript
* React
* Parcel

## Setup

DockerFile로 구성되어 있습니다.
수동으로 실행하는 방법은 [여기](#SETUP_MANUALLY.md)를 참고해 주세요

### 설치

```bash
docker build -t c-react-ssr .
```

### 실행

```bash
docker run -p 3030:3030 c-react-ssr
```

`localhost:3030`에 접속하여 Server Side Rendering 작동을 확인합니다.
