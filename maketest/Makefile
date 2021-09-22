# 
# Makefile
# 

# 最終目的のファイル
TARGET = kekka.exe

# ソースファイルの(*.c)一覧
SRCS = prog1.c prog2.c \
	prog3.c

# オブジェクトファイル(*.o)の一覧
OBJS = ${SRCS:.c=.o}

# ヘッダファイル(*.h)の一覧 (今はなし)
HEADERS = 

# コンパイラの設定
CC = i686-pc-cygwin-gcc
CCFLAGS = -Wall -I/usr/include/opengi
LD = i686-pc-cygwin-gcc
LDFLAGS =
# MATH LIB setting
LIBS = -lm
# GLUT LIB setting
# LIBS = -lglpng -lglut32 -lglu32 -lopengl32

# OBJSからTARGETを作る方法
$(TARGET) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

# *.c から *.o を作る方法
.c.o :
	$(CC) $(CCFLAGS) -c $<

# *.o は HEADERS と Makefile に依存 (これらが書き換わったときにも *.o を再構築)
$(OBJS) : $(HEADERS) Makefile

# Make clean としたときの実行コマンド
clean :
	rm -f $(TARGET) $(OBJS) core