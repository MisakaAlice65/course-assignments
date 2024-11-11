# Makefile
CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = main

all: $(TARGET)

$(TARGET): main.cpp expression_evaluator.cpp
	$(CC) $(CFLAGS) main.cpp expression_evaluator.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

# 生成报告
report:
	xelatex report.tex

