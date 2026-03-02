PLATFORMS = test
DIRS = $(PLATFORMS:%=out/%)

COPTS = --std=c99 -g3 -Og -Wall -Wextra -Werror=implicit-function-declaration -Werror=return-type

.PHONY: clean all $(PLATFORMS)
.DEFAULT_GOAL=test

all: $(PLATFORMS)

objs = $(patsubst src/common/%.c,out/$(1)/%.o,$(wildcard src/common/*.c)) \
	   $(patsubst src/$(1)/%.c,out/$(1)/%.o,$(wildcard src/$(1)/*.c))

$(DIRS): %:
	mkdir -p $@

# Platforms
# Each platform should define the following:
# - a rule with the name of the platform which redirects to whatever the 
# 	platform's main executable is
# - a way to get from src/common/(file).c to out/(platform)/(file).o
# - a way to get from src/(platform)/(file).c to out/(platform)/(file).o
# - a way to get from all of the .o files to a main executable

test: out/test/main | out/test
	./$<
out/test/%.o: src/common/%.c | out/test
	cc $(COPTS) -o $@ -Isrc/test -MMD -c $<
out/test/%.o: src/test/%.c | out/test
	cc $(COPTS) -o $@ -Isrc/common -MMD -c $<
out/test/main: $(call objs,test)
	cc $(COPTS) -o $@ $^

clean:
	rm -rf out

DEPS = $(patsubst %.o,%.d,$(foreach pf,$(PLATFORMS),$(call objs,$(pf))))
-include $(DEPS)