#!/bin/bash
# -----subdir build-----

mkdir -p build
cd build

QMAKEPRO=`/usr/bin/find ../ -name '*.pro'`

if [ `uname -o ` = "GNU/Linux" ] ; then
  echo "linux"
  if [ ! $QMAKEPRO ]; then
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. ..
  else
    qmake $QMAKEPRO -spec linux-g++  "CONFIG+=release"
  fi
  make -j8
else
  echo "win"
  if [ ! $QMAKEPRO ]; then
    cmake -G "MinGW Makefiles" -DCMAKE_SH=CMAKE_SH-NOTFOUND -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=. ..
  else
    qmake $QMAKEPRO -spec win32-g++ "CONFIG+=release"
  fi
  mingw32-make -j8

  QMAKETARGET=`/usr/bin/find ./ -name '*.exe'| grep release`
  if [ $QMAKETARGET ]; then
    whereis cmake | grep -q "mingw32"
    if [ $? -ne 0 ] ;then
      arch=mingw64
    else
      arch=mingw32
    fi
    echo $arch
    windeployqt $QMAKETARGET
    ldd $QMAKETARGET |grep /$arch/bin | sed "s#[\+0-9a-zA-Z\_\.\-]* =># cp -f#g" | sed "s#(\b0[xX][0-9a-fA-F]*\b)#./release#g" > cp.sh
	sh ./cp.sh
  fi

fi
