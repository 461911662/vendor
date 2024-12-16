
#!/usr/bin/env bash

python_prog=""
curdir=$(dirname "${0}")

SCRIPT_NAME=$(basename "${BASH_SOURCE[0]}")

println() {
  printf "${SCRIPT_NAME%\.*}: ${1}\n"
}

usage() {
  echo ""
  echo "USAGE: ${SCRIPT_NAME} [-h] -t <target>"
  echo ""
  echo "Where:"
  echo "  -t <target> Target project"
  echo ""
}

install_python_zip() {
  local dist=${curdir}/../dist
  local tempdir="${curdir}/../.boss"

#  If You have python-3.11.2-linux-offline.zip, it help you.
#  local off_python_package="python-3.11.2-linux-offline.zip"

#  if command -v unzip &> /dev/null
#  then
#    println "unzip 已安装，无需再次安装."
#  else
#    println "unzip 未安装，正在安装中..."
#    apt-get update
#    apt-get install -y unzip
#    if [ $? -eq 0 ]; then
#      println "unzip 安装成功."
#    else
#      println "unzip 安装失败."
#      usage
#      exit 1
#    fi
#  fi

#  rm -rf ${tempdir}
#  mkdir ${tempdir}
#  unzip -q -o ${dist}/${off_python_package} -d ${tempdir}
#  python_prog=$(command -v ${tempdir}/*/bin/python3)

# Else, You get source for python binary.
  local off_python_package="python-3.11.2-linux-offline"
  rm -rf ${tempdir}
  mkdir ${tempdir}
  cp -rf ${dist}/${off_python_package} ${tempdir}
  python_prog=$(command -v ${tempdir}/*/bin/python3)

  ${python_prog} --version &> /dev/null
  if command -v ${python_prog} &> /dev/null
  then
    println "Python离线版本安装完成."
  else
    rm -rf ${tempdir}
    println "请安装以下步骤手动安装:"
    println "\t1.wget https://www.python.org/ftp/python/3.11.2/Python-3.11.2.tgz"
    println "\t2.tar -zxf Python-3.11.2.tgz"
    println "\t3../configure"
    println "\t4.make && make install"
  fi
}

check_python_env() {
  python_prog=""
  local target=${1}

  if command -v python3 &> /dev/null
  then
    println "Python 3 已安装."
    python_prog="python3"
  elif command -v python &> /dev/null
  then
    python_prog="python"
    println "Python（非Python 3）已安装."
  else
    println "Python 未安装。请安装Python后再试."
  fi

  if [ "s${python_progs}" = "s" ]
  then
    println "开始自动安装离线python压缩包..."
    install_python_zip
  fi
}

while getopts ":ht:" arg; do
  case "${arg}" in
    t)
      target=${OPTARG}
      ;;
    h)
      usage
      exit 0
      ;;
    *)
      usage
      exit 1
      ;;
  esac
done

if [ -z "${target}" ]; then
  printf "ERROR: Missing target project.\n"
  usage
  exit 1
fi

check_python_env $target

println "To Install python virtaul env and tools."
${python_prog} ${curdir}/idf-tools.py install --python-env

"${python_prog} --version"

println "To Download Tools."
${python_prog} ${curdir}/idf-tools.py download --targets $target
