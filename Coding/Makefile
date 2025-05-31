PROJECT_NAME := delta_robot
PROJECT_DIR  := .
SRC_DIRS     := 
INC_DIRS     := 
GCC          := gcc
CCOPT        := -Wall -Wextra -O2
OBJ_DIR      := obj
OUTPUT_DIR   := bin
# Linker option
LDOPT        := -lgpiod   # Thêm thư viện gpiod khi link

SRC_DIRS += ./Application_layer
SRC_DIRS += ./Driver/src
SRC_DIRS += ./Hal_layer/src

INC_DIRS += ./Driver/inc
INC_DIRS += ./Hal_layer/inc

# Tìm tất cả file .c trong SRC_DIRS
SRC_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
# Chuyển tên file .c thành obj/file.o
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

# Gắn cờ -I cho thư mục chứa .h
INC_PARTS := $(foreach dir,$(INC_DIRS),-I$(dir))

# Cho Make biết file .c nằm ở đâu
vpath %.c $(SRC_DIRS)

# Mặc định
all: build

# Build đầy đủ (compile + link)
build: $(OUTPUT_DIR)/$(PROJECT_NAME)

# Linker flags
LDLIBS += -lgpiod -lpigpio -lrt -lpthread

# Link file .o thành file thực thi
$(OUTPUT_DIR)/$(PROJECT_NAME): $(OBJ_FILES)
	@mkdir -p $(OUTPUT_DIR)
	$(GCC) $^ -o $@ $(LDLIBS)


# Compile từng file .c thành .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(GCC) $(CCOPT) $(INC_PARTS) -c $< -o $@

# Chỉ compile
compiler: $(OBJ_FILES)

# Chạy chương trình
run: build
	./$(OUTPUT_DIR)/$(PROJECT_NAME)

# Dọn sạch
clean:
	rm -rf $(OBJ_DIR) $(OUTPUT_DIR)

.PHONY: all build compiler run clean
