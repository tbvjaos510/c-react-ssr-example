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

## Install

윈도우, Linux, Mac에서 동작은 하지만 Mac환경에서 실행하기를 권장합니다.

### VCPKG 설치

1. [vcpkg](https://github.com/microsoft/vcpkg)를 설치해 주세요 (홈페이지 참고)

2. 환경변수 등록
   * 윈도우는 환경변수에 들어가서 vcpkg폴더를 추가해 주세요
   * linux/mac에서는

     ```bash
     ln -s ./vcpkg /usr/local/bin/vcpkg
     ```

     를 실행하여 vcpkg를 링크해 주세요

3. cmake toolchain_file folder 추가

   터미널에서

   ```bash
   vcpkg integrate install
   ```

   를 실행한뒤 나오는 출력중에  `-DCMAKE_TOOLCHAIN_FILE=(path)` - 이 (path)를 복사해 주세요

   * 윈도우

     ```bash
     set VCPKG_TOOLCHAIN=(path)
     ```

   * linux/mac

     ```bash
     VCPKG_TOOLCHAIN=(path)
     ```

```bash
git clone https://github.com/tbvjaos510/c-react-ssr-example
cd c-react-ssr-example
npm run bootstrap # for linux/mac
npm run bootstrap:window # for window
```

## Run

```bash
npm start
```

를 통해 웹서버를 실행합니다.

`localhost:3030`에 접속하여 Server Side Rendering 작동을 확인합니다.
