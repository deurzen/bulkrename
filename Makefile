PROJECT = bulkrename

CC = g++
CXXFLAGS ?= -std=c++17
CXXFLAGS += -lboost_system -lboost_filesystem

OBJDIR = obj
SRCDIR = src

DEPS = $(OBJ_FILES:%.o=%.d)

TARGET = bin/$(PROJECT)

H_FILES := $(shell find $(SRCDIR) -name '*.hh')
SRC_FILES := $(shell find $(SRCDIR) -name '*.cc')
OBJ_FILES := $(patsubst src/%.cc,obj/%.o,${SRC_FILES})

all: build

install:
	install $(RELEASE) /usr/$(BIN)

bin:
	@[ -d bin ] || mkdir bin

obj:
	@[ -d obj ] || mkdir obj

notify-build:
	@echo building

notify-link:
	@echo
	@echo linking

build: notify-build bin obj ${OBJ_FILES} notify-link
	${CC} ${CXXFLAGS} ${OBJ_FILES} -o ${TARGET}

-include $(DEPS)

obj/%.o: obj

obj/%.o: src/%.cc
	${CC} ${CXXFLAGS} -MMD -c $< -o $@

.PHONY: tags
tags:
	@echo
	@echo generating tags
	@ctags -R --exclude=.git --c++-kinds=+p --fields=+iaS --extras=+q .

.PHONY: clean
clean:
	@echo cleaning
	@rm -rf ./bin ./obj
