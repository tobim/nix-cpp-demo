phony := config shell full
.DEFAULT: config
.PHONY: $(phony)

builddir := build

ifeq (${attr},)
	attr := gcc7
endif

ifeq (${variant},)
	variant := release
endif

.PHONY:=all
all: gen

comma:= ,
empty:=
space:= $(empty) $(empty)
attr_:= $(subst $(comma),$(space),$(attr))
variant_:= $(subst $(comma),$(space),$(variant))


define BOZO

ifeq ($(2),debug)
	VC-$(1)$(2) := Debug
endif
ifeq ($(2),release)
	VC-$(1)$(2) := RelWithDebInfo
endif

BUILD-$(1)$(2) := $(builddir)/$(1)-$(2)

$$(BUILD-$(1)$(2)):
	nix-shell --pure --argstr compiler $(1) --run "cmake -B$$(BUILD-$(1)$(2)) -H. -DCMAKE_BUILD_TYPE=$$(VC-$(1)$(2)) -DCMAKE_EXPORT_COMPILE_COMMANDS=1"

gen: $$(BUILD-$(1)$(2))

.PHONY:=run-$(1)$(2)
run-$(1)$(2): $$(BUILD-$(1)$(2))
	eval `nix-shell --pure --argstr compiler $(1) --run "export" | sed 's/$$$$/\;/'`; \
	$$(MAKE) -C $$(BUILD-$(1)$(2)) --no-print-directory

all: run-$(1)$(2)

endef

$(foreach i,${attr_},$(foreach j,${variant_},$(eval $(call BOZO,$(i),$(j)))))

shell:
	nix-shell --argstr compiler ${attr}


