###############################################################################
# MIT License
#
# Copyright (c) 2022 Brian Costabile
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

-include $(TOPDIR)/Make.defs

include Make.defs

# Create dependency list
DEPENDENCIES = $(patsubst %.o,%.d,$(UTTF_OBJS)) $(patsubst %.o,%.d,$(OTFDUMP_OBJS))


# Build rules
#-------------
# Builds all forms of libraries required by selected PRODUCT
.PHONY: all
	all: $(BUILD_DIR)/otf_dump

# microttf build options
$(BUILD_DIR)/$(UTTF_ROOT)/%.o: _CC = $(CC) $(CFLAGS) $(UTTF_IFLAGS)
$(BUILD_DIR)/$(OTFDUMP_ROOT)/%.o: _CC = $(CC) $(CFLAGS) $(OTFDUMP_IFLAGS)

$(BUILD_DIR)/%.o: _CC = $(CC) $(CFLAGS) $(IFLAGS)

# Build C SRCS only generate dependencies if building with gcc
$(BUILD_DIR)/%.o: %.c
	$(ECHO) "CC $(notdir $@)"
	$(MKDIR) $(dir $@)
	$(Q)$(_CC) -c $< -o $@
	$(Q)$(_CC) -c $< -MM -MF $(patsubst %.o,%.d,$@) -MT $@


$(BUILD_DIR)/bin/otfdump: $(UTTF_OBJS) $(OTFDUMP_OBJS)
	$(MKDIR) $(dir $@)
	$(ECHO) "CC $(notdir $@)"
	$(Q)$(CC) $(UTTF_OBJS) $(OTFDUMP_OBJS) -o $@



#-------------
# clean removes all builds
.PHONY: clean
clean:
	$(RM) $(BUILD_ROOT)

.PHONY: uttf
uttf: $(UTTF_LIB)

$(UTTF_LIB): $(UTTF_OBJS)
	$(ECHO) "AR $(notdir $@)"
	$(archive) $(UTTF_OBJS)

# No default rules; we should have explicit rules for everything
.SUFFIXES:

# Uncomment to keep the intermediate files available after build
.SECONDARY:

-include $(DEPENDENCIES)
