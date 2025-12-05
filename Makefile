CC=gcc

# Support both `day=01 make build` and `make build 01`
day ?= $(word 2,$(MAKECMDGOALS))

# build specific sub-directory passed as argument
ifeq ($(day),)
build:
	@echo "Usage: day=01 make build OR make build 01"
	@exit 1
else
build:
	@cd ./$(day)
	@gcc -o ./bin/$(day) ./$(day)/*.c

run: build
	@echo "===================="
	@./bin/$(day) $(day)/puzzle.txt

example: build
	@echo "===================="
	@./bin/$(day) $(day)/example.txt
endif

clean:
	@rm ./bin/*

# Catch the day argument when passed as a target
%:
	@:
