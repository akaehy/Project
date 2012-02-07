#!/bin/sh
#read -p "Enter your name:" name
#echo "hello $name, welcome to my program"
#myvar=foodforthought.tar.gz
#echo $myvar
#echo ${myvar##*fo}
#echo ${myvar#*fo}
#echo ${myvar##*.}
#echo ${myvar#*.}

#read -p "Enter file name:" filename
#echo extension:${filename##*.}
#echo filename:${filename%%.*}
#cmd='ls'
#echo $cmd
#cmd=$(ls)
#echo $cmd
#myvar=hello
#myvar=${myvar}world
#echo $myvar
#filename="foo.tar.gzip"
#if [ ${filename##*.} = "gz" ]
#then
#echo "${filename} is a tarball"
#elif [ ${filename##*. } = "c" ]
#then
#echo "${filename} is a c source"
#else
#echo "${filename} not a tarball or c source"
#fi
#if [ -e a.c ]
#then
#echo a.c exist
#fi
#if [ -d a.c ]
#then
#echo a.c is a directory
#else
#echo a.c not a directory
#fi
#read -p "Enter filename:" filename
#if [ -e $filename ]
#then
	#if [ -d $filename ]
	#then
		#echo "directory"
	#fi
	#if [ -f $filename ]
	#then
		#echo "file"
	#fi
#else
	#echo "file not exist"
#fi
string=hello
#if [ -z "$string" ]
#then
	#echo "len is zero"
#else
	#echo "not zero"
#fi
#if [ $string != "hello" ]
#then
	#echo "not equal"
#else
	#echo "equal"
#fi
#myvar=03
#if [ $myvar -eq 3 ]
#then
	#echo "equal -eq"
#fi
#if [ $myvar = "3" ]
#then
	#echo "equal ="
#fi
#for x in one two three four
#do
	#echo $x
#done
#for name in /etc/r*
#do
	#if [ -d $name ]
	#then
		#echo "$name (dir)"
	#else
		#echo "$name"
	#fi
#done
#echo $0
#echo $1
#echo $#
#echo $@
#filename=$1
#echo extension:${filename##*.}
#echo filename:${filename%%.*}
#echo $@
#for x in $@
#do
	#echo $x
#done
#for file in ./*.c
#do
	#mv $file ${file%.*}.d
#done
myvar=0
until [ $myvar -eq 10 ]
do
	echo $myvar
	myvar=$(($myvar + 1))
done

#向下的文件为
#判断参数个数，不符合退出
if [ $# -ne 3 ]
then
	echo "Arguments error"
	exit
fi
#$1为路径
#$2为文件类型
#$3为前缀
cnt=1
#取得指定路径下指定类型的文件名
for file in $1/*.$2
do
	echo $file
	mv $file $1/$3$cnt.$2
	cnt=$(($cnt+1))
done

if [ $# -ne 2 ]
then echo "Argument error!"
	exit 
fi
myvar=1
while [ $myvar -ne $1 ]
do
	touch $myvar.$2
	myvar=$(($myvar+1))
done



















