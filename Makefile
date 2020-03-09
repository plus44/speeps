LDFLAGS   = -lbcm2835 -lm 
INCFLAGS  = -I./include
CPPFLAGS += $(INCFLAGS)
CFLAGS   += $(LDFLAGS) -g -O0 -Wall

CC = gcc

OBJ_DRIVER = driver/pi_epdhw.o driver/epdrv_2in9d.o
TARGET = epd

DEBUG_OR_RELEASE = DEBUG
OUTPUT_DIR_NAME = release
ifeq ($(DEBUG_OR_RELEASE), DEBUG)
    CPPFLAGS += -DEPD_LOG_DEBUG
    OUTPUT_DIR_NAME = debug
endif
OBJ_DIR = ./bin/$(OUTPUT_DIR_NAME)

.PHONY: clean mkdir

all: mkdir $(TARGET)

mkdir:
	mkdir -p $(OBJ_DIR)/driver

$(TARGET): $(addprefix $(OBJ_DIR)/, $(OBJ_DRIVER))
	$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ_DRIVER)) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: ./src/%.c
	$(CC) $(CPPFLAGS) $(CPFLAGS) -c -o $@ $<
	
clean :
	@rm -f $(TARGET) $(OBJ_DIR) || true