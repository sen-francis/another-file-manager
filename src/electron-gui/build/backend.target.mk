# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := backend
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=backend' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DV8_COMPRESS_POINTERS' \
	'-DV8_31BIT_SMIS_ON_64BIT_ARCH' \
	'-DV8_REVERSE_JSARGS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DNAPI_DISABLE_CPP_EXCEPTIONS' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG' \
	'-DV8_ENABLE_CHECKS'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-fPIC \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++1y \
	-std=c++17

INCS_Debug := \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/include/node \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/src \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/openssl/config \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/openssl/openssl/include \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/uv/include \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/zlib \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/v8/include \
	-I/mnt/d/projects/another-file-manager/src/electron-gui/node_modules/node-addon-api

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=backend' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DV8_COMPRESS_POINTERS' \
	'-DV8_31BIT_SMIS_ON_64BIT_ARCH' \
	'-DV8_REVERSE_JSARGS' \
	'-D__STDC_FORMAT_MACROS' \
	'-DNAPI_DISABLE_CPP_EXCEPTIONS' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-fPIC \
	-O3 \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++1y \
	-std=c++17

INCS_Release := \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/include/node \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/src \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/openssl/config \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/openssl/openssl/include \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/uv/include \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/zlib \
	-I/home/sen-francis/.electron-gyp/.cache/node-gyp/13.1.9/deps/v8/include \
	-I/mnt/d/projects/another-file-manager/src/electron-gui/node_modules/node-addon-api

OBJS := \
	$(obj).target/$(TARGET)/../cpp-backend/backend.o \
	$(obj).target/$(TARGET)/../cpp-backend/main.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(builddir)/nothing.a $(obj).target/node_modules/node-addon-api/nothing.a

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS := \
	-lnode

$(obj).target/backend.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/backend.node: LIBS := $(LIBS)
$(obj).target/backend.node: TOOLSET := $(TOOLSET)
$(obj).target/backend.node: $(OBJS) $(obj).target/node_modules/node-addon-api/nothing.a FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/backend.node
# Add target alias
.PHONY: backend
backend: $(builddir)/backend.node

# Copy this to the executable output path.
$(builddir)/backend.node: TOOLSET := $(TOOLSET)
$(builddir)/backend.node: $(obj).target/backend.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/backend.node
# Short alias for building this executable.
.PHONY: backend.node
backend.node: $(obj).target/backend.node $(builddir)/backend.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/backend.node

