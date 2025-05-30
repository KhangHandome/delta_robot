# ==========================
# CONFIGURABLE VARIABLES
# ==========================

# Tên file thực thi
TARGET = delta_robot.elf

# Trình biên dịch (sửa thành arm-none-eabi-gcc nếu dùng embedded)
CC = gcc

# Cờ biên dịch
CFLAGS = -Wall -Wextra -O2

# Các thư mục header
INCLUDE_DIRS = \
    Coding/Driver/inc \
    Coding/Hal_layer/inc

# Các thư mục chứa mã nguồn .c
SRC_DIRS = \
    Coding/Application_layer \
    Coding/Driver/src \
    Coding/Hal_layer/src

# Thư mục build chứa các file .o
BUILD_DIR = build

# ==========================
# INTERNAL VARIABLES
# ==========================

# Convert INCLUDE_DIRS to -I flags
INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

# Lấy danh sách tất cả các file .c
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Tạo danh sách các file .o tương ứng trong build/
OBJ_FILES = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# ==========================
# RULES
# ==========================

# Mặc định khi gọi `make` là build
all: build

# Biên dịch toàn bộ
build: $(TARGET)

# Link thành file .elf
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Compile từng file .c thành .o và đưa vào thư mục build/
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Chạy chương trình (chỉ có ý nghĩa khi dùng gcc trên PC)
run: build
	./$(TARGET)

# Xoá file build và file thực thi
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# ==========================
# PHONY
# ==========================
.PHONY: all build clean run
